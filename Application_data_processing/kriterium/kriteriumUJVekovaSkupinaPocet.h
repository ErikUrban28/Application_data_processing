#pragma once
#include "kriteriumUJ.h"
#include "../uzemnaJednotka/uzemnaJednotka.h"
class KriteriumVekovaSkupinaPocet : public KriteriumUJ<int>
{
private:
	EVS evs_;
public:
	explicit KriteriumVekovaSkupinaPocet(const EVS evs)
		: evs_{evs}
	{
	}
	int ohodnot(UzemnaJednotka* ujednotka) override;
};

inline int KriteriumVekovaSkupinaPocet::ohodnot(UzemnaJednotka* ujednotka)
{
	
	return ujednotka->pocetObyvatelovEVS(evs_);
}

