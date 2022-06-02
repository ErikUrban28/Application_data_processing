#pragma once
#include "../structures/table/unsorted_sequence_table.h"
#include "../triedenie/quick_sortUJ.h"
#include "../kriterium/kriterium.h"
template <typename K, typename T, typename V>
class Triedenie
{
public:
	void utried(structures::UnsortedSequenceTable<K,T>& table, Kriterium<T,V>& kriterium,bool vzostupne);
private:
	structures::QuickSortUJ<K,T,V>quickSort_; 
};

template<typename K, typename T, typename V>
inline void Triedenie<K, T, V>::utried(structures::UnsortedSequenceTable<K, T>& table, Kriterium<T, V>& kriterium,bool vzostupne)
{
	
		quickSort_.sort(table,kriterium,vzostupne);
}
