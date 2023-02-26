
#include "vypisovac.h"

#include "uzemnaJednotka/typUzemnaJednotka.h"
#include "kriterium/kriteriumUJNazov.h"
#include "kriterium/kriteriumUJTyp.h"

#include "kriterium/kriteriumUJVzdelaniePocet.h"
#include "kriterium/kriteriumUJVzdelaniePodiel.h"

#include "kriterium/kriteriumUJVekovaSkupinaPocet.h"
#include "kriterium/kriteriumUJVekovaSkupinaPodiel.h"



TypUzemnaJednotka Vypisovac::stringToTyp(std::string& vstup)
{
	if (vstup == "0")
	{
		return   TypUzemnaJednotka::STAT;
	}
	else if (vstup == "1")
	{
		return TypUzemnaJednotka::KRAJ;
	}
	else if (vstup == "2")
	{
		return TypUzemnaJednotka::OKRES;
	}
	else if (vstup == "3")
	{
		return  TypUzemnaJednotka::OBEC;
	}
	else
	{
		std::cout << "\nZadal si nespravny vstup, Typ sa nastavil na Obec\n";
		vstup = "0";
		return TypUzemnaJednotka::OBEC;
	}
}

void Vypisovac::vypisTypyUJ()
{
	std::cout << "\nZadajte typ uzemnej jednotky:\n "
		<< "\t0: pre STAT\n"
		<< "\t1: pre KRAJ\n"
		<< "\t2: pre OKRES\n"
		<< "\t3: pre OBEC\n";
}

void Vypisovac::trieditAko()
{
	std::cout << "Triedit\n"
					<< "0: pre zostupne\n"
					<< "1: pre vzostupne\n\n";
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

void Vypisovac::vypisVsetkyNazvy(structures::SortedSequenceTable<std::string, UzemnaJednotka*>& tab)
{
	KriteriumUJNazov kn;
	std::cout << "Vypis\n";
	for (const auto element : tab)
	{
		std::cout << kn.ohodnot(element->accessData()) << '\n';
	}
	std::cout << "\nKoniec Vypisu\n\n";
}

void Vypisovac::vypisVsetkyOperacie()
{
	std::cout << "\nStlacte pre vykonavanie operacie :\n "
		<< "\t0: pre Bodove vyhladavanie\n"
		<< "\t1: pre Filtrovanie\n"
		<< "\t2: pre Triedenie\n"
		<< "\t3: pre Koniec\n";
}

void Vypisovac::vypisCisloVsetkyFiltre()
{
	std::cout << "\nVyber si filtre:\n "
		<< "\t0: Vyber FilterNazov\n"
		<< "\t1: Vyber FilterTyp\n"
		<< "\t2: Vyber FilterPrislusnost\n"
		<< "\t3: Vyber FilterVzdelaniePocet\n"
		<< "\t4: Vyber FilterVzdelaniePodiel\n"
		<< "\t5: Vyber FilterVekovaSkupinaPocet\n"
		<< "\t6: Vyber FilterVekovaSkupinaPodiel\n"
		<< "\t7: Pridat do OR Filtra\n"
		<< "\t8: Pridat do AND Filtra\n"
		<< "\t9: Uz nevyberat\n";
}

void Vypisovac::vypisCisloVzdelania()
{
	std::cout << "\nVyber Vzdelanie: \n"
		<< "\t0: pre bez_ukonceneho_vzdelania\n"
		<< "\t1: pre zakladne\n"
		<< "\t2: pre ucnovske\n"
		<< "\t3: pre stredne\n"
		<< "\t4: pre vyssie\n"
		<< "\t5: pre vysokoskolske\n"
		<< "\t6: pre bez_vzdelania\n"
		<< "\t7: pre nezistene\n";
}

void Vypisovac::vypisCisloEVS()
{
	std::cout << "\nVyber EVS: \n"
		<< "\t0: pre predproduktivni\n"
		<< "\t1: pre produktivni\n"
		<< "\t2: pre poproduktivni\n";
}

void Vypisovac::vyhodnotParametreVzdelaniePocet(const std::string& vzdelanie, std::string& min, std::string& max,
	int& ivzdelanie, int& imin, int& imax)
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
		std::cout << "\nNedalo sa konvertovat niektore cislo"
			<< " filter bude mat ako parameter vzdelanie - bez_ukonceneho_vzdelania "
			<< "a interval bude 0 az Nekonecno\n";
		ivzdelanie = 0;
		imin = 0;
		imax = INT_MAX;
	}
}

