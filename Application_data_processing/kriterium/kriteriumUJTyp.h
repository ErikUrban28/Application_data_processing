#pragma once
#include "kriteriumUJ.h"

class KriteriumUJTyp : public KriteriumUJ<TypUzemnaJednotka>
{
	public:
	TypUzemnaJednotka ohodnot(UzemnaJednotka* ujednotka) override;
};

inline TypUzemnaJednotka KriteriumUJTyp::ohodnot(UzemnaJednotka* ujednotka)
{
	return ujednotka->getTyp();
}

