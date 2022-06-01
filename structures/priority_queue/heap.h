#pragma once

#include "priority_queue_list.h"
#include "../list/array_list.h"
#include "../utils.h"
#include "../heap_monitor.h"
#include <stdexcept>

namespace structures
{
	/// <summary> Prioritny front implementovany haldou. Implementujucim typom haldy je struktura ArrayList. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	template<typename T>
	class Heap : public PriorityQueueList<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		Heap();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Halda, z ktorej sa prevezmu vlastnosti. </param>
		Heap(Heap<T>& other);

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Vlozi prvok s danou prioritou do haldy. </summary>
		/// <param name = "priority"> Priorita vkladaneho prvku. </param>
		/// <param name = "data"> Vkladany prvok. </param>
		void push(int priority, const T& data) override;

		/// <summary> Odstrani prvok s najvacsou prioritou z haldy. </summary>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je halda prazdna. </exception>
		T pop() override;

	protected:
		/// <summary> Vrati index v ArrayList-e, na ktorom sa nachadza prvok s najvacsou prioritou. </summary>
		/// <returns> Index prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je ArrayList prazdny. </exception>
		int indexOfPeek() override;

	private:
		/// <summary> Vrati index v ArrayList-e, na ktorom by sa mal nachadzat otec daneho prvku. </summary>
		/// <param name = "index"> Index prvku, ktoreho otca chceme vratit. </param>
		/// <returns> Index, na ktorom ba sa mal nachadzat otec prvku. </returns>
		int getParentIndex(int index);

		/// <summary> Vrati index v ArrayList-e, na ktorom by mal mat dany prvok syna s najvacsou prioritou. </summary>
		/// <param name = "index"> Index prvku, ktoreho syna chceme vratit. </param>
		/// <returns> Index, na ktorom by sa mal nachadzat syn prvku. </returns>
		int getGreaterSonIndex(int index);
	};

	template<typename T>
	Heap<T>::Heap() :
		PriorityQueueList<T>(new ArrayList<PriorityQueueItem<T>*>())
	{
	}

	template<typename T>
	Heap<T>::Heap(Heap<T>& other) :
		Heap{}
	{
		assign(other);
	}

	template<typename T>
	inline Structure& Heap<T>::assign(Structure& other)
	{
		return PriorityQueueList<T>::assignPrioQueueList(dynamic_cast<Heap<T>&>(other));
	}

	template<typename T>
	void Heap<T>::push(int priority, const T& data)
	{
		constexpr int INDEX_KOREN{};
		PriorityQueueList<T>::list_->add(new PriorityQueueItem<T>(priority, data));

		int currentIndex{ static_cast<int>(PriorityQueueList<T>::list_->size()) - 1 };
		int parentIndex{ getParentIndex(currentIndex) };

		while ( currentIndex >  INDEX_KOREN && PriorityQueueList<T>::list_->at(currentIndex)->getPriority() < PriorityQueueList<T>::list_->at(parentIndex)->getPriority() )
		{
			Utils::swap(PriorityQueueList<T>::list_->at(currentIndex), PriorityQueueList<T>::list_->at(parentIndex));
			currentIndex = parentIndex;
			parentIndex = getParentIndex(currentIndex);
		}
	}

	template<typename T>
	T Heap<T>::pop()
	{
		int constexpr NEMA_SYNA{-1};
		PriorityQueueItem<T>* item{ (*PriorityQueueList<T>::list_).at(indexOfPeek()) };
		PriorityQueueList<T>::list_->at(indexOfPeek()) = PriorityQueueList<T>::list_->at(static_cast<int>(PriorityQueueList<T>::list_->size()) - 1);
		PriorityQueueList<T>::list_->removeAt(static_cast<int>(PriorityQueueList<T>::list_->size()) - 1);

		int currentIndex{};
		int sonIndex{ getGreaterSonIndex(currentIndex) };

		while (sonIndex < static_cast<int>(PriorityQueueList<T>::list_->size())
			&&
			sonIndex !=  NEMA_SYNA
			&&
			PriorityQueueList<T>::list_->at(currentIndex)->getPriority() >
			PriorityQueueList<T>::list_->at(sonIndex)->getPriority())
		{
			Utils::swap(PriorityQueueList<T>::list_->at(currentIndex), PriorityQueueList<T>::list_->at(sonIndex));
			currentIndex = sonIndex;
			sonIndex = getGreaterSonIndex(currentIndex);
		}

		T data{ item->accessData() };
		delete item;
		return data;
	}

	template<typename T>
	inline int Heap<T>::getParentIndex(int index)
	{
		int constexpr POSUN {1};
		return (index + POSUN) / 2 - POSUN;
	}

	template<typename T>
	inline int Heap<T>::getGreaterSonIndex(int index)
	{
		int constexpr NEMA_SYNA{-1};
		int leftIndex{ 2 * index + 1 };
		int rightIndex{ 2 * index + 2 };
		if (leftIndex >= PriorityQueueList<T>::size())
		{
			return NEMA_SYNA;
		}
		PriorityQueueItem<T>* leftSon{ PriorityQueueList<T>::list_->at(leftIndex) };

		if (rightIndex >= PriorityQueueList<T>::list_->size())
		{
			return leftIndex;
		}
		PriorityQueueItem<T>* rightSon{ PriorityQueueList<T>::list_->at(rightIndex) };
		return rightSon->getPriority() > leftSon->getPriority() ? leftIndex : rightIndex;


	}

	template<typename T>
	inline int Heap<T>::indexOfPeek()
	{
		constexpr int PEEK_INDEX{};
		if (PriorityQueueList<T>::isEmpty())
		{
			throw std::logic_error("Heap empty");
		}
		return PEEK_INDEX;
	}
}