void Vypisovac::vyhodnotParametreVzdelaniePodiel(const std::string& vzdelanie, std::string& min, std::string& max,
	int& ivzdelanie, double& dmin, double& dmax)
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
		std::cout << "\nNedalo sa konvertovat niektore cislo"
			<< " filter bude mat ako parameter vzdelanie - bez_ukonceneho_vzdelania "
			<< "a interval bude 0 az Nekonecno\n";
		ivzdelanie = 0;
		dmin = 0.0;
		dmax = DBL_MAX;
	}
}

void Vypisovac::vyhodnotParametreEVSPocet(const std::string& evs, std::string& min, std::string& max,
	int& ievs, int& imin, int& imax)
{
	if (min.empty() || min == "NEKONECNO")
	{
		min = "0";
	}
	if (max.empty()) {
		max = std::to_string(INT_MAX);
	}
	try {
		ievs = std::stoi(evs);
		imin = std::stoi(min);
		imax = std::stoi(max);
	}
	catch (...) {
		std::cout << "\nNedalo sa konvertovat niektore cislo"
			<< " filter bude mat ako parameter evs - predproduktivni "
			<< "a interval bude 0 az Nekonecno\n";
		ievs = 0;
		imin = 0;
		imax = INT_MAX;
	}
}

void Vypisovac::vyhodnotParametreEVSPodiel(const std::string& evs, std::string& min, std::string& max,
	int& devs, double& dmin, double& dmax)
{
	if (min.empty() || min == "NEKONECNO")
	{
		min = "0";
	}
	if (max.empty()) {
		max = std::to_string(DBL_MAX);
	}
	try {
		devs = std::stoi(evs);
		dmin = std::stod(min);
		dmax = std::stod(max);
	}
	catch (...) {
		std::cout << "\nNedalo sa konvertovat niektore cislo"
			<< " filter bude mat ako parameter evs - predproduktivni "
			<< "a interval bude 0 az Nekonecno\n";
		devs = 0;
		dmin = 0.0;
		dmax = DBL_MAX;
	}
}

void Vypisovac::vypisBodoveUJ(UzemnaJednotka* uj)
{
	KriteriumUJNazov kn;
	KriteriumUJTyp kt;
	std::cout << "\n\nVypis UJ\n";
	std::cout << "\nNazov UJ: " << kn.ohodnot(uj) << '\n';
	std::cout << "Typ UJ: " << typToString(kt.ohodnot(uj)) << '\n';
	vypisKritVzdelaniePocetVsetko(uj);
	vypisKritVekovaSkupinaPocetVsetko(uj);
	while (uj->getNadriadenaUJ())
	{
		uj = uj->getNadriadenaUJ();
		std::cout << "\nNazov nadradenej UJ: " << kn.ohodnot(uj) << '\n';
		std::cout << "Typ nadradenej UJ: " << typToString(kt.ohodnot(uj)) << '\n';

	}
	std::cout << "\nKoniec Vypisu UJ\n\n";
}

void Vypisovac::vypisKritVzdelaniePocetVsetko(UzemnaJednotka* uzemna)
{
	std::cout << "\nVypis UJ Vzdelania Pocet: \n\n";
	for (int i{}; i < 8; ++i)
	{
		switch (i)
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
		KriteriumUJVzdelaniePocet kp{ static_cast<Vzdelanie>(i) };
		std::cout << kp.ohodnot(uzemna) << " ludi\n";

	}
	std::cout << "\nKoniec Vypisu UJ Vzdelanie Pocet\n";
}

void Vypisovac::vypisKritVekovaSkupinaPocetVsetko(UzemnaJednotka* uzemna)
{

	std::cout << "\nVypis UJ VekovaSkupina Pocet : \n\n";
	for (int i{}; i < 3; ++i)
	{
		switch (i)
		{
		case predproduktivni: std::cout << "predproduktivni:  ";
			break;
		case produktivni: std::cout << "produktivny: ";
			break;
		case poproduktivni: std::cout << "poproduktivni: ";
			break;
		default:;
		}
		KriteriumVekovaSkupinaPocet kp(static_cast<EVS>(i));
		std::cout << kp.ohodnot(uzemna) << " ludi\n";

	}
	std::cout << "\nKoniec UJ Vekova Skupina Pocet\n";

}

