#pragma once
#include "../structures/list/linked_list.h"
#include "../filter/Filter.h"
#include "../structures/table/sorted_sequence_table.h"
#include "../structures/table/unsorted_sequence_table.h"
template <typename O>
class ZlozenyFilter : public Filter<O>
{
protected:
	structures::LinkedList<Filter<O>*>filtre_;
public:
	void addFilter(Filter<O>* filter);
	size_t size() {return filtre_.size();}
	virtual void vyfiltruj(structures::SortedSequenceTable<std::string, UzemnaJednotka*>& table,
		structures::UnsortedSequenceTable<std::string, UzemnaJednotka*>& newTable) = 0;
	~ZlozenyFilter() override;
};


template<typename O>
inline void ZlozenyFilter<O>::addFilter(Filter<O>* filter)
{
	filtre_.add(filter);
}

template<typename O>
inline ZlozenyFilter<O>::~ZlozenyFilter()
{
	for (auto filter : filtre_)
	{
		delete filter;
	}
}





 



