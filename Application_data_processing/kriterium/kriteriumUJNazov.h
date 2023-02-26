#pragma once
#include "kriteriumUJ.h"
#include "../uzemnaJednotka/uzemnaJednotka.h"
#include <string>

class KriteriumUJNazov : public KriteriumUJ<std::string>
{
public:
	std::string ohodnot(UzemnaJednotka* ujednotka) override;
};

inline std::string KriteriumUJNazov::ohodnot(UzemnaJednotka* ujednotka)
{
	return ujednotka->getNazov();
}