void Vypisovac::vypisFilterUJBezFiltra(UzemnaJednotka* uj)
{
	KriteriumUJNazov kn;
	KriteriumUJTyp kt;

	std::cout << "\n\nNazov UJ: " << kn.ohodnot(uj) << '\n';
	std::cout << "Typ UJ: " << typToString(kt.ohodnot(uj)) << "\n\n";
	while (uj->getNadriadenaUJ())
	{
		uj = uj->getNadriadenaUJ();
		std::cout << "\nNazov nadradenej UJ: " << kn.ohodnot(uj) << '\n';
		std::cout << "Typ nadradenej UJ: " << typToString(kt.ohodnot(uj)) << '\n';

	}
	std::cout << "\nKoniec Vypisu UJ\n\n";
}

void Vypisovac::vypisFilterUJVzPocet(UzemnaJednotka* uj, Vzdelanie vzdelaniePocet)
{
	std::cout << "\nVzdelania UJ Pocet: \n";
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
	std::cout << kp.ohodnot(uj) << " ludi\n";
	std::cout << "\nKoniec Vypisu Vzdelanie Pocet\n\n";
}

void Vypisovac::vypisFilterUJVzPodiel(UzemnaJednotka* uj, Vzdelanie vzdelaniePodiel)
{
	std::cout << "\nVzdelania UJ Podiel: \n";
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
	std::cout << kp.ohodnot(uj) << "%\n";

	std::cout << "\nKoniec Vypisu Vzdelanie Podiel\n\n";
}

void Vypisovac::vypisFilterUJEVSPocet(UzemnaJednotka* uj, EVS evsPocet)
{

	std::cout << "\nVypis UJ VekovaSkupina Pocet : \n\n";
	switch (evsPocet)
	{
	case predproduktivni: std::cout << "predproduktivni:  ";
		break;
	case produktivni: std::cout << "produktivny: ";
		break;
	case poproduktivni: std::cout << "poproduktivni: ";
		break;
	default:;
	}
	KriteriumVekovaSkupinaPocet kp((evsPocet));
	std::cout << kp.ohodnot(uj) << " ludi\n";

	std::cout << "\nKoniec UJ Vekova Skupina Pocet\n";
}

void Vypisovac::vypisFilterUJEVSPodiel(UzemnaJednotka* uj, EVS evsPodiel)
{
	std::cout << "\nVypis UJ VekovaSkupina Podiel : \n\n";
	switch (evsPodiel)
	{
	case predproduktivni: std::cout << "predproduktivni:  ";
		break;
	case produktivni: std::cout << "produktivny: ";
		break;
	case poproduktivni: std::cout << "poproduktivni: ";
		break;
	default:;
	}
	KriteriumUJVekovaSkupinaPodiel kp((evsPodiel));
	std::cout << kp.ohodnot(uj) << " ludi\n";

	std::cout << "\nKoniec UJ Vekova Skupina Podiel\n";
}



void Vypisovac::vypisNazovATyp(UzemnaJednotka* uj, bool vypisTyp)
{
	KriteriumUJNazov kn;
	KriteriumUJTyp kt;
	std::cout << "\n\nZaciatok vypisu UJ: \n";
	std::cout << "\nNazov UJ: " << kn.ohodnot(uj) << '\n';
	if (vypisTyp)
		std::cout << "Typ UJ: " << typToString(kt.ohodnot(uj)) << "\n\n";
}

void Vypisovac::vypisNadradeneUJ(UzemnaJednotka* uj, bool typ)
{
	KriteriumUJNazov kn;
	KriteriumUJTyp kt;
	while (uj->getNadriadenaUJ())
	{
		uj = uj->getNadriadenaUJ();
		std::cout << "\nNazov nadradenej UJ: " << kn.ohodnot(uj) << '\n';
		if(typ){
		std::cout << "Typ nadradenej UJ: " << typToString(kt.ohodnot(uj)) << '\n';
		}
	}
}


