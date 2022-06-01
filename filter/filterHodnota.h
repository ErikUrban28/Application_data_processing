#pragma once
#include "FilterSKriteriom.h"
template <typename O, typename T>
class FilterHodnota : public FilterSKriteriom<O,T>
{
	T hodnota_;
public:
	FilterHodnota(Kriterium<O, T>* kriterium, T hodnota)
		: FilterSKriteriom<O, T>{kriterium},
		  hodnota_{hodnota}
	{
	}
protected:
	bool passFilter(T hodnota) override;
};

template<typename O, typename  T>
inline bool FilterHodnota<O,T>::passFilter(T hodnota)
{
	return hodnota_ == hodnota;
}
