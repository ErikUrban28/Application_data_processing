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
		std::cerr << "Nepodarilo sa otvorit kraje.csv subor";
		return;
	}
	std::cout << "Nacitavanie kraje.csv...\n";

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

	std::ifstream fileOkresy{ "okresy.csv",std::ios::in };
	if (!fileOkresy)
	{
		std::cerr << "Nepodarilo sa otvorit okresy.csv subor";
		return;
	}
	std::cout << "Nacitavanie okresy.csv...\n";

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
	structures::SortedSequenceTable<std::string,UzemnaJednotka*> pomTab(table);

	std::ifstream fileObce{ "obce.csv",std::ios::in };


	if (!fileObce)
	{
		std::cerr << "Nepodarilo sa otvorit obce.csv subor";
		return;
	}
	std::cout << "Nacitavanie obce.csv...\n";


	while (getline(fileObce, riadok))
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



	std::ifstream fileVzdelanie{ "vzdelanie.csv",std::ios::in };


	if (!fileVzdelanie)
	{
		std::cerr << "Nepodarilo sa otvorit vzdelanie.csv subor";
		return;
	}
	std::cout << "Nacitavanie vzdelanie.csv...\n";


	while (getline(fileVzdelanie, riadok))
	{
		std::stringstream ss{ riadok };
		std::getline(ss, riadok, ';');

		auto kodObec{ riadok };
		auto obec{ table.find(kodObec) };

		auto kodOkres{ kodObec.substr(0,6) };
		auto okres{ table.find(kodOkres) };

		auto kodKraj{ kodOkres.substr(0,5) };
		auto kraj{ table.find(kodKraj) };

		std::getline(ss, riadok, ';');
		for (int i{}; i < 9; i++) {
			std::getline(ss, riadok, ';');
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


	fileObce.close();
	fileOkresy.close();
	fileKraje.close();



}
