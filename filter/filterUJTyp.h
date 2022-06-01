#pragma once
# include "filterHodnota.h"
#include "../kriterium/kriteriumUJTyp.h"
class FilterUJTyp : public FilterHodnota<UzemnaJednotka*,TypUzemnaJednotka>
{
public:
	FilterUJTyp(TypUzemnaJednotka typ)
		: FilterHodnota(new KriteriumUJTyp(),typ)
	{
	}
};