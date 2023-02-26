#pragma once

#include "kriteriumUJ.h"
#include "../uzemnaJednotka/uzemnaJednotka.h"
class KriteriumUJVzdelaniePodiel : public KriteriumUJ<double>
{
private:
	Vzdelanie vzdelanie_;
public:
	explicit KriteriumUJVzdelaniePodiel(const Vzdelanie vzdelanie)
		: vzdelanie_{ vzdelanie }
	{
	}

	double ohodnot( UzemnaJednotka* ujednotka) override;
};

inline double KriteriumUJVzdelaniePodiel::ohodnot(UzemnaJednotka* ujednotka)
{
	const int delenec{ 100 * ujednotka->pocetObyvatelovSoVzdelanim(vzdelanie_) };
	const int delitel{ujednotka->getPocetObyvatelov()};
	return 1.0 * delenec / delitel;
}

