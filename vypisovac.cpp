
#include "vypisovac.h"
#include "kriterium/kriteriumUJNazov.h"
#include "kriterium/kriteriumUJTyp.h"
#include "kriterium/kriteriumUJVzdelaniePocet.h"
#include "kriterium/kriteriumUJVzdelaniePodiel.h"
#include "uzemnaJednotka/typUzemnaJednotka.h"

TypUzemnaJednotka Vypisovac::stringToTyp(std::string& cislo)
{
	if (cislo == "0")
	{
		return   TypUzemnaJednotka::STAT;
	}
	else if (cislo == "1")
	{
		return TypUzemnaJednotka::KRAJ;
	}
	else if (cislo == "2")
	{
		return TypUzemnaJednotka::OKRES;
	}
	else if (cislo == "3")
	{
		return  TypUzemnaJednotka::OBEC;
	}
	else
	{
		std::cout << "\nZadal si nespravny vstup, Typ sa nastavil na Obec\n";
		cislo = "0";
		return TypUzemnaJednotka::OBEC;
	}
}

void Vypisovac::vypisTypyUJ()
{
	std::cout << "\nZadajte typ uzemnej jednotky:\n "
		<< "\t0 pre STAT\n"
		<< "\t1 pre KRAJ\n"
		<< "\t2 pre OKRES\n"
		<< "\t3 pre OBEC\n";
}

void Vypisovac::vypisTabulkuPodlaTypu(structures::SortedSequenceTable<std::string,
	UzemnaJednotka*>& tab, TypUzemnaJednotka typ)
{
	KriteriumUJNazov kn;
	const int kodsize = typToCodeSize(typ);
	for (const auto element : tab)
	{
		if (static_cast<int>(element->getKey().size()) == kodsize) {
			std::cout << kn.ohodnot(element->accessData()) << '\n';
		}
	}
}

void Vypisovac::vypisBodoveUJ(UzemnaJednotka* uj, bool vypisKritVzPocet, bool vypisKritVzPodiel)
{
	KriteriumUJNazov kn;
	KriteriumUJTyp kt;

	std::cout << "\nVypis\n\n";
	std::cout << "\nNazov hladanej UJ: " << kn.ohodnot(uj) << '\n';
	std::cout << "Typ hladanej UJ: " << typToString(kt.ohodnot(uj)) << '\n' << '\n';
	vypisKriteriaVsetkoVzdelanie(uj, vypisKritVzPocet, vypisKritVzPodiel);
	while (uj->getNadriadenaUJ())
	{
		uj = uj->getNadriadenaUJ();
		std::cout << "\nNazov nadradenej UJ: " << kn.ohodnot(uj) << '\n';
		std::cout << "Typ nadradenej UJ: " << typToString(kt.ohodnot(uj)) << '\n';

	}
	std::cout << "\nKoniec Vypisu\n\n";

}

void Vypisovac::vypisFilterUJ(UzemnaJednotka* uj, bool vypisKritVzPocet, bool vypisKritVzPodiel, Vzdelanie vzdelaniePocet, Vzdelanie vzdelaniePodiel)
{
	KriteriumUJNazov kn;
	KriteriumUJTyp kt;

	std::cout << "\nVypis\n\n";
	std::cout << "\nNazov hladanej UJ: " << kn.ohodnot(uj) << '\n';
	std::cout << "Typ hladanej UJ: " << typToString(kt.ohodnot(uj)) << '\n' << '\n';
	vypisKonkretneVzdelanie(uj,vypisKritVzPocet,vypisKritVzPodiel,vzdelaniePocet,vzdelaniePodiel);
	while (uj->getNadriadenaUJ())
	{
		uj = uj->getNadriadenaUJ();
		std::cout << "\nNazov nadradenej UJ: " << kn.ohodnot(uj) << '\n';
		std::cout << "Typ nadradenej UJ: " << typToString(kt.ohodnot(uj)) << '\n';

	}
	std::cout << "\nKoniec Vypisu\n\n";
}

