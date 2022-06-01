#pragma once

#include "list.h"
#include "linked_list.h"
#include "../heap_monitor.h"


namespace structures
{
	// implementacne tipy: 
	//  - namiesto triedy List<T> mozete v triede DoubleLinkedList<T> 
	//    zdedit jednostranne zretazeny zoznam (LinkedList<T>).
	//    ak tak urobite, mozete mnoho metod odstranit a prekryt iba tie, 
	//    ktore maju z pohladu obojsmerne zretazeneho zoznamu vyznam a
	//    zvysok nechat na predka.
	//  - nezabudnite si vytvorit triedu pre prvok obojstranne zretazeneho zoznamu.
	//    opat tento prvok mozete zdedit z prvku jednostranne zretazeneho zoznamu.
	//  - ak vyuzijete dedicnost, budete moct vyuzit predkove iteratory, 
	//    takze ich nebudete musiet implementovat.

	template<typename T>
	class DoubleLinkedListItem : public  DataItem<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		/// <param name = "data"> Data, ktore uchovava. </param>
		DoubleLinkedListItem(T data);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Prvok obojstranne zretazeneho zoznamu, z ktoreho sa prevezmu vlastnosti.. </param>
		DoubleLinkedListItem(DoubleLinkedListItem<T>& other);

		/// <summary> Destruktor. </summary>
		~DoubleLinkedListItem() override;

		/// <summary> Getter predchazdajuceho prvku obojstranne zretazeneho zoznamu. </summary>
		/// <returns> predchadzajuci prvok obojstranne zretazeneho zoznamu. </returns>
		DoubleLinkedListItem<T>* getPrevious();

		/// <summary> Setter predchadzajuceho prvku obojstranne zretazeneho zoznamu. </summary>
		/// <param name´= "previous"> Novy predchadzajuci prvok obojstranne zretazeneho zoznamu. </param>
		void setPrevious(DoubleLinkedListItem<T>* previous);

		/// <summary> Getter nasledujuceho prvku obojstranne zretazeneho zoznamu. </summary>
		/// <returns> Nasledujuci prvok obojstranne zretazeneho zoznamu. </returns>
		DoubleLinkedListItem* getNext();

		/// <summary> Setter nasledujuceho prvku obojstranne zretazeneho zoznamu. </summary>
		/// <param name´= "next"> Novy nasledujuci prvokobojstranne  zretazeneho zoznamu. </param>
		void setNext(DoubleLinkedListItem<T>* next);

