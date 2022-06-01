#pragma once
#include <string>

#include "typUzemnaJednotka.h"
#include "structures/list/array_list.h"
enum Vzdelanie
{
	bez_ukonceneho_vzdelania,
	zakladne,
	ucnovske,
	stredne,
	vyssie,
	vysokoskolske,
	bez_vzdelania,
	nezistene,

};


class UzemnaJednotka
{
public:
	UzemnaJednotka(const TypUzemnaJednotka typ, const std::string& code,const std::string& nazov);

	const std::string& getNazov() const{return officalTitle_;}
	TypUzemnaJednotka getTyp() const{return typ_;}
	const std::string& getCode() const{return code_;}

	int getPocetObyvatelov() const {return pocetObyvatelov_;}
	bool patriDoVyssiehoCelku(UzemnaJednotka* vyssiCelok);
	UzemnaJednotka* getNadriadenaUJ() const {return nadradenaUJ_;}
	void setNadriadenaUJ(UzemnaJednotka* vyssiaUJ) {nadradenaUJ_ = vyssiaUJ;}
	
	void pridajOsobyAVzdelanie(const int pocet, const Vzdelanie vzdelanie);
	int pocetObyvatelovSoVzdelanim(const Vzdelanie vzdelanie) const{return vzdelania_->at(vzdelanie);}


private:
	TypUzemnaJednotka typ_;
	std::string code_;
	std::string officalTitle_;
	structures::ArrayList<int>* vzdelania_ {new structures::ArrayList<int>};
	UzemnaJednotka* nadradenaUJ_{nullptr};
	int pocetObyvatelov_{};

};

inline UzemnaJednotka::UzemnaJednotka(const TypUzemnaJednotka typ, const std::string& code, const std::string& nazov):
	typ_{ typ },
	code_{ code },
	officalTitle_{nazov}
{
	for(int i{}; i <8;i++)
	{
		vzdelania_->insert(0,i);
	}
}

inline bool UzemnaJednotka::patriDoVyssiehoCelku(UzemnaJednotka* vyssiCelok)
{
	UzemnaJednotka* uj = this;
	while (uj)
	{
		if (uj->getNadriadenaUJ() == vyssiCelok)
		{
			return true;
		}
		uj = uj->getNadriadenaUJ();
	}
	return false;
}

inline void UzemnaJednotka::pridajOsobyAVzdelanie(const int pocet, const Vzdelanie vzdelanie)
{
	vzdelania_->at(vzdelanie) += pocet;
	pocetObyvatelov_+=pocet;
}


