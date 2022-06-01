#pragma once

#include "matrix.h"
#include <stdexcept>

namespace structures
{
	/// <summary> Implementacia matice v nesuvislej pamati. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v matici. </typepram>
	template<typename T>
	class IncoherentMatrix
		: public Matrix<T>
	{
	public:
		/// <summary>
		///	Konstruktor. Vytvori maticu o danom pocte riadkov a stlpcov.
		/// Polozky su inicializovane na "nulovu" hodnotu typu T.
		/// </summary>
		/// <param name="rowCount"> Pocet riadkov. </param>
		/// <param name="columnCount"> Pocet stlpcov. </param>
		IncoherentMatrix(size_t rowCount, size_t columnCount);

		/// <summary> Inicializuje tuto maticu ako kopiu matice odovzdanej ako parameter. </summary>
		/// <param name = "other"> Odkaz na maticu, z ktorej sa prevezmu vlastnosti. </param>
		IncoherentMatrix(IncoherentMatrix& other);

		/// <summary> Destruktor. </summary>
		~IncoherentMatrix();

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
		Array<Array<T>*>* matrix_;
		size_t rowCount_;
		size_t columnCount_;
	};

	template<typename T>
	inline IncoherentMatrix<T>::IncoherentMatrix(size_t rowCount, size_t columnCount)
		: Matrix{}, matrix_{ new Array<Array<T>*>(rowCount) }, rowCount_{ rowCount }, columnCount_{ columnCount }
	{
		for (size_t i{}; i < rowCount_; ++i)
		{
			matrix_->at(i) = new Array<T>(columnCount_);
		}

	}

	template<typename T>
	inline IncoherentMatrix<T>::IncoherentMatrix(IncoherentMatrix& other)
		: Matrix{}, matrix_{ new Array<Array<T>*>(other.rowCount_) },
		rowCount_{ other.rowCount_ }, columnCount_{ other.columnCount_ }

	{
		for (size_t i{}; i < rowCount_; ++i)
		{
			matrix_->at(i) = new Array<T>(*other.matrix_->at(i));
		}
	}

	template<typename T>
	inline IncoherentMatrix<T>::~IncoherentMatrix()
	{
		for (size_t i{}; i < rowCount_; ++i)
		{
			delete matrix_->at(i);
			matrix_->at(i) = nullptr;
		}
		delete matrix_;
		matrix_ = nullptr;
		rowCount_ = 0;
		columnCount_ = 0;
	}

	template<typename T>
	inline Structure& IncoherentMatrix<T>::assign(Structure& other)
	{

		if (this != &other)
		{
			IncoherentMatrix<T>& otherMatrix = dynamic_cast<IncoherentMatrix<T>&>(other);
			if (rowCount_ != otherMatrix.rowCount_ || columnCount_ != otherMatrix.columnCount_)
			{
				throw std::invalid_argument("Matrixes are different dimensions!");
			}
			delete matrix_;
			matrix_ = new Array<Array<T>*>(rowCount_);
			for (int i{};i < rowCount_; ++i)
			{
				delete matrix_->at(i);
				matrix_->at(i) = new Array<T>(*otherMatrix.matrix_->at(i));
			}
		}
		return *this;
	}

	template<typename T>
	inline bool IncoherentMatrix<T>::equals(Structure& other)
	{
		IncoherentMatrix<T>* otherMatrix = dynamic_cast<IncoherentMatrix<T>*>(&other);
		if (otherMatrix != nullptr && rowCount_ == otherMatrix->rowCount_ && columnCount_ == otherMatrix->columnCount_)
		{
			for (size_t i{}; i < rowCount_; ++i)
			{
				for (size_t j{}; j < columnCount_; ++j)
				{
					if (this->at(i,j) != otherMatrix->at(i, j))
					{
						return false;
					}
				}
			}
			return true;
		}
		return false;
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::size()
	{
		return rowCount_ * columnCount_;
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::getRowCount()
	{
		return  rowCount_;
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::getColumnCount()
	{
		return  columnCount_;
	}

	template<typename T>
	inline T& IncoherentMatrix<T>::at(int rowIndex, int columnIndex)
	{
		return matrix_->at(rowIndex)->at(columnIndex);
	}
}