	private:
		/// <summary> Predchadzajuci prvok  obojstranne zretazeneho zoznamu. </summary>
		DoubleLinkedListItem<T>* previous_;
		DoubleLinkedListItem<T>* next_;
	};




	/// <summary> Obojstranne zretazeny zoznam. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v zozname. </typepram>
	template<typename T>
	class DoubleLinkedList : public List<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		DoubleLinkedList();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> DoubleLinkedList, z ktoreho sa prevezmu vlastnosti. </param>
		DoubleLinkedList(DoubleLinkedList<T>& other);

		/// <summary> Destruktor. </summary>
		~DoubleLinkedList() override;

		/// <summary> Vrati pocet prvkov v zozname. </summary>
		/// <returns> Pocet prvkov v zozname. </returns>
		size_t size() override;

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Porovnanie struktur. </summary>
		/// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Vrati adresou prvok na indexe. </summary>
	   /// <param name = "index"> Index prvku. </param>
	   /// <returns> Adresa prvku na danom indexe. </returns>
	   /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
		T& at(int index) override;

		/// <summary> Prida prvok do zoznamu. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		void add(const T& data) override;

		/// <summary> Vlozi prvok do zoznamu na dany index. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		/// <param name = "index"> Index prvku. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
		/// <remarks> Ak je ako index zadana hodnota poctu prvkov (teda prvy neplatny index), metoda insert sa sprava ako metoda add. </remarks>
		void insert(const T& data, int index) override;

		/// <summary> Odstrani prvy vyskyt prvku zo zoznamu. </summary>
		/// <param name = "data"> Odstranovany prvok. </param>
		/// <returns> true, ak sa podarilo prvok zo zoznamu odobrat, false inak. </returns>
		bool tryRemove(const T& data) override;

		/// <summary> Odstrani zo zoznamu prvok na danom indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
		T removeAt(int index) override;

		/// <summary> Vrati index prveho vyskytu prvku v zozname. </summary>
		/// <param name = "data"> Prvok, ktoreho index sa hlada. </param>
		/// <returns> Index prveho vyskytu prvku v zozname, ak sa prvok v zozname nenachadza, vrati -1. </returns>
		int getIndexOf(const T& data) override;

		/// <summary> Vymaze zoznam. </summary>
		void clear() override;

		/// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
	   /// <returns> Iterator na zaciatok struktury. </returns>
	   /// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getBeginIterator() override;

		/// <summary> Vrati skutocny iterator na koniec struktury </summary>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getEndIterator() override;

	private:
		/// <summary> Vrati prvok zoznamu na danom indexe. </summary>
		/// <param name = "index"> Pozadovany index. </summary>
		/// <returns> Prvok zoznamu na danom indexe. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
		virtual DoubleLinkedListItem<T>* getItemAtIndex(int index);
		/// <summary> Prvy prvok zoznamu. </summary>
		DoubleLinkedListItem<T>* first_;
		/// <summary> Posledny prvok zoznamu. </summary>
		DoubleLinkedListItem<T>* last_;
		/// <summary> Pocet prvkov v zozname. </summary>
		size_t size_;

	private:
		/// <summary> Iterator pre DoubleLinkedList. </summary>
		class DoubleLinkedListIterator : public Iterator<T>
		{
		public:
			/// <summary> Konstruktor. </summary>
			/// <param name = "position"> Pozicia v zretazenom zozname, na ktorej zacina. </param>
			DoubleLinkedListIterator(DoubleLinkedListItem<T>* position);

			/// <summary> Destruktor. </summary>
			~DoubleLinkedListIterator() override;

			/// <summary> Operator priradenia. Priradi do seba hodnotu druheho iteratora. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> Vrati seba po priradeni. </returns>
			Iterator<T>& operator= (Iterator<T>& other) override;

			/// <summary> Porovna sa s druhym iteratorom na nerovnost. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> True, ak sa iteratory nerovnaju, false inak. </returns>
			bool operator!=(Iterator<T>& other) override;

			/// <summary> Vrati data, na ktore aktualne ukazuje iterator. </summary>
			/// <returns> Data, na ktore aktualne ukazuje iterator. </returns>
			T operator*() override;

			/// <summary> Posunie iterator na dalsi prvok v strukture. </summary>
			/// <returns> Iterator na dalsi prvok v strukture. </returns>
			/// <remarks> Zvycajne vrati seba. Ak vrati iny iterator, povodny bude automaticky zruseny. </remarks>
			Iterator<T>& operator++() override;

		private:
			/// <summary> Aktualna pozicia v zozname. </summary>
			DoubleLinkedListItem<T>* position_;
		};
	};

	template <typename T>
	DoubleLinkedListItem<T>::DoubleLinkedListItem(T data)
		: DataItem<T>{ data }, previous_{ nullptr }, next_{ nullptr }
	{
	}

	template<typename T>
	inline DoubleLinkedListItem<T>::DoubleLinkedListItem(DoubleLinkedListItem<T>& other)
		: DataItem<T>{ other }, previous_{ other.previous_ }, next_{ other.next_ }
	{
	}

	template<typename T>
	inline DoubleLinkedListItem<T>::~DoubleLinkedListItem()
	{
		previous_ = nullptr;
		next_ = nullptr;
	}


	template<typename T>
	inline DoubleLinkedListItem<T>* DoubleLinkedListItem<T>::getPrevious()
	{
		return previous_;
	}


	template<typename T>
	inline void DoubleLinkedListItem<T>::setPrevious(DoubleLinkedListItem<T>* previous)
	{
		previous_ = previous;
	}

	template <typename T>
	DoubleLinkedListItem<T>* DoubleLinkedListItem<T>::getNext()
	{
		return next_;
	}

	template <typename T>
	void DoubleLinkedListItem<T>::setNext(DoubleLinkedListItem<T>* next)
	{
		next_ = next;
	}


	template<typename T>
	inline DoubleLinkedList<T>::DoubleLinkedList()
		:
		List<T>{},
		first_{ nullptr },
		last_{ nullptr },
		size_{}
	{
	}

	template<typename T>
	inline DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList<T>& other)
		:DoubleLinkedList{}
	{
		this->assign(other);
	}

	template<typename T>
	inline DoubleLinkedList<T>::~DoubleLinkedList()
	{
		DoubleLinkedList<T>::clear();
	}
	template<typename T>
	inline size_t DoubleLinkedList<T>::size()
	{
		return size_;
	}

	template<typename T>
	inline Structure& DoubleLinkedList<T>::assign(Structure& other)
	{
		if (this != &other)
		{
			const DoubleLinkedList<T>& otherList = dynamic_cast<DoubleLinkedList<T>&>(other);
			clear();
			DoubleLinkedListItem<T>* otherItem = otherList.first_;
			while (otherItem != nullptr)
			{
				add(otherItem->accessData());
				otherItem = otherItem->getNext();
			}
		}
		return *this;
	}
	template<typename T>
	inline bool DoubleLinkedList<T>::equals(Structure& other)
	{
		if (size_ != other.size()) {
			return false;
		}
		if (this == &other)
		{
			return true;
		}
		DoubleLinkedList<T>* otherList = dynamic_cast<DoubleLinkedList<T>*>(&other);
		if (otherList == nullptr) {
			return false;
		}

		DoubleLinkedListItem<T>* item = first_;
		DoubleLinkedListItem<T>* otherItem = otherList->first_;
		while (item != nullptr)
		{
			if (item->accessData() != otherItem->accessData())
			{
				return false;
			}
			item = item->getNext();
			otherItem = otherItem->getNext();
		}
		return true;
	}

	template<typename T>
	inline T& DoubleLinkedList<T>::at(int index)
	{
		DoubleLinkedListItem<T>* item = getItemAtIndex(index);
		return item->accessData();
	}

	template<typename T>
	inline void DoubleLinkedList<T>::add(const T& data)
	{
		DoubleLinkedListItem<T>* newItem = new DoubleLinkedListItem<T>(data);
		if (size_ == 0) {
			first_ = newItem;
			last_ = newItem;
		}
		else {
			last_->setNext(newItem);
			newItem->setPrevious(last_);
			last_ = newItem;
		}

		++size_;
	}

	template<typename T>
	inline void DoubleLinkedList<T>::insert(const T& data, int index)
	{
		if (index == static_cast<int>(size_))
		{
			add(data);
		}
		else
		{
			Utils::rangeCheckExcept(index, size_, "Index out of range");
			DoubleLinkedListItem<T>* newItem = new DoubleLinkedListItem<T>(data);
			if (index == 0)
			{
				newItem->setNext(first_);
				first_->setPrevious(newItem);
				first_ = newItem;
			}
			else
			{
				DoubleLinkedListItem<T>* prevItem = getItemAtIndex(index - 1);

				newItem->setNext(prevItem->getNext()); //nastav ako 'next' pridanemu prvu ten prvok, ktory bol 'next' prvkom, prvku predtym
				prevItem->setNext(newItem);
				newItem->getNext()->setPrevious(newItem); // nastav dalsiemu prvku aktualne pridany prvok ako 'previous'
				newItem->setPrevious(prevItem);
			}
			++size_;
		}
	}

	template<typename T>
	inline bool DoubleLinkedList<T>::tryRemove(const T& data)
	{
		int index = getIndexOf(data);
		if (index == -1)
		{
			return false;
		}
			removeAt(index);
			return true;
	}

	template<typename T>
	inline T DoubleLinkedList<T>::removeAt(int index)
	{
		Utils::rangeCheckExcept(index, size_, "Index out of range");
		DoubleLinkedListItem<T>* delItem;
		if (first_ == last_)
		{
			delItem = first_;
			first_ = nullptr;
			last_ = nullptr;
		}
		else
		{
			if (index == 0)
			{
				delItem = first_;
				first_ = first_->getNext();
				first_->setPrevious(nullptr);
			}
			else {
				DoubleLinkedListItem<T>* previousItem = getItemAtIndex(index - 1);
				delItem = previousItem->getNext();
				previousItem->setNext(delItem->getNext());

				if (last_ == delItem)
				{
					last_ = previousItem;
				}
				else
				{
					delItem->getNext()->setPrevious(previousItem);
				}
			}
		}
		T result = delItem->accessData();
		delete delItem;
		--size_;
		return result;
	}

	template<typename T>
	inline int DoubleLinkedList<T>::getIndexOf(const T& data)
	{
		DoubleLinkedListItem<T>* item = first_;
		int index = 0;

		while (item != nullptr)
		{
			if (item->accessData() == data)
			{
				return index;
			}
			++index;
			item = item->getNext();
		}
		return -1;
	}

	template<typename T>
	inline void DoubleLinkedList<T>::clear()
	{
		if (size_ != 0)
		{
			DoubleLinkedListItem<T>* delItem = first_;
			while (delItem != nullptr)
			{
				DoubleLinkedListItem<T>* nextItem = delItem->getNext();
				delete delItem;
				delItem = nextItem;
			}
			size_ = 0;
			first_ = nullptr;
			last_ = nullptr;
		}
	}


	template<typename T>
	inline DoubleLinkedListItem<T>* DoubleLinkedList<T>::getItemAtIndex(int index)
	{
		Utils::rangeCheckExcept(index, size_, "Index out of the range");
		DoubleLinkedListItem<T>* result;
		if (index <= size_ / 2)
		{
			result = first_;
			if (result)
			{
				for (int i{}; i < index; ++i)
				{
					result = result->getNext();
				}
			}
		}
		else
		{
			result = last_;
			if (result)
			{
				for (int i = size_ - 1; i > index; --i)
				{
					result = result->getPrevious();
				}
			}
		}
		return result;
	}


	template<typename T>
	inline Iterator<T>* DoubleLinkedList<T>::getBeginIterator()
	{
		return new DoubleLinkedListIterator(first_);
	}

	template<typename T>
	inline Iterator<T>* DoubleLinkedList<T>::getEndIterator()
	{
		return new DoubleLinkedListIterator(nullptr);
	}
	template<typename T>
	inline DoubleLinkedList<T>::DoubleLinkedListIterator::DoubleLinkedListIterator(DoubleLinkedListItem<T>* position)
		:position_{ position }
	{
	}

	template<typename T>
	inline DoubleLinkedList<T>::DoubleLinkedListIterator::~DoubleLinkedListIterator()
	{
		position_ = nullptr;
	}

	template<typename T>
	inline Iterator<T>& DoubleLinkedList<T>::DoubleLinkedListIterator::operator=(Iterator<T>& other)
	{
		position_ = dynamic_cast<const DoubleLinkedListIterator&>(other).position_;
		return *this;
	}

	template<typename T>
	inline bool DoubleLinkedList<T>::DoubleLinkedListIterator::operator!=(Iterator<T>& other)
	{
		return position_ != dynamic_cast<const DoubleLinkedListIterator&>(other).position_;
	}

	template<typename T>
	inline T DoubleLinkedList<T>::DoubleLinkedListIterator::operator*()
	{
		return position_->accessData();
	}

	template<typename T>
	inline Iterator<T>& DoubleLinkedList<T>::DoubleLinkedListIterator::operator++()
	{
		position_ = position_->getNext();
		return *this;
	}

}