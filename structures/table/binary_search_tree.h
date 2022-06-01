#pragma once

#include "table.h"
#include "../list/list.h"
#include "../tree/binary_tree.h"
#include <stdexcept>

namespace structures
{

	/// <summary> Binarny vyhladavaci strom. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class BinarySearchTree : public Table<K, T>
	{
	public:
		typedef typename BinaryTreeNode<TableItem<K, T>*> BSTTreeNode;
	public:
		/// <summary> Konstruktor. </summary>
		BinarySearchTree();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> BinarySearchTree, z ktoreho sa prevezmu vlastnosti. </param>
		BinarySearchTree(BinarySearchTree<K, T>& other);

		/// <summary> Destruktor. </summary>
		~BinarySearchTree();

		/// <summary> Vrati pocet prvkov v tabulke. </summary>
		/// <returns> Pocet prvkov v tabulke. </returns>
		size_t size() override;

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Porovnanie struktur. </summary>
		/// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Vrati adresou data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <returns> Adresa dat s danym klucom. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak kluc nepatri do tabulky. </exception>
		T& find(const K& key) override;

		/// <summary> Vlozi data s danym klucom do tabulky. </summary>
		/// <param name = "key"> Kluc vkladanych dat. </param>
		/// <param name = "data"> Vkladane data. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak tabulka uz obsahuje data s takymto klucom. </exception>
		void insert(const K& key, const T& data) override;

		/// <summary> Odstrani z tabulky prvok s danym klucom. </summary>
		/// <param name = "key"> Kluc prvku. </param>
		/// <returns> Odstranene data. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak tabulka neobsahuje data s takymto klucom. </exception>
		T remove(const K& key) override;

		/// <summary> Bezpecne ziska data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <param name = "data"> Najdene data (vystupny parameter). </param>
		/// <returns> true, ak sa podarilo najst a naplnit data s danym klucom, false inak. </returns>
		bool tryFind(const K& key, T& data) override;

		/// <summary> Zisti, ci tabulka obsahuje data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <returns> true, tabulka obsahuje dany kluc, false inak. </returns>
		bool containsKey(const K& key) override;

		/// <summary> Vymaze tabulku. </summary>
		void clear() override;

		/// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
		/// <returns> Iterator na zaciatok struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<TableItem<K, T>*>* getBeginIterator() override;

		/// <summary> Vrati skutocny iterator na koniec struktury </summary>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<TableItem<K, T>*>* getEndIterator() override;

	protected:
		/// <summary> Najde vrchol binarneho vyhladavacieho stromu s danym klucom. </summary>
		/// <param name = "key"> Hladany kluc. </param>
		/// <param name = "found"> Vystupny parameter, ktory indikuje, ci sa kluc nasiel. </param>
		/// <returns> Vrchol binarneho vyhladavacieho stromu s danym klucom. Ak sa kluc v tabulke nenachadza, vrati otca, ktoreho by mal mat vrchol s takym klucom. </returns>
		typename BSTTreeNode* findBSTNode(K key, bool& found);

	protected:
		/// <summary> Binarny strom s datami. </summary>
		BinaryTree<TableItem<K, T>*>* binaryTree_;
		/// <summary> Pocet prvkov v binarnom vyhladavacom strome. </summary>
		size_t size_;

		/// <summary> Vlozi vrchol do stromu tak, aby nedoslo k naruseniu usporiadania BST. </summary>
		/// <param name = "node"> Vrchol stromu, ktory ma byt vlozeny. </param>
		/// <returns> true, ak sa podarilo vrchol vlozit (teda v strome nie je vrchol s rovnakym klucom), false inak. </returns>
		bool tryToInsertNode(BSTTreeNode* node);

		/// <summary> Bezpecne vyjme zo stromu vrchol stromu tak, aby nedoslo k naruseniu usporiadania BST. </summary>
		/// <param name = "node"> Vrchol stromu, ktory ma byt vyjmuty. </param>
		/// <remarks> Vrchol nebude zruseny, iba odstraneny zo stromu a ziadne vrcholy nebudu ukazovat na neho a ani on nebude ukazovat na ziadne ine vrcholy. </remarks>
		void extractNode(BSTTreeNode* node);
		
	};

	template<typename K, typename T>
	inline BinarySearchTree<K, T>::BinarySearchTree() :
		Table<K, T>(),
		binaryTree_(new BinaryTree<TableItem<K, T>*>()),
		size_(0)
	{
	}

	template<typename K, typename T>
	inline BinarySearchTree<K, T>::BinarySearchTree(BinarySearchTree<K, T>& other) :
		BinarySearchTree()
	{
		assign(other);
	}

	template<typename K, typename T>
	inline BinarySearchTree<K, T>::~BinarySearchTree()
	{
		BinarySearchTree<K, T>::clear();
		delete binaryTree_;
		binaryTree_ = nullptr;
	}

	template<typename K, typename T>
	inline size_t BinarySearchTree<K, T>::size()
	{
		return size_;
	}

	template<typename K, typename T>
	inline Structure& BinarySearchTree<K, T>::assign(Structure& other)
	{
		if (this != &other)
		{
			BinarySearchTree<K, T>& otherBst = dynamic_cast<BinarySearchTree<K, T>&>(other);
			clear();
			Iterator<TableItem<K, T>*>* iterCurrent =
				new Tree<TableItem<K, T>*>::PreOrderTreeIterator(otherBst.binaryTree_->getRoot());
			Iterator<TableItem<K, T>*>* iterEnd =
				new Tree<TableItem<K, T>*>::PreOrderTreeIterator(nullptr);
			while (*iterCurrent != *iterEnd)
			{
				TableItem<K, T>* item = *(*iterCurrent);
				insert(item->getKey(), item->accessData());
				++(*iterCurrent);
			}
			delete iterCurrent;
			delete iterEnd;
		}
		return *this;
	}

