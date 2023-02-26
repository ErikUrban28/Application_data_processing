#pragma once
# include "filterInterval.h"
#include "../kriterium/kriteriumUJVekovaSkupinaPodiel.h"
class FilterUJVekovaSkupinaPodiel : public FilterInterval<UzemnaJednotka*,double>
{
public:
	FilterUJVekovaSkupinaPodiel(EVS evs,double min, double max)
		: FilterInterval(new KriteriumUJVekovaSkupinaPodiel(evs),min,max)
	{
	}
};