#pragma once
#include "FilterSKriteriom.h"
template <typename O, typename  T>
class FilterInterval : public FilterSKriteriom<O, T>
{
	T min_;
	T max_;
public:
	FilterInterval(Kriterium<O, T>* kriterium,T min,T max)
		: FilterSKriteriom<O, T>{kriterium},
		  min_{min},
		  max_{max}
	{
	}
protected:
	bool passFilter(T hodnota) override;
};

template<typename O, typename T>
inline bool FilterInterval<O, T>::passFilter(T hodnota)
{
	return hodnota >= min_ && hodnota <= max_;
}
