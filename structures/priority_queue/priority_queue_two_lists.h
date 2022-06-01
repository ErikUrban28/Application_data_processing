#pragma once

#include "priority_queue.h"
#include "priority_queue_limited_sorted_array_list.h"
#include "../heap_monitor.h"
#include "../list/linked_list.h"
#include <cmath>

namespace structures
{
	/// <summary> Prioritny front implementovany dvojzoznamom. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	/// <remarks> Implementacia efektivne vyuziva prioritny front implementovany utriednym ArrayList-om s obmedzenou kapacitou a LinkedList. </remarks>
	template<typename T>
	class PriorityQueueTwoLists : public PriorityQueue<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		PriorityQueueTwoLists();

		PriorityQueueTwoLists(PriorityQueueTwoLists<T>& other);
		~PriorityQueueTwoLists();

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Vrati pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </summary>
		/// <returns> Pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </returns>
		size_t size() override;

		/// <summary> Vymaze obsah prioritneho frontu implementovaneho dvojzoznamom. </summary>
		void clear() override;

		/// <summary> Vlozi prvok s danou prioritou do prioritneho frontu. </summary>
		/// <param name = "priority"> Priorita vkladaneho prvku. </param>
		/// <param name = "data"> Vkladany prvok. </param>
		void push(int priority, const T& data) override;

		/// <summary> Odstrani prvok s najvacsou prioritou z prioritneho frontu implementovaneho dvojzoznamom. </summary>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		T pop() override;

		/// <summary> Vrati adresou prvok s najvacsou prioritou. </summary>
		/// <returns> Adresa, na ktorej sa nachadza prvok s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		T& peek() override;

		/// <summary> Vrati prioritu prvku s najvacsou prioritou. </summary>
		/// <returns> Priorita prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		int peekPriority() override;

	private:
		/// <summary> Smernik na prioritny front ako implementovany utriednym ArrayList-om s obmedzenou kapacitou . </summary>
		/// <remarks> Z pohladu dvojzoznamu sa jedna o kratsi utriedeny zoznam. </remarks>
		PriorityQueueLimitedSortedArrayList<T>* shortList_;

		/// <summary> Smernik na dlhsi neutriedeny zoznam. </summary>
		LinkedList<PriorityQueueItem<T>*>* longList_;
	};

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists() :
		shortList_(new PriorityQueueLimitedSortedArrayList<T>()),
		longList_(new LinkedList<PriorityQueueItem<T>*>())
	{
	}

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists(PriorityQueueTwoLists<T>& other) :
		PriorityQueueTwoLists<T>{}
	{
		assign(other);
	}

	template<typename T>
	PriorityQueueTwoLists<T>::~PriorityQueueTwoLists()
	{
		PriorityQueueTwoLists<T>::clear();
		delete longList_;
		longList_ = nullptr;
		delete shortList_;
		shortList_ = nullptr;

	}

	template<typename T>
	Structure& PriorityQueueTwoLists<T>::assign(Structure& other)
	{
		constexpr int ZACIATOK_LISTU{};
		if (this != &other)
		{
			PriorityQueueTwoLists& otherPriorityQueueTwoLists { dynamic_cast<PriorityQueueTwoLists&>(other)};
			clear();
			shortList_->assign(*otherPriorityQueueTwoLists.shortList_);
			for(PriorityQueueItem<T>* element : *otherPriorityQueueTwoLists.longList_)
			{
				longList_->insert(new PriorityQueueItem<T>{*element},ZACIATOK_LISTU);
			}
		}
		return *this;
	}

	template<typename T>
	size_t PriorityQueueTwoLists<T>::size()
	{
		return longList_->size() + shortList_->size();
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::clear()
	{

		for ( auto element : *longList_)
		{
			delete element;
		}
		longList_->clear();
		shortList_->clear();
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::push(int priority, const T& data)
	{
		if(longList_->isEmpty() || shortList_->minPriority() > priority)
		{
			PriorityQueueItem<T>* item {shortList_->pushAndRemove(priority,data)};
			if(item)
			{
				longList_->add(item);
			}
		}
		else
		{
			PriorityQueueItem<T>* item = {new PriorityQueueItem<T>{priority, data}};
			longList_->add(item);
		}
	}

	template<typename T>
	T PriorityQueueTwoLists<T>::pop()
	{
		constexpr int DEFAULT {4};
		constexpr int ZACIATOK_LISTU{};
		T deletedItem = shortList_->pop();
		if(shortList_->isEmpty() && !longList_->isEmpty())
		{
			if(sqrt(longList_->size()) < DEFAULT)
			{
				shortList_->trySetCapacity(DEFAULT);
			}
			else
			{
				shortList_->trySetCapacity(sqrt(longList_->size()));
			}

			LinkedList<PriorityQueueItem<T>*>* helpingList { new LinkedList<PriorityQueueItem<T>*>()};
			while (!longList_->isEmpty())
			{
				PriorityQueueItem<T>* longItem {longList_->removeAt(ZACIATOK_LISTU)};
				PriorityQueueItem<T>* shortItem {shortList_->pushAndRemove(longItem->getPriority(),longItem->accessData())};
				if (shortItem)
				{
					helpingList->add(shortItem);
				}
				delete longItem;
			}
			longList_->assign(*helpingList);
			delete helpingList;
		}
		return deletedItem;
	}

	template<typename T>
	T& PriorityQueueTwoLists<T>::peek()
	{
		return shortList_->peek();
	}

	template<typename T>
	int PriorityQueueTwoLists<T>::peekPriority()
	{
		return shortList_->peekPriority();
	}
}