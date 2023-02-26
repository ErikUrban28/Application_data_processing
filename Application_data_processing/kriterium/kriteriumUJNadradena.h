#pragma once
#pragma once
#include "kriteriumUJ.h"
#include "../uzemnaJednotka/uzemnaJednotka.h"

class KriteriumUJNadradena : public KriteriumUJ<UzemnaJednotka*>
{
public:
	UzemnaJednotka* ohodnot(UzemnaJednotka* ujednotka) override;
};

inline UzemnaJednotka* KriteriumUJNadradena::ohodnot(UzemnaJednotka* ujednotka)
{
	return ujednotka->getNadriadenaUJ();
}