std::string Vypisovac::typToString(TypUzemnaJednotka typ)
{
	if (typ == TypUzemnaJednotka::STAT)
	{
		return "Stat";
	}
	else if (typ == TypUzemnaJednotka::KRAJ) {
		return  "Kraj";
	}
	else if (typ == TypUzemnaJednotka::OKRES) {
		return  "Okres";
	}
	else
	{
		return "Obec";
	}
}



void Vypisovac::vypisKriteriaVsetkoVzdelanie(UzemnaJednotka* uzemna, bool vypisKritVzPocet, bool vypisKritVzPodiel)
{
	if (vypisKritVzPocet)
	{

		std::cout << "\nVzdelania UJ Pocet: \n";
		for (int i{}; i < 8; ++i)
		{
			switch (i)
			{
			case 0: std::cout << "bez_ukonceneho_vzdelania: ";
				break;
			case 1: std::cout << "zakladne: ";
				break;
			case 2: std::cout << "ucnovske: ";
				break;
			case 3: std::cout << "stredne: ";
				break;
			case 4: std::cout << "vyssie: ";
				break;
			case 5: std::cout << "vysokoskolske: ";
				break;
			case 6: std::cout << "bez_vzdelania: ";
				break;
			case 7: std::cout << "nezistene: ";
				break;
			default:;
			}
			KriteriumUJVzdelaniePocet kp{ static_cast<Vzdelanie>(i) };
			std::cout << kp.ohodnot(uzemna) << " ludi\n";
		}
	}
	if (vypisKritVzPodiel)
	{
		std::cout << "\nVzdelania UJ Podiel: \n";
		for (int i{}; i < 8; ++i)
		{
			switch (i)
			{
			case 0: std::cout << "bez_ukonceneho_vzdelania: ";
				break;
			case 1: std::cout << "zakladne: ";
				break;
			case 2: std::cout << "ucnovske: ";
				break;
			case 3: std::cout << "stredne: ";
				break;
			case 4: std::cout << "vyssie: ";
				break;
			case 5: std::cout << "vysokoskolske: ";
				break;
			case 6: std::cout << "bez_vzdelania: ";
				break;
			case 7: std::cout << "nezistene: ";
				break;
			default:;
			}
			KriteriumUJVzdelaniePodiel kp{ static_cast<Vzdelanie>(i) };
			std::cout << kp.ohodnot(uzemna) << "%\n";
		}
	}
}

int Vypisovac::typToCodeSize(TypUzemnaJednotka typ)
{
	switch (typ)
	{
	case TypUzemnaJednotka::OBEC: return 12;
	case TypUzemnaJednotka::OKRES:  return 6;
	case TypUzemnaJednotka::KRAJ: return 5;
	case TypUzemnaJednotka::STAT: return 2;
	}
}

void Vypisovac::vypisCeluTabulku(structures::SortedSequenceTable<std::string, UzemnaJednotka*>& tab)
{
	KriteriumUJNazov kn;
	std::cout << "Vypis\n\n";
	for (const auto element : tab)
	{
		std::cout << kn.ohodnot(element->accessData()) << '\n';
	}
	std::cout << "\nKoniec Vypisu\n\n";
}

void Vypisovac::vypisVsetkyOperacie()
{
	std::cout << "\nStlacte pre vykonavanie operacie :\n "
		<< "\t0 pre Bodove vyhladavanie\n"
		<< "\t1 pre Filtrovanie\n"
		<< "\t2 pre Triedenie\n"
		<< "\t3 pre Koniec\n";
}

void Vypisovac::vypisCisloVsetkyFiltre()
{
	std::cout << "\nVyber si filtre:\n "
		<< "\t0 Vyber FilterNazov\n"
		<< "\t1 Vyber FilterTyp\n"
		<< "\t2 Vyber FilterPrislusnost\n"
		<< "\t3 Vyber FilterVzdelaniePocet\n"
		<< "\t4 Vyber FilterVzdelaniePodiel\n"
		<< "\t5 Pridat do OR Filtra\n"
		<< "\t6 Pridat do AND Filtra\n"
		<< "\t7 Uz nevyberat\n";
}

