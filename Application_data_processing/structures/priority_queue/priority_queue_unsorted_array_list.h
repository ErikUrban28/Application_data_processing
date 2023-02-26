#pragma once

#include "priority_queue_list.h"
#include "../heap_monitor.h"

namespace structures
{
	/// <summary> Prioritny front implementovany neutriednym ArrayList-om. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	template<typename T>
	class PriorityQueueUnsortedArrayList : public PriorityQueueList<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		PriorityQueueUnsortedArrayList();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Prioritny front implementovany neutriednym ArrayList-om, z ktoreho sa prevezmu vlastnosti. </param>
		PriorityQueueUnsortedArrayList(PriorityQueueUnsortedArrayList<T>& other);

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Vlozi prvok s danou prioritou do prioritneho frontu implementovaneho neutriednym ArrayList-om. </summary>
		/// <param name = "priority"> Priorita vkladaneho prvku. </param>
		/// <param name = "data"> Vkladany prvok. </param>
		void push(int priority, const T& data) override;

		/// <summary> Odstrani prvok s najvacsou prioritou z prioritneho frontu implementovaneho neutriednym ArrayList-om. </summary>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany neutriednym ArrayList-om prazdny. </exception>
		T pop() override;
	};

	template<typename T>
	PriorityQueueUnsortedArrayList<T>::PriorityQueueUnsortedArrayList() :
		PriorityQueueList<T>(new ArrayList<PriorityQueueItem<T>*>())
	{
	}

	template<typename T>
	PriorityQueueUnsortedArrayList<T>::PriorityQueueUnsortedArrayList(PriorityQueueUnsortedArrayList<T>& other) :
		PriorityQueueList<T>(
			new ArrayList<PriorityQueueItem<T>*>(
				dynamic_cast<ArrayList<PriorityQueueItem<T>*>&>(*other.list_)))
	{
	}

	template<typename T>
	inline Structure& PriorityQueueUnsortedArrayList<T>::assign(Structure& other)
	{
		return PriorityQueueList<T>::assignPrioQueueList(dynamic_cast<PriorityQueueUnsortedArrayList<T>&>(other));
	}

	template<typename T>
	void PriorityQueueUnsortedArrayList<T>::push(int priority, const T& data)
	{
		PriorityQueueList<T>::list_->add(new PriorityQueueItem<T>(priority, data));
	}

	template<typename T>
	inline T PriorityQueueUnsortedArrayList<T>::pop()
	{
		int index = PriorityQueueList<T>::indexOfPeek();

		PriorityQueueItem<T>* item = PriorityQueueList<T>::list_->at(index);
		PriorityQueueList<T>::list_->at(index) = PriorityQueueList<T>::list_->at(static_cast<int>(PriorityQueueList<T>::list_->size()) - 1);
		PriorityQueueList<T>::list_->removeAt(static_cast<int>(PriorityQueueList<T>::list_->size()) - 1);

		T data = item->accessData();
		delete item;

		return data;
	}
}