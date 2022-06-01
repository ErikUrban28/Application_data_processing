#pragma once

#include "matrix.h"
#include <stdexcept>
#include "../array/array.h"

namespace structures
{
	/// <summary> Implementacia matice v suvislej pamati. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v matici. </typepram>
	template<typename T>
	class CoherentMatrix
		: public Matrix<T>
	{
	public:
		/// <summary>
		///	Konstruktor. Vytvori maticu o danom pocte riadkov a stlpcov.
		/// Polozky su inicializovane na "nulovu" hodnotu typu T.
		/// </summary>
		/// <param name="rowCount"> Pocet riadkov. </param>
		/// <param name="columnCount"> Pocet stlpcov. </param>
		CoherentMatrix(size_t rowCount, size_t columnCount);

		/// <summary> Inicializuje tuto maticu ako kopiu matice odovzdanej ako parameter. </summary>
		/// <param name = "other"> Odkaz na maticu, z ktorej sa prevezmu vlastnosti. </param>
		CoherentMatrix(CoherentMatrix& other);

		/// <summary> Destruktor. </summary>
		~CoherentMatrix();

		/// <summary>
		/// Ak je to mozne (parametrom je matica, ktora ma rovnake rozmery ako ako aktualna matica),
		/// tak skopiruje vlastnosti z matice odovzdanej ako parameter.
		/// Ak to nie je mozne, vyhodi sa vynimka.
		/// </summary>
		/// <param name = "other"> Odkaz na strukturu, z ktorej maju prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary>
		/// Ak je parametrom matica a obsah porovnavanych matic je rovnaky,
		/// tak vrati hodnotu true. V opacnom pripade vrati hodnotu false.
		/// </summary>
		/// <param name="other"> Odkaz na strukturu, s ktorou sa ma tato matica porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Pocet vsetkych prvkov v matici. </summary>
		/// <returns> Pocet prvkov v matici. </returns>
		size_t size() override;

		/// <summary> Vrati pocet riadkov v matici. </summary>
		/// <returns> Pocet riadkov matice. </returns>
		size_t getRowCount() override;

		/// <summary> Vrati pocet stlpcov matice. </summary>
		/// <returns> Pocet stlpcov matice. </returns>
		size_t getColumnCount() override;

		/// <summary> Vrati odkaz na prvok v danom riadku a stlpci. </summary>
		/// <param name="rowIndex"> Index riadku. </param>
		/// <param name="columnIndex"> Index stlpca. </param>
		/// <returns> Odkaz na prvok na danych indexoch. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index riadku alebo stlpca nepatri do matice. </exception>
		T& at(int rowIndex, int columnIndex) override;
	private:
		Vector* vector_;
		size_t size_;
		size_t columnCount_;

	};

	template<typename T>
	inline CoherentMatrix<T>::CoherentMatrix(size_t rowCount, size_t columnCount)
		: Matrix{},
		vector_{ new Vector(rowCount * columnCount * sizeof(T)) },
		size_{ rowCount * columnCount },
		columnCount_{ columnCount }
	{
	}

	template<typename T>
	inline CoherentMatrix<T>::CoherentMatrix(CoherentMatrix& other)
		: Matrix{},
		vector_(new Vector(*(other.vector_))),
		size_(other.size_),
		columnCount_{ other.columnCount_ }
	{
	}

	template<typename T>
	inline CoherentMatrix<T>::~CoherentMatrix()
	{
		delete vector_;
		vector_ = nullptr;
		size_ = 0;
		columnCount_ = 0;
	}

	template<typename T>
	inline Structure& CoherentMatrix<T>::assign(Structure& other)
	{
		if (this != &other)
		{
			const CoherentMatrix<T>& otherMatrix = dynamic_cast<const CoherentMatrix<T>&>(other);
			if (size_ != otherMatrix.size_ || columnCount_ != otherMatrix.columnCount_)
			{
				throw std::invalid_argument("Matrixes are different dimensions!");
			}
			vector_->assign(*otherMatrix.vector_);
		}
		return *this;
	}

	template<typename T>
	inline bool CoherentMatrix<T>::equals(Structure& other)
	{
		const CoherentMatrix<T>* otherMatrix = dynamic_cast<const CoherentMatrix<T>*>(&other);
		if (otherMatrix != nullptr)
		{
			return vector_->equals(*otherMatrix->vector_);
		}
		return false;
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::size()
	{
		return size_;
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::getRowCount()
	{
		return size_ / columnCount_;
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::getColumnCount()
	{
		return columnCount_;
	}

	template<typename T>
	inline T& CoherentMatrix<T>::at(int rowIndex, int columnIndex)
	{
		Utils::rangeCheckExcept(rowIndex, getRowCount(), "Invalid row index !");
		Utils::rangeCheckExcept(columnIndex, columnCount_, "Invalid column index !");

		size_t vectorIndex = (rowIndex * columnCount_ + columnIndex )* sizeof(T);
		byte* vectorPointer = vector_->getBytePointer(vectorIndex);
		T* typeVectorPointer = reinterpret_cast<T*>(vectorPointer);
		return *typeVectorPointer;
	}
	
}