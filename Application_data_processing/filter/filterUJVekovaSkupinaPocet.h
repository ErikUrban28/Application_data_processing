#pragma once
# include "filterInterval.h"
#include "../kriterium/kriteriumUJVekovaSkupinaPocet.h"
class FilterUJVekovaSkupinaPocet : public FilterInterval<UzemnaJednotka*,int>
{
public:
	FilterUJVekovaSkupinaPocet(EVS evs, int min,int max)
		: FilterInterval(new KriteriumVekovaSkupinaPocet(evs),min,max)
	{
	}
};