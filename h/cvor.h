#pragma once
#include <string>
using namespace std;

struct kljuc {
	string ime;
	bool flag;
	int vc, mvc, vi, vzi = 0;

	kljuc(string i, int v1, int v2) {
		ime = i;
		vzi = v1;
		vc = v2;
		mvc = 82;
		vi = 0;
	}
	kljuc() {
		flag = false;
		ime = "empty";
		vc = vi = mvc = vzi = 0;
	}
};

class cvor {

private:
	kljuc kljucevi[3];
	int ukupno_k = 1;
	cvor *deca[4], *otac;

public:
	int &DohvatiUkupno() { return ukupno_k; }
	cvor(cvor *o, kljuc k[]);
	cvor(kljuc k);
	cvor *&DohvatiSina(int i) { return deca[i]; }
	kljuc &DohvatiKljuc(int i) {
		return kljucevi[i];
	}
	cvor *&DohvatiOca() { return otac; }
	kljuc *DohvatiKljuceve() {
		return kljucevi;
	}
	cvor *zamena(cvor*, cvor*, int&);

	cvor * PunijiCvor(cvor * x, cvor * y);

	cvor * DohvatiBrata();

	int SredV() const;
	int LevaV() const;
	int DesnV() const;

	bool PunCvor() const;
	bool List() const;
	void UbaciSredinaDesno(kljuc k, int & x);
	void UbaciSredinaLevo(kljuc k, int & x);
	void UbaciLevo(kljuc k, int & x);
	void UbaciDesno(kljuc k, int & x);
	cvor * DohvatiSina();
	bool Prazan();
	kljuc DohvatiMax(cvor *& c);
	kljuc DohvatiMin(cvor *& c);
	void Obrisi(int x);
	bool Srednji();
	bool Pozajmi(cvor *& c);
	cvor * NadjiMin();
	int KojSin() const;
	cvor * DohvatiMinCvor();
	cvor * Sledbenik(int i) const;
	//~cvor();

};

void Spajanje(cvor *&, cvor *&, cvor*&);