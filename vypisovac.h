#pragma once
#include <iostream>
#include <string>

#include "structures/table/sorted_sequence_table.h"
#include "uzemnaJednotka/typUzemnaJednotka.h"
#include "uzemnaJednotka/uzemnaJednotka.h"

class Vypisovac
{
public:
	TypUzemnaJednotka stringToTyp(std::string& cislo);
	void vypisTypyUJ();
	void vypisTabulkuPodlaTypu(structures::SortedSequenceTable<std::string,
		UzemnaJednotka*>& tab, TypUzemnaJednotka typ);
	void vypisBodoveUJ(UzemnaJednotka* uj, bool vypisKritVzPocet, bool vypisKritVzPodiel);
	void vypisFilterUJ(UzemnaJednotka* uj, bool vypisKritVzPocet, bool vypisKritVzPodiel, Vzdelanie vzdelaniePocet, Vzdelanie vzdelaniePodiel);
	std::string typToString(TypUzemnaJednotka typ);
	void vypisKriteriaVsetkoVzdelanie(UzemnaJednotka* uzemna, bool vypisKritVzPocet, bool vypisKritVzPodiel);
	int typToCodeSize(TypUzemnaJednotka typ);
	void vypisCeluTabulku(structures::SortedSequenceTable<std::string, UzemnaJednotka*>& tab);
	void vypisVsetkyOperacie();
	void vypisCisloVsetkyFiltre();
	void vypisCisloVzdelania();
	void vyhodnotParametreVzdelaniePocet(const std::string& vzdelanie, std::string& min, std::string& max,
		int& ivzdelanie, int& imin, int& imax);
	void vyhodnotParametreVzdelaniePodiel(const std::string& vzdelanie, std::string& min, std::string& max,
		int& ivzdelanie, double& dmin, double& dmax);


	void vypisKonkretneVzdelanie(UzemnaJednotka* uzemna, bool vypisKritVzPocet,
		bool vypisKritVzPodiel, Vzdelanie vzdelaniePocet, Vzdelanie vzdelaniePodiel);

};

