#pragma once

#include "../structures/table/sorting/sort.h"
#include "../structures/table/unsorted_sequence_table.h"
#include "../kriterium/kriterium.h"

namespace structures
{
	/// <summary> Triedenie Quick sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T, typename V>
	class QuickSortUJ : public Sort<K, T>
	{
	private:
		void quick(UnsortedSequenceTable<K, T>& table, int min, int max, Kriterium<T, V>& kriterium, bool vzostupne);
	public:
		/// <summary> Utriedi tabulku triedenim Quick sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table, Kriterium<T, V>& kriterium, bool vzostupne);
		void sort(UnsortedSequenceTable<K, T>& table) override;
	};

	template<typename K, typename T, typename V>
	inline void QuickSortUJ<K, T, V>::quick(UnsortedSequenceTable<K, T>& table, int min, int max, Kriterium<T, V>& kriterium, bool vzostupne)
	{
		V pivot = kriterium.ohodnot(table.getItemAtIndex(min + (max - min) / 2).accessData());
		int lavy = min;
		int pravy = max;
		do
		{
			if (vzostupne) {
				while (kriterium.ohodnot(table.getItemAtIndex(lavy).accessData()) < pivot)
				{
					lavy++;
				}
				while (kriterium.ohodnot(table.getItemAtIndex(pravy).accessData()) > pivot)
				{
					pravy--;
				}
			}
			else
			{
				while (kriterium.ohodnot(table.getItemAtIndex(lavy).accessData()) > pivot)
				{
					lavy++;
				}
				while (kriterium.ohodnot(table.getItemAtIndex(pravy).accessData()) < pivot)
				{
					pravy--;
				}
			}
			if (lavy <= pravy)
			{
				table.swap(lavy, pravy);
				lavy++;
				pravy--;
			}
		} while (lavy <= pravy);
		if (min < pravy)
		{
			quick(table, min, pravy, kriterium,vzostupne);
		}
		if (lavy < max)
		{
			quick(table, lavy, max, kriterium,vzostupne);
		}
	}

	template<typename K, typename T, typename V>
	inline void QuickSortUJ<K, T, V>::sort(UnsortedSequenceTable<K, T>& table, Kriterium<T, V>& kriterium, bool vzostupne)
	{
		quick(table, 0, static_cast<int>(table.size()) - 1, kriterium, vzostupne);
	}

	template<typename K, typename T, typename V>
	inline void QuickSortUJ<K, T, V>::sort(UnsortedSequenceTable<K, T>& table)
	{
	}

}