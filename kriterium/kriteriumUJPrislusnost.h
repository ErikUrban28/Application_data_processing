#pragma once
#pragma once
#include "kriteriumUJ.h"
#include "../uzemnaJednotka/uzemnaJednotka.h"
#include <string>

class KriteriumUJPrislusnost : public KriteriumUJ<bool>
{
private:
	UzemnaJednotka* vyssiCelok_;
public:
	KriteriumUJPrislusnost(UzemnaJednotka* vyssi_celok)
		: vyssiCelok_{vyssi_celok}
	{
	}

	bool ohodnot(UzemnaJednotka* ujednotka) override;
};

inline bool KriteriumUJPrislusnost::ohodnot(UzemnaJednotka* ujednotka)
{
	return ujednotka->patriDoVyssiehoCelku(vyssiCelok_);
}
