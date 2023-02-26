#pragma once
#include <fstream>
#include <iostream>
#include <sstream>

#include "uzemnaJednotka/uzemnaJednotka.h"
#include "structures/table/sorted_sequence_table.h"
using std::string;
using std::getline;

class Loader
{
public:
	void nacitaj(
		structures::SortedSequenceTable<string, UzemnaJednotka*>& table,
	structures::SortedSequenceTable<string, string>& kodovanie);
};

inline void Loader::nacitaj(
	structures::SortedSequenceTable<string, UzemnaJednotka*>& table,
	structures::SortedSequenceTable<string, string>& kodovanie)
{
	

	string kod ="SK";
	string nazov = "Slovensko";
	string riadok;
	UzemnaJednotka* slovensko {new UzemnaJednotka(TypUzemnaJednotka::STAT,kod,nazov)};
	table.insert(kod,slovensko);
	kodovanie.insert("Slovensko", "SK");


	std::ifstream fileKraje{ "kraje.csv",std::ios::in };


	if (!fileKraje)
	{
		fileKraje.close();
		throw std::runtime_error("Nepodarilo sa otvorit kraje.csv subor");
	}
	std::cout << "Nacitavanie kraje.csv...\n";
	getline(fileKraje,riadok); // prvy riadok s popismy
	while (getline(fileKraje, riadok))
	{
		std::stringstream ss{ riadok };
		string stlpec;
		for (int i{}; i < 6; i++) {
			std::getline(ss, stlpec, ';');
			switch (i)
			{
			case 5: kod = stlpec.substr(5, 5);
				break;
			case 2: nazov = stlpec;
				break;
			default:;
			}
		}
		UzemnaJednotka* kraj{ new UzemnaJednotka(TypUzemnaJednotka::KRAJ,kod,nazov) };
		kraj->setNadriadenaUJ(slovensko);
		table.insert(kod, kraj);
		kodovanie.insert(nazov,kod);
	}
	fileKraje.close();

	std::ifstream fileOkresy{ "okresy.csv",std::ios::in };
	if (!fileOkresy)
	{
		fileOkresy.close();
		throw std::runtime_error("Nepodarilo sa otvorit okresy.csv subor");
	}
	std::cout << "Nacitavanie okresy.csv...\n";
	getline(fileOkresy,riadok);  // prvy riadok s popismy
	while (getline(fileOkresy, riadok))
	{
		std::stringstream ss{ riadok };
		string stlpec;
		for (int i{}; i < 6; i++) {
			std::getline(ss, stlpec, ';');
			switch (i)
			{
			case 1: kod = stlpec;
				break;
			case 2: nazov = stlpec;
				break;
			default:;
			}
		}
		if(kod == "SKZZZ")
			kod = "SKYYYY";
		UzemnaJednotka* okres{ new UzemnaJednotka(TypUzemnaJednotka::OKRES,kod,nazov) };
		if(kod =="SKYYYY" || kod == "SKZZZZ")
			okres->setNadriadenaUJ(table.find("*****"));
		table.insert(kod, okres);
		kodovanie.insert(nazov,kod);
		for (auto kraj : table)
		{
			if (kod.substr(0, 5) == kraj->getKey())
			{
				okres->setNadriadenaUJ(kraj->accessData());
				break;
			}
		}

	}
	fileOkresy.close();

	structures::SortedSequenceTable<std::string,UzemnaJednotka*> pomTab(table);

	std::ifstream fileObce{ "obce.csv",std::ios::in };


	if (!fileObce)
	{
		fileObce.close();
		throw std::runtime_error("Nepodarilo sa otvorit obce.csv subor");
	}
	std::cout << "Nacitavanie obce.csv...\n";

	getline(fileObce,riadok);  // prvy riadok s popismy
	while (getline(fileObce, riadok)) //kym nie je koniec file
	{
		std::stringstream ss{ riadok };
		string stlpec;
		for (int i{}; i < 6; i++) {
			std::getline(ss, stlpec, ';');
			switch (i)
			{
			case 1: kod = stlpec;
				break;
			case 2: nazov = stlpec;
				break;
			default:;
			}
		}
		if(kod == "SKZZZZ")
			kod = "SKYYYYYYYYYY";
		UzemnaJednotka* obec{ new UzemnaJednotka(TypUzemnaJednotka::OBEC,kod,nazov) };
		
		table.insert(kod, obec);
		kodovanie.insert(nazov,kod);
		for (auto okres : pomTab)
		{
			if (kod.substr(0, 6) == okres->getKey())
			{

				obec->setNadriadenaUJ(okres->accessData());
				break;
			}
		}
	}
	fileObce.close();


	std::ifstream fileVzdelanie{ "vzdelanie.csv",std::ios::in };


	if (!fileVzdelanie)
	{
		fileVzdelanie.close();
		throw std::runtime_error("Nepodarilo sa otvorit vzdelanie.csv subor");
	}
	std::cout << "Nacitavanie vzdelanie.csv...\n";

	getline(fileVzdelanie,riadok);  // prvy riadok s popismy
	while (getline(fileVzdelanie, riadok)) //kym nie je koniec file
	{
		std::stringstream ss{ riadok };
		std::getline(ss, riadok, ';'); //kod

		auto kodObec{ riadok };
		auto obec{ table.find(kodObec) };

		auto kodOkres{ kodObec.substr(0,6) };
		auto okres{ table.find(kodOkres) };

		auto kodKraj{ kodOkres.substr(0,5) };
		auto kraj{ table.find(kodKraj) };

		std::getline(ss, riadok, ';'); //nazov - naprazdno
		for (int i{}; i < 9; i++) {
			std::getline(ss, riadok, ';'); //vzdelania
			switch (i)
			{
			case bez_ukonceneho_vzdelania:
				obec->pridajOsobyAVzdelanie(std::stoi(riadok), bez_ukonceneho_vzdelania);
				okres->pridajOsobyAVzdelanie(std::stoi(riadok), bez_ukonceneho_vzdelania);
				kraj->pridajOsobyAVzdelanie(std::stoi(riadok), bez_ukonceneho_vzdelania);
				slovensko->pridajOsobyAVzdelanie(std::stoi(riadok), bez_ukonceneho_vzdelania);

				break;
			case zakladne:
				obec->pridajOsobyAVzdelanie(std::stoi(riadok), zakladne);
				okres->pridajOsobyAVzdelanie(std::stoi(riadok), zakladne);
				kraj->pridajOsobyAVzdelanie(std::stoi(riadok), zakladne);
				slovensko->pridajOsobyAVzdelanie(std::stoi(riadok), zakladne);
				break;
			case ucnovske:
				obec->pridajOsobyAVzdelanie(std::stoi(riadok), ucnovske);
				okres->pridajOsobyAVzdelanie(std::stoi(riadok), ucnovske);
				kraj->pridajOsobyAVzdelanie(std::stoi(riadok), ucnovske);
				slovensko->pridajOsobyAVzdelanie(std::stoi(riadok), ucnovske);
				break;
			case stredne:
				obec->pridajOsobyAVzdelanie(std::stoi(riadok), stredne);
				okres->pridajOsobyAVzdelanie(std::stoi(riadok), stredne);
				kraj->pridajOsobyAVzdelanie(std::stoi(riadok), stredne);
				slovensko->pridajOsobyAVzdelanie(std::stoi(riadok), stredne);
				break;
			case vyssie:
				obec->pridajOsobyAVzdelanie(std::stoi(riadok), vyssie);
				okres->pridajOsobyAVzdelanie(std::stoi(riadok), vyssie);
				kraj->pridajOsobyAVzdelanie(std::stoi(riadok), vyssie);
				slovensko->pridajOsobyAVzdelanie(std::stoi(riadok), vyssie);
				break;
			case vysokoskolske:
				obec->pridajOsobyAVzdelanie(std::stoi(riadok), vysokoskolske);
				okres->pridajOsobyAVzdelanie(std::stoi(riadok), vysokoskolske);
				kraj->pridajOsobyAVzdelanie(std::stoi(riadok), vysokoskolske);
				slovensko->pridajOsobyAVzdelanie(std::stoi(riadok), vysokoskolske);
				break;
			case bez_vzdelania:
				obec->pridajOsobyAVzdelanie(std::stoi(riadok), bez_vzdelania);
				okres->pridajOsobyAVzdelanie(std::stoi(riadok), bez_vzdelania);
				kraj->pridajOsobyAVzdelanie(std::stoi(riadok), bez_vzdelania);
				slovensko->pridajOsobyAVzdelanie(std::stoi(riadok), bez_vzdelania);
				break;
			case nezistene:
				obec->pridajOsobyAVzdelanie(std::stoi(riadok), nezistene);
				okres->pridajOsobyAVzdelanie(std::stoi(riadok), nezistene);
				kraj->pridajOsobyAVzdelanie(std::stoi(riadok), nezistene);
				slovensko->pridajOsobyAVzdelanie(std::stoi(riadok), nezistene);
				break;
			default:;
			}
		}
	}
	fileVzdelanie.close();

	


	std::ifstream fileVek{ "vek.csv",std::ios::in };


	if (!fileVek)
	{
		fileVek.close();
		throw std::runtime_error("Nepodarilo sa otvorit vek.csv subor");
	}
	std::cout << "Nacitavanie vek.csv...\n";

	getline(fileVek,riadok);  // prvy riadok s popismy
	while (getline(fileVek, riadok)) //kym nie je koniec file
	{
		std::stringstream ss{ riadok };
		std::getline(ss, riadok, ';'); //kod

		auto kodObec{ riadok };
		auto obec{ table.find(kodObec) };

		auto kodOkres{ kodObec.substr(0,6) };
		auto okres{ table.find(kodOkres) };

		auto kodKraj{ kodOkres.substr(0,5) };
		auto kraj{ table.find(kodKraj) };

		int spolu{};
		std::getline(ss, riadok, ';'); //nazov - naprazdno
		for (int i{}; i < 15; i++) {
			std::getline(ss, riadok, ';');
			spolu += std::stoi(riadok);
		}
		obec->pridajEVS(spolu,predproduktivni);
		okres->pridajEVS(spolu,predproduktivni);
		kraj->pridajEVS(spolu,predproduktivni);
		slovensko->pridajEVS(spolu,predproduktivni);
		spolu = 0;

		for (int i{}; i < 50; i++) {
			std::getline(ss, riadok, ';');
			spolu += std::stoi(riadok);
		}
		obec->pridajEVS(spolu,produktivni);
		okres->pridajEVS(spolu,produktivni);
		kraj->pridajEVS(spolu,produktivni);
		slovensko->pridajEVS(spolu,produktivni);
		spolu = 0;

		for (int i{}; i < 36; i++) {
			std::getline(ss, riadok, ';');
			spolu += std::stoi(riadok);
		}
		obec->pridajEVS(spolu,poproduktivni);
		okres->pridajEVS(spolu,poproduktivni);
		kraj->pridajEVS(spolu,poproduktivni);
		slovensko->pridajEVS(spolu,poproduktivni);
		spolu = 0;

		for (int i{}; i < 15; i++) {
			std::getline(ss, riadok, ';');
			spolu += std::stoi(riadok);
		}
		obec->pridajEVS(spolu,predproduktivni);
		okres->pridajEVS(spolu,predproduktivni);
		kraj->pridajEVS(spolu,predproduktivni);
		slovensko->pridajEVS(spolu,predproduktivni);
		spolu = 0;

		for (int i{}; i < 50; i++) {
			std::getline(ss, riadok, ';');
			spolu += std::stoi(riadok);
		}
		obec->pridajEVS(spolu,produktivni);
		okres->pridajEVS(spolu,produktivni);
		kraj->pridajEVS(spolu,produktivni);
		slovensko->pridajEVS(spolu,produktivni);
		spolu = 0;

		for (int i{}; i < 36; i++) {
			std::getline(ss, riadok, ';');
			spolu += std::stoi(riadok);
		}
		obec->pridajEVS(spolu,poproduktivni);
		okres->pridajEVS(spolu,poproduktivni);
		kraj->pridajEVS(spolu,poproduktivni);
		slovensko->pridajEVS(spolu,poproduktivni);
		spolu = 0;
	}
	
	fileVek.close();


}
