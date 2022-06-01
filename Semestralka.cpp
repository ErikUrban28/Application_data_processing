#include "handler.h"
#include "loader.h"
#include "structures/table/sorted_sequence_table.h"
#include "kriterium/kriteriumUJVzdelaniePocet.h"
#include "kriterium/kriteriumUJVzdelaniePodiel.h"
#include "kriterium/kriteriumUJNazov.h"
#include "filter/filterHodnota.h"
#include "filter/filterInterval.h"
#include "filter/filterAnd.h"
#include "filter/FilterUJVzdelaniePocet.h"
#include "filter/FilterUJVzdelaniePodiel.h"
#include "triedenie/triedenie.h"
#include "filter/filterUJNazov.h"
#include "filter/filterUJTyp.h"
#include "../Semestralka/structures/heap_monitor.h"
#include "filter/filterOr.h"

int main()
{
	Handler handler;
	handler.spusti();
	//	TODO:
	//Filter Prislusnost
	//filter vyfiltruj
	//	FilterANDnefunguje
	/*initHeapMonitor();
	Loader loader;

	UzemnaJednotka* slovensko{ new UzemnaJednotka(TypUzemnaJednotka::STAT,"SK","Slovensko") };
	structures::SortedSequenceTable<std::string, UzemnaJednotka*> kraje;
	structures::SortedSequenceTable<std::string, UzemnaJednotka*>okresy;
	structures::SortedSequenceTable<std::string, UzemnaJednotka*> obce;
	structures::SortedSequenceTable<std::string, string> kodovanie;
	loader.nacitaj(*slovensko, kraje, okresy, obce, kodovanie);
	kodovanie.insert("Slovensko", "SK");

	bool koniec{ false };


	while (!koniec) {
		while (true) 
		{
			if (koniec)
			{
				break;
			}
			std::cout << "\nStlacte pre vykonavanie operacie :\n "
				<< "\t0 pre Bodove vyhladavanie\n"
				<< "\t1 pre Filtrovanie\n"
				<< "\t2 pre Triedenie\n"
				<< "\t3 pre Koniec\n"
				<< std::endl;
			std::string operacia;
			getline(std::cin, operacia);


			if (operacia == "0") {
				while (!koniec)
				{
					UzemnaJednotka* HladanaUzemnaJednotka;
					TypUzemnaJednotka typ;
					std::string kod;
					std::string styp;
					bool najdeny = false;
					while (true) {
						std::cout << "\nZadajte typ uzemnej jednotky:\n "
							<< "\t0 pre STAT\n"
							<< "\t1 pre KRAJ\n"
							<< "\t2 pre OKRES\n"
							<< "\t3 pre OBEC\n"
							<< "\t4 pre Koniec"
							<< std::endl;

						getline(std::cin, styp);
						if (styp == "0")
						{
							typ = TypUzemnaJednotka::STAT;
							break;
						}
						else if (styp == "1")
						{
							typ = TypUzemnaJednotka::KRAJ;
							break;
						}
						else if (styp == "2")
						{
							typ = TypUzemnaJednotka::OKRES;
							break;
						}
						else if (styp == "3")
						{
							typ = TypUzemnaJednotka::OBEC;
							break;
						}
						else if (styp == "4")
						{
							koniec = true;
							break;
						}
						else
						{
							std::cout << "Zly vstup!";
						}
					}
					if (koniec) {
						break;
					}

					std::string nazov;
					while (!najdeny) {
						std::cout << "\nZadajte nazov hladanej uzemnej jednotky ALEBO zadajte Koniec pre koniec: ";

						getline(std::cin, nazov);
						if (nazov == "Koniec")
						{
							koniec = true;
							break;
						}
						najdeny = kodovanie.tryFind(nazov, kod);
					}

					if (najdeny)
					{
						switch (typ)
						{
						case TypUzemnaJednotka::STAT: {
							if (nazov == "Slovensko") {
								HladanaUzemnaJednotka = slovensko;
								std::cout << "Nazov hladanej UJ:" << HladanaUzemnaJednotka->getNazov() << '\n';
								std::string vtyp;
								if (typ == TypUzemnaJednotka::STAT)
								{
									vtyp = "Stat";
								}
								else if (typ == TypUzemnaJednotka::KRAJ) {
									vtyp = "Kraj";
								}
								else if (typ == TypUzemnaJednotka::OKRES) {
									vtyp = "Okres";
								}
								else
								{
									vtyp = "Obec";
								}
								std::cout << "Typ hladanej UJ: " << vtyp << '\n';
								std::cout << "Vzdelania UJ: \n";
								for (int i = 0; i < 8; ++i)
								{
									switch (i)
									{
									case 0: std::cout << "bez_ukonceneho_vzdelania: ";
										break;
									case 1: std::cout << "zakladne: ";
										break;
									case 2: std::cout << "ucnovske: ";
										break;
									case 3: std::cout << "vyssie: ";
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
									std::cout << HladanaUzemnaJednotka->pocetObyvatelovSoVzdelanim(static_cast<Vzdelanie>(i)) << '\n';
								}
								break;

							}
						case TypUzemnaJednotka::KRAJ: {

							if (kraje.tryFind(kod, HladanaUzemnaJednotka)) {
								std::cout << "Nazov hladanej UJ:" << HladanaUzemnaJednotka->getNazov() << '\n';
								std::string vtyp;
								if (typ == TypUzemnaJednotka::STAT)
								{
									vtyp = "Stat";
								}
								else if (typ == TypUzemnaJednotka::KRAJ) {
									vtyp = "Kraj";
								}
								else if (typ == TypUzemnaJednotka::OKRES) {
									vtyp = "Okres";
								}
								else
								{
									vtyp = "Obec";
								}
								std::cout << "Typ hladanej UJ: " << vtyp << '\n';
								std::cout << "Vzdelania UJ: \n";
								for (int i = 0; i < 8; ++i)
								{
									switch (i)
									{
									case 0: std::cout << "bez_ukonceneho_vzdelania: ";
										break;
									case 1: std::cout << "zakladne: ";
										break;
									case 2: std::cout << "ucnovske: ";
										break;
									case 3: std::cout << "vyssie: ";
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
									std::cout << HladanaUzemnaJednotka->pocetObyvatelovSoVzdelanim(static_cast<Vzdelanie>(i)) << '\n';
								}
								while (HladanaUzemnaJednotka->getNadriadenaUJ()) {

									typ = HladanaUzemnaJednotka->getNadriadenaUJ()->getTyp();
									if (typ == TypUzemnaJednotka::STAT)
									{
										vtyp = "Stat";
									}
									else if (typ == TypUzemnaJednotka::KRAJ) {
										vtyp = "Kraj";
									}
									else if (typ == TypUzemnaJednotka::OKRES) {
										vtyp = "Okres";
									}
									else
									{
										vtyp = "Obec";
									}

									std::cout << "\nNazov nadriadenej UJ: " << HladanaUzemnaJednotka->getNadriadenaUJ()->getNazov();
									std::cout << "\nTyp nadriadenej UJ: " << vtyp << '\n';
									HladanaUzemnaJednotka = HladanaUzemnaJednotka->getNadriadenaUJ();
								}
							}
						}
													break;

						}
						case TypUzemnaJednotka::OKRES: {
							if (okresy.tryFind(kod, HladanaUzemnaJednotka)) {
								std::cout << "Nazov hladanej UJ:" << HladanaUzemnaJednotka->getNazov() << '\n';
								std::string vtyp;
								if (typ == TypUzemnaJednotka::STAT)
								{
									vtyp = "Stat";
								}
								else if (typ == TypUzemnaJednotka::KRAJ) {
									vtyp = "Kraj";
								}
								else if (typ == TypUzemnaJednotka::OKRES) {
									vtyp = "Okres";
								}
								else
								{
									vtyp = "Obec";
								}
								std::cout << "Typ hladanej UJ: " << vtyp << '\n';
								std::cout << "Vzdelania UJ: \n";
								for (int i = 0; i < 8; ++i)
								{
									switch (i)
									{
									case 0: std::cout << "bez_ukonceneho_vzdelania: ";
										break;
									case 1: std::cout << "zakladne: ";
										break;
									case 2: std::cout << "ucnovske: ";
										break;
									case 3: std::cout << "vyssie: ";
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
									std::cout << HladanaUzemnaJednotka->pocetObyvatelovSoVzdelanim(static_cast<Vzdelanie>(i)) << '\n';
								}
								while (HladanaUzemnaJednotka->getNadriadenaUJ()) {

									typ = HladanaUzemnaJednotka->getNadriadenaUJ()->getTyp();
									if (typ == TypUzemnaJednotka::STAT)
									{
										vtyp = "Stat";
									}
									else if (typ == TypUzemnaJednotka::KRAJ) {
										vtyp = "Kraj";
									}
									else if (typ == TypUzemnaJednotka::OKRES) {
										vtyp = "Okres";
									}
									else
									{
										vtyp = "Obec";
									}

									std::cout << "\nNazov nadriadenej UJ: " << HladanaUzemnaJednotka->getNadriadenaUJ()->getNazov();
									std::cout << "\nTyp nadriadenej UJ: " << vtyp << '\n';
									HladanaUzemnaJednotka = HladanaUzemnaJednotka->getNadriadenaUJ();
								}
							}
							break;
						}
						case TypUzemnaJednotka::OBEC: {
							if (obce.tryFind(kod, HladanaUzemnaJednotka)) {
								std::cout << "Nazov hladanej UJ:" << HladanaUzemnaJednotka->getNazov() << '\n';
								std::string vtyp;
								if (typ == TypUzemnaJednotka::STAT)
								{
									vtyp = "Stat";
								}
								else if (typ == TypUzemnaJednotka::KRAJ) {
									vtyp = "Kraj";
								}
								else if (typ == TypUzemnaJednotka::OKRES) {
									vtyp = "Okres";
								}
								else
								{
									vtyp = "Obec";
								}
								std::cout << "Typ hladanej UJ: " << vtyp << '\n';
								std::cout << "Vzdelania UJ: \n";
								for (int i = 0; i < 8; ++i)
								{
									switch (i)
									{
									case 0: std::cout << "bez_ukonceneho_vzdelania: ";
										break;
									case 1: std::cout << "zakladne: ";
										break;
									case 2: std::cout << "ucnovske: ";
										break;
									case 3: std::cout << "vyssie: ";
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
									std::cout << HladanaUzemnaJednotka->pocetObyvatelovSoVzdelanim(static_cast<Vzdelanie>(i)) << '\n';
								}
								while (HladanaUzemnaJednotka->getNadriadenaUJ()) {

									typ = HladanaUzemnaJednotka->getNadriadenaUJ()->getTyp();
									if (typ == TypUzemnaJednotka::STAT)
									{
										vtyp = "Stat";
									}
									else if (typ == TypUzemnaJednotka::KRAJ) {
										vtyp = "Kraj";
									}
									else if (typ == TypUzemnaJednotka::OKRES) {
										vtyp = "Okres";
									}
									else
									{
										vtyp = "Obec";
									}

									std::cout << "\nNazov nadriadenej UJ: " << HladanaUzemnaJednotka->getNadriadenaUJ()->getNazov();
									std::cout << "\nTyp nadriadenej UJ: " << vtyp << '\n';
									HladanaUzemnaJednotka = HladanaUzemnaJednotka->getNadriadenaUJ();
								}
							}
							break;
						}
						default:;
						}
					}
				}
			}
			else if (operacia == "1")
			{
				std::string volba;
				std::string volbafiltra;
				std::cout << "\nPouzit filtre?\n"
					<< "\t0 pre Nie\n"
					<< "\t1 pre Ano\n"
					<< "\tine pre Koniec\n";
				getline(std::cin, volba);

				std::cout << "\nLog. Operacia?\n"
					<< "\t0 AND\n"
					<< "\t1 OR\n";
				getline(std::cin, volbafiltra);

				ZlozenyFilter<UzemnaJednotka*>* filter;
				if (volbafiltra == "0")
				{
					filter = new Filter_AND<UzemnaJednotka*>;
				}
				else if (volbafiltra == "1")
				{
					filter = new Filter_OR<UzemnaJednotka*>;
				}
				else
				{
					std::cout << "Zly vstup, vytvaram AND Filter";

					filter = new Filter_AND<UzemnaJednotka*>;
				}
				if (volba == "1") {
					bool aplivakonyVzPodiel = false;
					bool aplikovanyVzPocet = false;
					bool fkoniec = false;
					while (!fkoniec) {
						std::cout << "\nVyber si filtre:\n "
							<< "\t0 Vyber FilterNazov\n"
							<< "\t1 Vyber FilterTyp\n"
							<< "\t2 Vyber FilterPrislusnost\n"
							<< "\t3 Vyber FilterVzdelaniePocet\n"
							<< "\t4 Vyber FilterVzdelaniePodiel\n"
							<< "\t5 Uz nevyberat\n"
							<< std::endl;

						getline(std::cin, volba);


						std::string par;
						if (volba == "0")
						{
							std::cout << "\nZadaj meno: ";
							getline(std::cin, par);
							filter->addFilter(new FilterUJNazov(par));
						}


						else if (volba == "1")
						{
							TypUzemnaJednotka typ;
							std::cout << "\nStlac:\n"
								<< "\t0 pre STAT\n"
								<< "\t1 pre KRAJ\n"
								<< "\t2 pre OKRES\n"
								<< "\t3 pre OBEC\n";
							getline(std::cin, par);
							if (par == "0")
							{
								typ = TypUzemnaJednotka::STAT;
							}
							else if (par == "1")
							{
								typ = TypUzemnaJednotka::KRAJ;
							}
							else if (par == "2")
							{
								typ = TypUzemnaJednotka::OKRES;
							}
							else if (par == "3")
							{
								typ = TypUzemnaJednotka::OBEC;
							}
							else {
								std::cout << "Neplatny vstup, filter sa aplikuje pre STAT";
								typ = TypUzemnaJednotka::STAT;
							}
							filter->addFilter(new FilterUJTyp(typ));
						}
						else if (volba == "2")
						{

						}
						else if (volba == "3")
						{
							std::string vzdelanie;
							std::string min{};
							std::string max{};
							int ivzdelanie;
							int imin;
							int imax;

							std::cout << "\nVyber Vzdelanie: \n";
							std::cout << "Stlac:\n"
								<< "\t0 pre bez_ukonceneho_vzdelania\n"
								<< "\t1 pre zakladne\n"
								<< "\t2 pre ucnovske\n"
								<< "\t3 pre vyssie\n"
								<< "\t4 pre vyssie\n"
								<< "\t5 pre vysokoskolske\n"
								<< "\t6 pre bez_vzdelania\n"
								<< "\t7 pre nezistene\n";
							getline(std::cin, vzdelanie);
							std::cout << "Vyber dolnu hranicu intervalu: ";
							getline(std::cin, min);
							std::cout << "Vyber hornu hranicu intervalu: ";
							getline(std::cin, max);
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
							aplikovanyVzPocet = true;
							filter->addFilter(new FilterUJVzdelaniePocet(static_cast<Vzdelanie>(ivzdelanie), imin, imax));
						}
						else if (volba == "4")
						{
							std::string vzdelanie;
							std::string min{};
							std::string max{};
							int ivzdelanie;
							double dmin;
							double dmax;

							std::cout << "\nVyber Vzdelanie: \n";
							std::cout << "Stlac:\n"
								<< "\t0 pre bez_ukonceneho_vzdelania\n"
								<< "\t1 pre zakladne\n"
								<< "\t2 pre ucnovske\n"
								<< "\t3 pre vyssie\n"
								<< "\t4 pre vyssie\n"
								<< "\t5 pre vysokoskolske\n"
								<< "\t6 pre bez_vzdelania\n"
								<< "\t7 pre nezistene\n";
							getline(std::cin, vzdelanie);
							std::cout << "Vyber dolnu hranicu intervalu: ";
							getline(std::cin, min);
							std::cout << "Vyber hornu hranicu intervalu: ";
							getline(std::cin, max);
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
							aplivakonyVzPodiel = true;
							filter->addFilter(new FilterUJVzdelaniePodiel(static_cast<Vzdelanie>(ivzdelanie), dmin, dmax));
						}
						else if (volba == "5")
						{
							fkoniec = true;
							break;
						}
						else
						{
							std::cout << "Zly vstup!";
						}
					}
					std::string volbaTabulky;
					structures::UnsortedSequenceTable<std::string, UzemnaJednotka*> novaTab;
					std::cout << "\nCo chceme filtrovat?\n"
						<< "0 pre kraje\n"
						<< "1 pre okresy\n"
						<< "2 pre obce\n";
					getline(std::cin, volbaTabulky);
					if (volbaTabulky == "0")
					{

						filter->vyfiltruj(kraje, novaTab);
						for (auto element : novaTab)
						{
							std::cout << "Vyfiltrovana UJ: \n";
							KriteriumUJNazov krit;
							std::cout << "\nNazov: ";
							std::cout << krit.ohodnot(element->accessData()) << '\n';
							KriteriumUJTyp krite;
							std::cout << "\nTyp: ";
							auto p = krite.ohodnot(element->accessData());

							std::string pom;
							if (p == TypUzemnaJednotka::STAT)
							{
								pom = "Stat";
							}
							else if (p == TypUzemnaJednotka::KRAJ) {
								pom = "Kraj";
							}
							else if (p == TypUzemnaJednotka::OKRES) {
								pom = "Okres";
							}
							else
							{
								pom = "Obec";
							}
							std::cout << pom << '\n';
							if (aplikovanyVzPocet) {
								for (int i = 0; i < 8; ++i)
								{
									switch (i)
									{
									case 0: std::cout << "\nbez_ukonceneho_vzdelania: ";
										break;
									case 1: std::cout << "zakladne: ";
										break;
									case 2: std::cout << "ucnovske: ";
										break;
									case 3: std::cout << "vyssie: ";
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
									KriteriumUJVzdelaniePocet kritpocet(static_cast<Vzdelanie>(i));
									std::cout << "pocet - " << kritpocet.ohodnot(element->accessData()) << '\n';
								}
							}
							if (aplivakonyVzPodiel) {
								for (int i = 0; i < 8; ++i)
								{
									switch (i)
									{
									case 0: std::cout << "\nbez_ukonceneho_vzdelania: ";
										break;
									case 1: std::cout << "zakladne: ";
										break;
									case 2: std::cout << "ucnovske: ";
										break;
									case 3: std::cout << "vyssie: ";
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
									KriteriumUJVzdelaniePodiel kritpocet(static_cast<Vzdelanie>(i));
									std::cout << "podiel - " << kritpocet.ohodnot(element->accessData()) << '\n';
								}
							}

							UzemnaJednotka* nadradena = element->accessData()->getNadriadenaUJ();
							std::string vtyp;
							TypUzemnaJednotka typ;
							while (nadradena) {
								std::cout << "\nNazov nadradenej UJ: " << krit.ohodnot(nadradena) << '\n';

								typ =  krite.ohodnot(nadradena);
									if (typ == TypUzemnaJednotka::STAT)
									{
										vtyp = "Stat";
									}
									else if (typ == TypUzemnaJednotka::KRAJ) {
										vtyp = "Kraj";
									}
									else if (typ == TypUzemnaJednotka::OKRES) {
										vtyp = "Okres";
									}
									else
									{
										vtyp = "Obec";
									}
									std::cout << "\nTyp nadriadenej UJ: " << vtyp << '\n';
									nadradena = nadradena->getNadriadenaUJ();
							}
							std::cout << "///////////////////////////////////////////////////\n";

						}
					}
					else if (volbaTabulky == "1")
					{
					
						filter->vyfiltruj(okresy, novaTab);
						for (auto element : novaTab)
						{
							std::cout << "Vyfiltrovana UJ: \n";
							KriteriumUJNazov krit;
							std::cout << "\nNazov: ";
							std::cout << krit.ohodnot(element->accessData()) << '\n';
							KriteriumUJTyp krite;
							std::cout << "\nTyp: ";
							auto p = krite.ohodnot(element->accessData());

							std::string pom;
							if (p == TypUzemnaJednotka::STAT)
							{
								pom = "Stat";
							}
							else if (p == TypUzemnaJednotka::KRAJ) {
								pom = "Kraj";
							}
							else if (p == TypUzemnaJednotka::OKRES) {
								pom = "Okres";
							}
							else
							{
								pom = "Obec";
							}
							std::cout << pom << '\n';
							if (aplikovanyVzPocet) {
								for (int i = 0; i < 8; ++i)
								{
									switch (i)
									{
									case 0: std::cout << "\nbez_ukonceneho_vzdelania: ";
										break;
									case 1: std::cout << "zakladne: ";
										break;
									case 2: std::cout << "ucnovske: ";
										break;
									case 3: std::cout << "vyssie: ";
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
									KriteriumUJVzdelaniePocet kritpocet(static_cast<Vzdelanie>(i));
									std::cout << "pocet - " << kritpocet.ohodnot(element->accessData()) << '\n';
								}
							}
							if (aplivakonyVzPodiel) {
								for (int i = 0; i < 8; ++i)
								{
									switch (i)
									{
									case 0: std::cout << "\nbez_ukonceneho_vzdelania: ";
										break;
									case 1: std::cout << "zakladne: ";
										break;
									case 2: std::cout << "ucnovske: ";
										break;
									case 3: std::cout << "vyssie: ";
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
									KriteriumUJVzdelaniePodiel kritpocet(static_cast<Vzdelanie>(i));
									std::cout << "podiel - " << kritpocet.ohodnot(element->accessData()) << '\n';
								}
							}

							UzemnaJednotka* nadradena = element->accessData()->getNadriadenaUJ();
							std::string vtyp;
							TypUzemnaJednotka typ;
							while (nadradena) {
								std::cout << "\nNazov nadradenej UJ: " << krit.ohodnot(nadradena) << '\n';

								typ =  krite.ohodnot(nadradena);
									if (typ == TypUzemnaJednotka::STAT)
									{
										vtyp = "Stat";
									}
									else if (typ == TypUzemnaJednotka::KRAJ) {
										vtyp = "Kraj";
									}
									else if (typ == TypUzemnaJednotka::OKRES) {
										vtyp = "Okres";
									}
									else
									{
										vtyp = "Obec";
									}
									std::cout << "\nTyp nadriadenej UJ: " << vtyp << '\n';
									nadradena = nadradena->getNadriadenaUJ();
							}
							
							std::cout << "////////////////////////////////////////////////////////\n";
						}
					}
					else if(volbaTabulky =="2")
					{
						filter->vyfiltruj(obce, novaTab);
						for (auto element : novaTab)
						{
							std::cout << "Vyfiltrovana UJ: \n";
							KriteriumUJNazov krit;
							std::cout << "\nNazov: ";
							std::cout << krit.ohodnot(element->accessData()) << '\n';
							KriteriumUJTyp krite;
							std::cout << "\nTyp: ";
							auto p = krite.ohodnot(element->accessData());

							std::string pom;
							if (p == TypUzemnaJednotka::STAT)
							{
								pom = "Stat";
							}
							else if (p == TypUzemnaJednotka::KRAJ) {
								pom = "Kraj";
							}
							else if (p == TypUzemnaJednotka::OKRES) {
								pom = "Okres";
							}
							else
							{
								pom = "Obec";
							}
							std::cout << pom << '\n';
							if (aplikovanyVzPocet) {
								for (int i = 0; i < 8; ++i)
								{
									switch (i)
									{
									case 0: std::cout << "\nbez_ukonceneho_vzdelania: ";
										break;
									case 1: std::cout << "zakladne: ";
										break;
									case 2: std::cout << "ucnovske: ";
										break;
									case 3: std::cout << "vyssie: ";
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
									KriteriumUJVzdelaniePocet kritpocet(static_cast<Vzdelanie>(i));
									std::cout << "pocet - " << kritpocet.ohodnot(element->accessData()) << '\n';
								}
							}
							if (aplivakonyVzPodiel) {
								for (int i = 0; i < 8; ++i)
								{
									switch (i)
									{
									case 0: std::cout << "\nbez_ukonceneho_vzdelania: ";
										break;
									case 1: std::cout << "zakladne: ";
										break;
									case 2: std::cout << "ucnovske: ";
										break;
									case 3: std::cout << "vyssie: ";
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
									KriteriumUJVzdelaniePodiel kritpocet(static_cast<Vzdelanie>(i));
									std::cout << "podiel - " << kritpocet.ohodnot(element->accessData()) << '\n';
								}
							}

							UzemnaJednotka* nadradena = element->accessData()->getNadriadenaUJ();
							std::string vtyp;
							TypUzemnaJednotka typ;
							while (nadradena) {
								std::cout << "\nNazov nadradenej UJ: " << krit.ohodnot(nadradena) << '\n';

								typ =  krite.ohodnot(nadradena);
									if (typ == TypUzemnaJednotka::STAT)
									{
										vtyp = "Stat";
									}
									else if (typ == TypUzemnaJednotka::KRAJ) {
										vtyp = "Kraj";
									}
									else if (typ == TypUzemnaJednotka::OKRES) {
										vtyp = "Okres";
									}
									else
									{
										vtyp = "Obec";
									}
									std::cout << "\nTyp nadriadenej UJ: " << vtyp << '\n';
									nadradena = nadradena->getNadriadenaUJ();
							}
							
							std::cout << "////////////////////////////////////////////////////////\n";
						}
					}
				}
				else if (volba == "0")
				{
					std::cout << "zatial nic";
				}
				else
				{
					koniec = true;
					break;
				}

			}


			else if (operacia == "2")
			{

			}
			else if (operacia == "3")
			{
				koniec = true;
				break;
			}
			else
			{
				std::cout << "Zly vstup!";
			}
		}
	}*/
}





