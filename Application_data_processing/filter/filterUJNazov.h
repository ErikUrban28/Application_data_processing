#pragma once
# include "filterHodnota.h"
#include "../kriterium/kriteriumUJNazov.h"
class FilterUJNazov : public FilterHodnota<UzemnaJednotka*,std::string>
{
public:
	FilterUJNazov(std::string nazov)
		: FilterHodnota(new KriteriumUJNazov,nazov)
	{
	}
};