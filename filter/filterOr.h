#pragma once
#include "zlozenyFilter.h"
template <typename O>
class Filter_OR : public ZlozenyFilter<O>
{
public:
	bool pass(O obj) override;
	void vyfiltruj(structures::SortedSequenceTable<std::string, UzemnaJednotka*>& table,
		structures::UnsortedSequenceTable<std::string, UzemnaJednotka*>& newTable) override;
	Filter_OR(Filter_OR& other);
	Filter_OR();
};

template<typename O>
inline bool Filter_OR<O>::pass(O obj)
{
	for(auto filter : ZlozenyFilter<O>::filtre_)
	{
		if(filter->pass(obj) || ZlozenyFilter<O>::filtre_.size() == 0)
		{
			return true;
		}
	}
	return false;
}

template <typename O>
void Filter_OR<O>::vyfiltruj(structures::SortedSequenceTable<std::string, UzemnaJednotka*>& table,
	structures::UnsortedSequenceTable<std::string, UzemnaJednotka*>& newTable)
{
	for (const auto element : table)
	{
		if (pass(element->accessData()))
		{
			newTable.insert(element->getKey(), element->accessData());
		}

	}
	ZlozenyFilter<O>::filtre_.clear();
}

template <typename O>
Filter_OR<O>::Filter_OR(Filter_OR& other)
{
	ZlozenyFilter<O>::filtre_.clear();
	ZlozenyFilter<O>::filtre_.assign(other.filtre_);
}

template <typename O>
Filter_OR<O>::Filter_OR()
{
}
