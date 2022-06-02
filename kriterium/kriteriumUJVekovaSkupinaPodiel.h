#include "kriteriumUJ.h"
#include "../uzemnaJednotka/uzemnaJednotka.h"
class KriteriumUJVekovaSkupinaPodiel : public KriteriumUJ<double>
{
private:
	EVS evs_;
public:
	explicit KriteriumUJVekovaSkupinaPodiel(const EVS evs)
		: evs_{ evs }
	{
	}

	double ohodnot( UzemnaJednotka* ujednotka) override;
};

inline double KriteriumUJVekovaSkupinaPodiel::ohodnot(UzemnaJednotka* ujednotka)
{
	const int delenec{ 100 * ujednotka->pocetObyvatelovEVS(evs_) };
	const int delitel{ujednotka->getPocetObyvatelov()};
	return 1.0 * delenec / delitel;
}

