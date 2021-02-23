#pragma once
#include <string>
#include "cvor.h"
using namespace std;

class Stablo {

private:
	cvor *koren;

public:
	void Pretraga();
	void Obilazak() const;
	Stablo() { koren = nullptr; }
	Stablo(Stablo && t);
	Stablo(const Stablo &);
	void IzbrisiStablo();

	cvor *PretraziPoVremenuCekanja(int kriterijum, int &k);
	cvor * PretraziPoVremenuIzvrsavanja(int k, int x);
	cvor *NadjiGde(kljuc) const;

	void UbaciPunCvor(cvor *& c, kljuc & k, cvor *& lprenos, cvor *& dprenos, bool & kraj);
	void UbaciNePunCvor(cvor *& pom, kljuc k, cvor *& lprenos, cvor *& dprenos);
	void UcitajIzFajla();
	void Ubaci(cvor * pom, kljuc k, cvor * lprenos, cvor * dprenos);
	Stablo & Ubacivanje(kljuc k);

	void Brisi(cvor * trenutni, int x);
	void Brisanje(kljuc k);

	void IspisCrvenoCrno();

	void BrisiUlaz();

	void UcitajUlaz();

	friend ostream &operator<<(ostream &stream, const Stablo &s);
	cvor * GdeJeKljuc(int &x, string i);
	void Simulacija();

	//~Stablo();
};