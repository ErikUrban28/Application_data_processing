#pragma once
# include "filterInterval.h"
#include "../kriterium/kriteriumUJVzdelaniePocet.h"
class FilterUJVzdelaniePocet : public FilterInterval<UzemnaJednotka*,int>
{
public:
	FilterUJVzdelaniePocet(Vzdelanie vzdelanie,int min, int max)
		: FilterInterval(new KriteriumUJVzdelaniePocet(vzdelanie),min,max)
	{
	}
};