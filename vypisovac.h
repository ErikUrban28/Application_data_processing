#pragma once
#include <iostream>
#include <string>

#include "structures/table/sorted_sequence_table.h"
#include "uzemnaJednotka/typUzemnaJednotka.h"
#include "uzemnaJednotka/uzemnaJednotka.h"

class Vypisovac
{
public:
	
	
	
	void vypisCisloVsetkyFiltre();
	void vypisCisloVzdelania();
	void vypisCisloEVS();
	void vypisVsetkyOperacie();
	void vypisTypyUJ();
	void trieditAko();

	std::string typToString(TypUzemnaJednotka typ);
	TypUzemnaJednotka stringToTyp(std::string& vstup);
	int typToCodeSize(TypUzemnaJednotka typ);

	void vyhodnotParametreVzdelaniePocet(const std::string& vzdelanie, std::string& min, std::string& max,
		int& ivzdelanie, int& imin, int& imax);
	void vyhodnotParametreVzdelaniePodiel(const std::string& vzdelanie, std::string& min, std::string& max,
		int& ivzdelanie, double& dmin, double& dmax);

	void vyhodnotParametreEVSPodiel(const std::string& evs,std::string& min, std::string& max,
		int& devs, double& dmin,double& dmax);
	void vyhodnotParametreEVSPocet(const std::string& evs, std::string& min, std::string& max,
		int& ievs, int& imin,int& imax);

	void vypisTabulkuPodlaTypu(structures::SortedSequenceTable<std::string,
		UzemnaJednotka*>& tab, TypUzemnaJednotka typ);

	void vypisBodoveUJ(UzemnaJednotka* uj);
	void vypisNazovATyp(UzemnaJednotka* uj,bool vypisTyp);
	void vypisNadradeneUJ(UzemnaJednotka* uj, bool typ);

	void vypisFilterUJBezFiltra(UzemnaJednotka* uj);
	void vypisFilterUJVzPocet(UzemnaJednotka* uj, Vzdelanie vzdelaniePocet);
	void vypisFilterUJVzPodiel(UzemnaJednotka* uj, Vzdelanie vzdelaniePodiel);
	void vypisFilterUJEVSPocet(UzemnaJednotka* uj, EVS evsPocet);
	void vypisFilterUJEVSPodiel(UzemnaJednotka* uj, EVS evsPodiel);

	void vypisKritVzdelaniePocetVsetko(UzemnaJednotka* uzemna);
	void vypisKritVekovaSkupinaPocetVsetko(UzemnaJednotka* uzemna);

	void vypisVsetkyNazvy(structures::SortedSequenceTable<std::string, UzemnaJednotka*>& tab);


};

