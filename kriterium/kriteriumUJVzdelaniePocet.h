#pragma once
#include "kriteriumUJ.h"
#include "../uzemnaJednotka/uzemnaJednotka.h"
class KriteriumUJVzdelaniePocet : public KriteriumUJ<int>
{
private:
	Vzdelanie vzdelanie_;
public:
	KriteriumUJVzdelaniePocet(const Vzdelanie vzdelanie)
		: vzdelanie_{vzdelanie}
	{
	}

	int ohodnot(UzemnaJednotka* ujednotka) override;
};

inline int KriteriumUJVzdelaniePocet::ohodnot(UzemnaJednotka* ujednotka)
{
	
	return ujednotka->pocetObyvatelovSoVzdelanim(vzdelanie_);
}

