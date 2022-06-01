#pragma once
# include "filterInterval.h"
#include "../kriterium/kriteriumUJVzdelaniePocet.h"
#include "../kriterium/kriteriumUJVzdelaniePodiel.h"
class FilterUJVzdelaniePodiel : public FilterInterval<UzemnaJednotka*,double>
{
public:
	FilterUJVzdelaniePodiel(Vzdelanie vzdelanie,double min, double max)
		: FilterInterval(new KriteriumUJVzdelaniePodiel(vzdelanie),min,max)
	{
	}
};