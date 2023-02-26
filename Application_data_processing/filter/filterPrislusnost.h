#pragma once
#include "filterHodnota.h"
# include "filterInterval.h"
#include "../kriterium/kriteriumUJPrislusnost.h"
class FilterPrislusnost : public FilterHodnota<UzemnaJednotka*,bool>
{
public:
	FilterPrislusnost(UzemnaJednotka* uzemna)
		: FilterHodnota(new KriteriumUJPrislusnost(uzemna),true)
	{
	}
};