void Vypisovac::vypisCisloVzdelania()
{
	std::cout << "\nVyber Vzdelanie: \n";
	std::cout << "Stlac:\n"
		<< "\t0 pre bez_ukonceneho_vzdelania\n"
		<< "\t1 pre zakladne\n"
		<< "\t2 pre ucnovske\n"
		<< "\t3 pre stredne\n"
		<< "\t4 pre vyssie\n"
		<< "\t5 pre vysokoskolske\n"
		<< "\t6 pre bez_vzdelania\n"
		<< "\t7 pre nezistene\n";
}

void Vypisovac::vyhodnotParametreVzdelaniePocet(const std::string& vzdelanie, std::string& min, std::string& max, int& ivzdelanie, int& imin, int& imax)
{
	if (min.empty() || min == "NEKONECNO")
	{
		min = "0";
	}
	if (max.empty()) {
		max = std::to_string(INT_MAX);
	}
	try {
		ivzdelanie = std::stoi(vzdelanie);
		imin = std::stoi(min);
		imax = std::stoi(max);
	}
	catch (...) {
		std::cout << "Nedalo sa konvertovat niektore cislo"
			<< " filter bude mat ako parameter vzdelanie - bez_ukonceneho_vzdelania "
			<< "a interval bude 0 az Nekonecno";
		ivzdelanie = 0;
		imin = 0;
		imax = INT_MAX;
	}
}

void Vypisovac::vyhodnotParametreVzdelaniePodiel(const std::string& vzdelanie, std::string& min, std::string& max, int& ivzdelanie, double& dmin, double& dmax)
{
	if (min.empty() || min == "NEKONECNO")
	{
		min = "0";
	}
	if (max.empty()) {
		max = std::to_string(DBL_MAX);
	}
	try {
		ivzdelanie = std::stoi(vzdelanie);
		dmin = std::stod(min);
		dmax = std::stod(max);
	}
	catch (...) {
		std::cout << "Nedalo sa konvertovat niektore cislo"
			<< " filter bude mat ako parameter vzdelanie - bez_ukonceneho_vzdelania "
			<< "a interval bude 0 az Nekonecno";
		ivzdelanie = 0;
		dmin = 0.0;
		dmax = DBL_MAX;
	}
}

void Vypisovac::vypisKonkretneVzdelanie(UzemnaJednotka* uzemna, bool vypisKritVzPocet,
	bool vypisKritVzPodiel, Vzdelanie vzdelaniePocet, Vzdelanie vzdelaniePodiel)
{
	if (vypisKritVzPocet)
	{

		switch (vzdelaniePocet)
		{
		case bez_ukonceneho_vzdelania: std::cout << "bez_ukonceneho_vzdelania: ";
			break;
		case zakladne: std::cout << "zakladne: ";
			break;
		case ucnovske: std::cout << "ucnovske: ";
			break;
		case stredne: std::cout << "stredne: ";
			break;
		case vyssie: std::cout << "vyssie: ";
			break;
		case vysokoskolske: std::cout << "vysokoskolske: ";
			break;
		case bez_vzdelania: std::cout << "bez_vzdelania: ";
			break;
		case nezistene: std::cout << "nezistene: ";
			break;
		default:;
		}
		KriteriumUJVzdelaniePocet kp{ vzdelaniePocet };
		std::cout << kp.ohodnot(uzemna) << " ludi\n";
	}
	if (vypisKritVzPodiel)
	{
		switch (vzdelaniePodiel)
		{
		case bez_ukonceneho_vzdelania: std::cout << "bez_ukonceneho_vzdelania: ";
			break;
		case zakladne: std::cout << "zakladne: ";
			break;
		case ucnovske: std::cout << "ucnovske: ";
			break;
		case stredne: std::cout << "stredne: ";
			break;
		case vyssie: std::cout << "vyssie: ";
			break;
		case vysokoskolske: std::cout << "vysokoskolske: ";
			break;
		case bez_vzdelania: std::cout << "bez_vzdelania: ";
			break;
		case nezistene: std::cout << "nezistene: ";
			break;
		default:;

		}

		KriteriumUJVzdelaniePodiel kp{ vzdelaniePodiel };
		std::cout << kp.ohodnot(uzemna) << "%\n";
	}
}

