#include "handler.h"

#include <string>

#include "loader.h"
#include "vypisovac.h"
#include "filter/filterAnd.h"
#include "filter/filterOr.h"
#include "filter/filterPrislusnost.h"
#include "filter/filterUJNazov.h"
#include "filter/filterUJTyp.h"
#include "filter/FilterUJVzdelaniePocet.h"
#include "filter/FilterUJVzdelaniePodiel.h"
#include "structures/table/sorted_sequence_table.h"
#include "uzemnaJednotka/uzemnaJednotka.h"
#include "triedenie/triedenie.h"
#include "structures/table/unsorted_sequence_table.h"



using std::cin; using std::cout; using std::string;

void Handler::spusti()
{
	Loader loader;
	Vypisovac vypisovac;
	structures::SortedSequenceTable<string, UzemnaJednotka*> tableData;
	structures::SortedSequenceTable<string, string> kodovanie;
	loader.nacitaj(tableData, kodovanie);

	bool koniec{ false };

	while (!koniec)
	{
		vypisovac.vypisVsetkyOperacie();
		string operacia;
		getline(cin, operacia);
		if (operacia == "0")
		{
			string kod;
			vypisovac.vypisTypyUJ();
			getline(cin, operacia);
			TypUzemnaJednotka typ = vypisovac.stringToTyp(operacia);
			bool najdenaUJ = false;
			string nazov;
			bool spat{};
			while (!najdenaUJ) {
				cout << "\nZadajte SPRAVNY nazov k danemu TYPU hladanej uzemnej jednotky"
					<< "\nALEBO zadajte 0 pre NASPAT"
					<< "\nALEBO 1 pre vypis vsetke UJ daneho typu:\n\n";
				getline(cin, nazov);
				if (nazov == "0")
				{
					spat = true;
					break;
				}
				else if (nazov == "1")
				{
					vypisovac.vypisTabulkuPodlaTypu(tableData, typ);
				}
				else
				{
					najdenaUJ = kodovanie.tryFind(nazov, kod);
					if (static_cast<int>(kod.size()) != vypisovac.typToCodeSize(typ))
					{
						najdenaUJ = false;
					}
				}
			}
			if (spat)
				continue;
			UzemnaJednotka* uzemnaJednotka = tableData.find(kod);
			vypisovac.vypisBodoveUJ(uzemnaJednotka, true, false);
		}
		else if (operacia == "1")
		{
			bool aplivakonyVzPodiel{};
			bool aplikovanyVzPocet{};

			cout << "\nPouzit filtre?\n"
				<< "\t0 pre Nie\n"
				<< "\t1 pre Ano\n"
				<< "\tine pre NASPAT\n";
			getline(cin, operacia);
			if (operacia == "0")
			{
				for (auto element : tableData) {
					vypisovac.vypisBodoveUJ(element->accessData(), false, false);
				}
				continue;
			}
			if (operacia != "1")
			{
				continue;
			}

			std::cout << "\nS akou logickou operaciou zacat?\n"
				<< "\t0 AND\n"
				<< "\t1 OR\n";
			getline(std::cin, operacia);
			ZlozenyFilter<UzemnaJednotka*>* filter;
			if (operacia == "0")
			{
				filter = new Filter_AND<UzemnaJednotka*>;
			}
			else if (operacia == "1")
			{
				filter = new Filter_OR<UzemnaJednotka*>;
			}
			else
			{
				std::cout << "Zly vstup, vytvaram AND Filter";

				filter = new Filter_AND<UzemnaJednotka*>;
			}
			bool fkoniec{};
			int ivzdelanie{};
			int dvzdelanie{};
			while (!fkoniec) {
				vypisovac.vypisCisloVsetkyFiltre();
				getline(cin, operacia);

				if (operacia == "0")
				{
					string meno;
					string kod;
					while (true) {
						cout << "\nZadaj nazov UJ Alebo napis 1 pre vypis vsetkeho: ";
						getline(std::cin, meno);
						if (meno == "1") {
							vypisovac.vypisCeluTabulku(tableData);
						}
						else
						{
							break;
						}
					}
					bool najdene = kodovanie.tryFind(meno, kod);
					if (najdene) {
						filter->addFilter(new FilterUJNazov(meno));
					}
					else
					{
						cout << "Zle zadany nazov";
					}
				}
				else if (operacia == "1")
				{
					vypisovac.vypisTypyUJ();
					getline(cin, operacia);
					TypUzemnaJednotka typ = vypisovac.stringToTyp(operacia);
					filter->addFilter(new FilterUJTyp(typ));
				}
				else if (operacia == "2")
				{

					string meno;
					string kod;
					bool najdene;
					cout << "\nZadaj nazov nadradenej UJ: ";
					getline(std::cin, meno);
					najdene = kodovanie.tryFind(meno, kod);
					if (najdene)
					{
						filter->addFilter(new FilterPrislusnost(tableData.find(kod)));
					}
					else
					{
						cout << "Neplatny nazov, filter sa neaplikuje...";
					}

				}
				else if (operacia == "3")
				{
					std::string vzdelanie;
					std::string min{};
					std::string max{};
					int imin;
					int imax;

					vypisovac.vypisCisloVzdelania();
					getline(std::cin, vzdelanie);
					std::cout << "Vyber dolnu hranicu intervalu: ";
					getline(std::cin, min);
					std::cout << "Vyber hornu hranicu intervalu: ";
					getline(std::cin, max);
					vypisovac.vyhodnotParametreVzdelaniePocet(vzdelanie, min, max,
						ivzdelanie, imin, imax);
					aplikovanyVzPocet = true;
					filter->addFilter(new FilterUJVzdelaniePocet(static_cast<Vzdelanie>(ivzdelanie),
						imin, imax));

				}
				else if (operacia == "4")
				{
					std::string vzdelanie;
					std::string min{};
					std::string max{};
					double dmin;
					double dmax;
					vypisovac.vypisCisloVzdelania();
					getline(std::cin, vzdelanie);
					std::cout << "Vyber dolnu hranicu intervalu: ";
					getline(std::cin, min);
					std::cout << "Vyber hornu hranicu intervalu: ";
					getline(std::cin, max);
					vypisovac.vyhodnotParametreVzdelaniePodiel(vzdelanie, min, max,
						dvzdelanie, dmin, dmax);
					aplivakonyVzPodiel = true;
					filter->addFilter(new FilterUJVzdelaniePodiel(static_cast<Vzdelanie>(dvzdelanie),
						dmin, dmax));
				}

				else if (operacia == "5")
				{
					auto pomFilter(filter);
					auto newFilter = new Filter_OR<UzemnaJednotka*>;
					newFilter->addFilter(pomFilter);
					//delete filter;
					filter = newFilter;
				}
				else if (operacia == "6")
				{
					auto pomFilter(filter);
					auto newFilter = new Filter_AND<UzemnaJednotka*>;
					newFilter->addFilter(pomFilter);
					//delete filter;
					filter = newFilter;
				}
				else if (operacia == "7")
				{
					if (filter->size() == 0)
					{
						cout << "Nevybral si ziadny filter, ale stlacil si ze ich budes pouzivat";
						continue;
					}
					fkoniec = true;
					break;
				}
				else
				{
					std::cout << "Zly vstup!";
				}
			}
			structures::UnsortedSequenceTable<std::string, UzemnaJednotka*> novaDataTab;
			filter->vyfiltruj(tableData, novaDataTab);

			for (auto element : novaDataTab) {

				vypisovac.vypisFilterUJ(element->accessData(),
					aplikovanyVzPocet, aplivakonyVzPodiel,
					static_cast<Vzdelanie>(ivzdelanie), static_cast<Vzdelanie>(dvzdelanie));
			}
			if (novaDataTab.size() == 0)
			{
				cout << "Filtrom nevyhovuje ziadna UJ\n";
			}
			//delete filter;
			//filter = nullptr;

		}
		else if (operacia == "2")
		{
			cout << "\tZacat triedit?\n";
			cout << "\t0: pre Spat\n";
			cout << "\tine pre Dalej\n";
			getline(cin, operacia);
			if (operacia == "0")
				continue;
			bool fkoniec{};
			Filter_AND<UzemnaJednotka*> triedenieFilter;
			while (!fkoniec) {
				cout << "Spolocne Filtre:\n"
					<< "\t0: Vyber FilterTyp\n"
					<< "\t1: Vyber FilterPrislusnost\n"
					<< "\t2: pre Dalej\n";
				getline(cin, operacia);

				if (operacia == "0")
				{
					vypisovac.vypisTypyUJ();
					getline(cin, operacia);
					TypUzemnaJednotka typ = vypisovac.stringToTyp(operacia);
					triedenieFilter.addFilter(new FilterUJTyp(typ));
				}
				else if (operacia == "1")
				{
					string meno;
					string kod;
					bool najdene;
					cout << "\nZadaj nazov nadradenej UJ: ";
					getline(std::cin, meno);
					najdene = kodovanie.tryFind(meno, kod);
					if (najdene)
					{
						triedenieFilter.addFilter(new FilterPrislusnost(tableData.find(kod)));
					}
					else
					{
						cout << "\nNeplatny nazov, filter sa neaplikuje...\n";
					}

				}
				else if (operacia == "2")
				{
					fkoniec = true;
				}
			}
			cout << "\t0: Tried podla nazvu\n"
				<< "\t1: Vyber FilterPocet a utried\n"
				<< "\t2: Vyber FilterPodiel a utried\n";
			getline(cin, operacia);
			int ivzdelanie{};
			if (operacia == "1")
			{
				std::string vzdelanie;
				std::string min{};
				std::string max{};
				int imin;
				int imax;

				vypisovac.vypisCisloVzdelania();
				getline(std::cin, vzdelanie);
				std::cout << "Vyber dolnu hranicu intervalu: ";
				getline(std::cin, min);
				std::cout << "Vyber hornu hranicu intervalu: ";
				getline(std::cin, max);
				vypisovac.vyhodnotParametreVzdelaniePocet(vzdelanie, min, max,
					ivzdelanie, imin, imax);
				triedenieFilter.addFilter(new FilterUJVzdelaniePocet(static_cast<Vzdelanie>(ivzdelanie),
					imin, imax));
			}
			else if (operacia == "2")
			{
				std::string vzdelanie;
				std::string min{};
				std::string max{};
				double dmin;
				double dmax;
				vypisovac.vypisCisloVzdelania();
				getline(std::cin, vzdelanie);
				std::cout << "Vyber dolnu hranicu intervalu: ";
				getline(std::cin, min);
				std::cout << "Vyber hornu hranicu intervalu: ";
				getline(std::cin, max);
				vypisovac.vyhodnotParametreVzdelaniePodiel(vzdelanie, min, max,
					ivzdelanie, dmin, dmax);
				triedenieFilter.addFilter(new FilterUJVzdelaniePodiel(static_cast<Vzdelanie>(ivzdelanie),
					dmin, dmax));
			}
			else if (operacia != "0")
			{
				cout << "Nevybral si ziadnu z moznosti, budem triedit podla nazvu\n";
			}

			structures::UnsortedSequenceTable<std::string, UzemnaJednotka*> novaDataTab;
			triedenieFilter.vyfiltruj(tableData, novaDataTab);
			if (novaDataTab.size() == 0)
			{
				cout << "Filtrom nevyhovuje ziadna UJ\n";
				continue;
			}

			KriteriumUJNazov kn;
			if (operacia == "1")
			{
				cout << "Triedit\n"
					<< "0: pre zostupne\n"
					<< "1: pre vzostupne\n\n";
				getline(cin, operacia);
				Triedenie<std::string, UzemnaJednotka*, int> triedenie;
				auto vzdelanie = static_cast<Vzdelanie>(ivzdelanie);
				KriteriumUJVzdelaniePocet kp(vzdelanie);
				if (operacia == "0") {
					triedenie.utried(novaDataTab, kp, false);
				}
				else if (operacia == "1") {
					triedenie.utried(novaDataTab, kp, true);
				}
				else
				{
					cout << "Zly vstup, triedim vzostupne\n";
					triedenie.utried(novaDataTab, kp, true);
				}
				for (auto element : novaDataTab)
				{
					cout << kn.ohodnot(element->accessData()) << "-";
					vypisovac.vypisKonkretneVzdelanie(element->accessData(), true, false, vzdelanie, vzdelanie);

				}
			}
			else if (operacia == "2")
			{
				cout << "Triedit\n"
					<< "0: pre zostupne\n"
					<< "1: pre vzostupne\n\n";
				getline(cin, operacia);
				Triedenie<std::string, UzemnaJednotka*, double> triedenie;
				auto vzdelanie = static_cast<Vzdelanie>(ivzdelanie);
				KriteriumUJVzdelaniePodiel kp(vzdelanie);
				if (operacia == "0") {
					triedenie.utried(novaDataTab, kp, false);
				}
				else if (operacia == "1") {
					triedenie.utried(novaDataTab, kp, true);
				}
				else
				{
					cout << "Zly vstup, triedim vzostupne\n";
					triedenie.utried(novaDataTab, kp, true);
				}
				for (auto element : novaDataTab)
				{
					cout << kn.ohodnot(element->accessData()) << "-";
					vypisovac.vypisKonkretneVzdelanie(element->accessData(), false, true, vzdelanie, vzdelanie);

				}
			}
			else
			{
				cout << "Triedit\n"
					<< "0: pre zostupne\n"
					<< "1: pre vzostupne\n\n";
				getline(cin, operacia);
				Triedenie<std::string, UzemnaJednotka*, std::string> triedenie;
				if (operacia == "0") {
					triedenie.utried(novaDataTab, kn, false);
				}
				else if (operacia == "1") {
					triedenie.utried(novaDataTab, kn, true);
				}
				else
				{
					cout << "Zly vstup, triedim vzostupne\n";
					triedenie.utried(novaDataTab, kn, true);
				}
				for (auto element : novaDataTab)
				{
					cout << kn.ohodnot(element->accessData()) << '\n';
				}
			}
			//delete filter;
			//filter = nullptr;
		}

		else if (operacia == "3")
		{
			std::cout << "\nZatvaram aplikaciu...\n";
			koniec = true;
			break;
		}
	}
}
