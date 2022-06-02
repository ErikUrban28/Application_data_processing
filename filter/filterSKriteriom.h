#pragma once
#include "../kriterium/kriterium.h"
#include "Filter.h"
template <typename O, typename T>
class FilterSKriteriom : public Filter<O>
{
	Kriterium<O,T>* kriterium_ ;
public:
	 FilterSKriteriom(Kriterium<O, T>* kriterium)
		: kriterium_{kriterium}
	{
	}

protected:
	virtual bool passFilter(T hodnota) = 0;
public:
	bool pass(O obj) override;
	~FilterSKriteriom() override;
};


template<typename O, typename T>
inline bool FilterSKriteriom<O, T>::pass(O obj) 
{
	return passFilter(kriterium_->ohodnot(obj));
}

template <typename O, typename T>
FilterSKriteriom<O, T>::~FilterSKriteriom()
{
	delete kriterium_;
	kriterium_ = nullptr;
}