	template<typename K, typename T>
	inline bool BinarySearchTree<K, T>::equals(Structure& other)
	{
		return Table<K, T>::equalsTable(dynamic_cast<BinarySearchTree<K, T>*>(&other));
	}

	template<typename K, typename T>
	inline T& BinarySearchTree<K, T>::find(const K& key)
	{
		bool found = false;
		BinaryTreeNode<TableItem<K, T>*>* node = findBSTNode(key, found);
		if (found)
		{
			return node->accessData()->accessData();
		}
		else
		{
			throw std::out_of_range("Data not found!");
		}
	}

	template<typename K, typename T>
	inline void BinarySearchTree<K, T>::insert(const K& key, const T& data)
	{
		TableItem<K,T>* tableItem = new TableItem<K, T>(key, data);
		BinaryTreeNode<TableItem<K,T>*>* treeNode = new BinaryTreeNode<TableItem<K, T>*>(tableItem);
		if(!tryToInsertNode(treeNode))
		{
			delete tableItem;
			delete treeNode;
			throw std::logic_error("Key already present in the table!");
		}
	}

	template<typename K, typename T>
	inline T BinarySearchTree<K, T>::remove(const K& key)
	{
		bool found = false;
		BinaryTreeNode<TableItem<K,T>*>* nodeToRemove = findBSTNode(key, found);
		if(found)
		{
			extractNode(nodeToRemove);
			T result = nodeToRemove->accessData()->accessData();
			delete nodeToRemove->accessData();
			delete nodeToRemove;
			size_--;
			return result;
		}
		else
		{
			throw std::logic_error("Key not found!");
		}
	}

	template<typename K, typename T>
	inline bool BinarySearchTree<K, T>::tryFind(const K& key, T& data)
	{
		bool result = false;
		BSTTreeNode* node = findBSTNode(key, result);
		if(result)
		{
			data = node->accessData()->accessData();
		}
		return result;
	}

	template<typename K, typename T>
	inline bool BinarySearchTree<K, T>::containsKey(const K& key)
	{
		bool result;
		findBSTNode(key, result);
		return result;
	}

	template<typename K, typename T>
	inline void BinarySearchTree<K, T>::clear()
	{
		for (TableItem<K, T>* tableItem : *binaryTree_)
		{
			delete tableItem;
		}
		binaryTree_->clear();
		size_ = 0;
	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>* BinarySearchTree<K, T>::getBeginIterator()
	{
		return new BinaryTree<TableItem<K, T>*>::InOrderTreeIterator(binaryTree_->getRoot());
	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>* BinarySearchTree<K, T>::getEndIterator()
	{
		return new BinaryTree<TableItem<K, T>*>::InOrderTreeIterator(nullptr);
	}

	template<typename K, typename T>
	inline typename BinarySearchTree<K, T>::BSTTreeNode* BinarySearchTree<K, T>::findBSTNode(K key, bool& found)
	{
		BSTTreeNode* node = dynamic_cast<BSTTreeNode*>(binaryTree_->getRoot());
		BSTTreeNode* result = node;
		while(node != nullptr && node->accessData()->getKey() != key)
		{
			node = key < node->accessData()->getKey() ? node->getLeftSon() : node->getRightSon();
			if(node != nullptr)
			{
				result = node;
			}
		}
		found = node != nullptr && node->accessData()->getKey() == key;
		return result;
	}

	template<typename K, typename T>
	inline bool BinarySearchTree<K, T>::tryToInsertNode(BSTTreeNode* node)
	{
		bool found = false;
		K key = node->accessData()->getKey();
		BSTTreeNode* parent = findBSTNode(key, found);
		if(!found)
		{
			if (this->isEmpty())
				binaryTree_->replaceRoot(node);
			else
			{
				if(key < parent->accessData()->getKey())
					parent->setLeftSon(node);
				else
					parent->setRightSon(node);
			}
			size_++;
		}
		return !found;
	}

	template<typename K, typename T>
	inline void BinarySearchTree<K, T>::extractNode(BSTTreeNode* node)
	{
		BSTTreeNode* parent = node->getParent();
		BSTTreeNode* replaceNode = nullptr;
		switch(node->numberOfSons())
		{
		case 1:
			replaceNode = node->hasLeftSon() ? node->changeLeftSon(nullptr) : node->changeRightSon(nullptr);
			break;
		case 2:
			replaceNode = node->getRightSon();
			while(replaceNode->hasLeftSon())
			{
				replaceNode = replaceNode->getLeftSon();
			}
			extractNode(replaceNode);
			replaceNode->setLeftSon(node->changeLeftSon(nullptr));
			replaceNode->setRightSon(node->changeRightSon(nullptr));
			break;
		default:
			;
		}
		if(parent == nullptr)
			binaryTree_->replaceRoot(replaceNode);
		else
		{
			if(node->isLeftSon())
			{
				parent->setLeftSon(replaceNode);
			}
			else
				parent->setRightSon(replaceNode);
		}
		if(replaceNode != nullptr)
			replaceNode->setParent(parent);
	}
	
}
