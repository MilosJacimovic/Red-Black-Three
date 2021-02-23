#include <iostream>
#include <string>
#include "cvor.h"
#include "stablo.h"
using namespace std;

cvor::cvor(cvor *o, kljuc keys[3]) {
	for (int i = 0; i < 4; i++) {
		kljucevi[i] = keys[i];
		deca[i] = nullptr;
	}
	otac = o;
	deca[3] = nullptr;
}

cvor::cvor(kljuc k) {
	int i = 0;

	kljucevi[1] = k;
	kljucevi[0].flag = kljucevi[2].flag = false;
	otac = nullptr;

	for (i; i < 4; i++)
		deca[i] = nullptr;
}

int cvor::SredV() const {
	if (kljucevi[1].flag)
		return kljucevi[1].vc;
	return 0;
}

int cvor::LevaV() const {
	if (kljucevi[0].flag)
		return kljucevi[0].vc;
	return 0;
}

int cvor::DesnV() const {
	if (kljucevi[2].flag)
		return kljucevi[2].vc;
	return 0;
}

bool cvor::PunCvor() const {
	int i = 0;

	for (i; i < 3; i++)
		if (!kljucevi[i].flag) return false;

	return true;
}

bool cvor::List() const {
	return (!(deca[3] || deca[2] || deca[1] || deca[0]));
}

void cvor::UbaciSredinaDesno(kljuc k, int &x) {
	DohvatiKljuc(2) = DohvatiKljuc(1);
	DohvatiKljuc(1) = k;
	DohvatiSina(3) = DohvatiSina(2);
	x = 1;

}
void cvor::UbaciSredinaLevo(kljuc k, int &x) {
	DohvatiKljuc(0) = DohvatiKljuc(1);
	DohvatiKljuc(1) = k;
	DohvatiSina(0) = DohvatiSina(1);
	x = 1;
}
void cvor::UbaciLevo(kljuc k, int &x) {
	DohvatiKljuc(2) = DohvatiKljuc(1);
	DohvatiKljuc(1) = DohvatiKljuc(0);
	DohvatiKljuc(0) = k;
	DohvatiSina(3) = DohvatiSina(2);
	DohvatiSina(2) = DohvatiSina(1);
	x = 0;
}
void cvor::UbaciDesno(kljuc k, int &x) {
	DohvatiKljuc(0) = DohvatiKljuc(1);
	DohvatiKljuc(1) = DohvatiKljuc(2);
	DohvatiKljuc(2) = k;
	DohvatiSina(0) = DohvatiSina(1);
	DohvatiSina(1) = DohvatiSina(2);
	x = 2;
}
cvor *cvor::DohvatiSina() {
	cvor *pom = this;
	int i = 0;

	while (!pom->List()) {
		for (i; i < 4; i++) {
			if (pom->deca[i]) {
				pom = pom->DohvatiSina(i);
				break;
			}
		}
	}
	return pom;
}
bool cvor::Prazan() {
	for (int i = 0; i < 3; i++)
		if (kljucevi[i].flag) return false;

	return true;
}
cvor* cvor::zamena(cvor *unut, cvor *list, int &x) {
	if (!list) return unut;
	for (int i = 0; i < 3; i++) {
		if (list->DohvatiKljuc(i).flag) {
			unut->DohvatiKljuc(x) = list->DohvatiKljuc(i);
			x = i;
			break;
		}
	}
	return list;
}

cvor *cvor::PunijiCvor(cvor *x, cvor *y) {
	int i = 0, j = 0;
	if (!x) return y;
	if (!y) return x;

	for (int b = 0; b < 3; b++) {
		if (x->kljucevi[i].flag) i++;
		if (y->kljucevi[i].flag) j++;
	}
	if (j > 1) return y;
	return (i > j ? x : y);
}

cvor *cvor::DohvatiBrata() {
	int i;
	if (otac) {
		switch (KojSin()) {
		case 0: return otac->DohvatiSina(1);
		case 1: return PunijiCvor(otac->DohvatiSina(0), otac->DohvatiSina(2));
		case 2: return PunijiCvor(otac->DohvatiSina(1), otac->DohvatiSina(3));
		case 3: return otac->DohvatiSina(2);
		}
	}
}

void Spajanje(cvor *&tr, cvor *&c, cvor *&koren) {
	cvor *brat = tr->DohvatiBrata();
	int i1 = tr->KojSin();
	int i2 = -1;
	if (brat)
		i2 = brat->KojSin();
	else return;

	cvor *o = tr->DohvatiOca();
	if (tr->DohvatiOca() == nullptr) {
		return;
	}

	o->DohvatiSina(i1) = nullptr;
	o->DohvatiSina(i2) = nullptr;
	delete tr;

	int io = i2 - (i1 > i2 ? 0 : 1);

	if (o->DohvatiKljuc(io).vc < brat->SredV()) {
		brat->DohvatiKljuc(0) = o->DohvatiKljuc(io);
		brat->DohvatiSina(0) = c;
		if (c)
			c->DohvatiOca() = brat;
	}
	else {
		brat->DohvatiKljuc(2) = o->DohvatiKljuc(io);
		brat->DohvatiSina(3) = c;
		if (c)
			c->DohvatiOca() = brat;
	}

	o->DohvatiKljuc(io).flag = false;

	int vel = 0;
	for (int i = 0; i < 3; i++)
		if (o->DohvatiKljuc(i).flag) vel++;

	if (vel) {
		if (io == 1) {
			if (o->DohvatiKljuc(2).flag) {
				o->DohvatiKljuc(1) = o->DohvatiKljuc(2);
				o->DohvatiKljuc(2).flag = false;
				o->DohvatiSina(2) = o->DohvatiSina(3);
				o->DohvatiSina(3) = nullptr;
				o->DohvatiSina(1) = brat;
			}
			else {
				o->DohvatiKljuc(1) = o->DohvatiKljuc(0);
				o->DohvatiKljuc(0).flag = false;
				o->DohvatiSina(2) = brat;
				o->DohvatiSina(1) = o->DohvatiSina(0);
				o->DohvatiSina(0) = nullptr;
			}
		}
		if (io == 2) {
			o->DohvatiSina(3) = nullptr;
			o->DohvatiSina(2) = brat;
		}
		if (io == 0) {
			o->DohvatiSina(0) = nullptr;
			o->DohvatiSina(1) = brat;
		}
		if (c) c->DohvatiOca() = brat;
	}

	tr = o;
	if ((o == koren) && koren->Prazan()) {
		delete koren;
		tr = koren = brat;
		if (brat->DohvatiKljuc(0).flag) brat->DohvatiSina(0) = c;
		else brat->DohvatiSina(3) = c;
	}
	c = brat;
}

kljuc cvor::DohvatiMax(cvor *&c) {
	kljuc k;
	int  i;

	for (i = 2; i >= 0; i--)
		if (kljucevi[i].flag) break;

	c = deca[i + 1];
	deca[i + 1] = nullptr;
	k = kljucevi[i];
	kljucevi[i].flag = false;

	if (i == 1) {
		kljucevi[1] = kljucevi[0];
		kljucevi[0].flag = false;
		deca[2] = deca[1];
		deca[1] = deca[0];
		deca[0] = nullptr;
	}
	return k;
}

kljuc cvor::DohvatiMin(cvor *& c) {
	kljuc k;
	int  i;

	for (i = 0; i < 3; i++)
		if (kljucevi[i].flag) break;

	c = deca[i];
	deca[i] = nullptr;
	k = kljucevi[i];
	kljucevi[i].flag = false;

	if (i == 1) {
		kljucevi[1] = kljucevi[2];
		kljucevi[2].flag = false;
		deca[1] = deca[2];
		deca[2] = deca[3];
		deca[3] = nullptr;
	}
	return k;
}
void cvor::Obrisi(int x) {
	if (x == 0) kljucevi[0].flag = false;
	if (x == 2) kljucevi[2].flag = false;
	if (x == 1) {
		if (kljucevi[2].flag) {
			kljucevi[1] = kljucevi[2];
			kljucevi[2].flag = false;
		}
		else {
			kljucevi[1] = kljucevi[0];
			kljucevi[0].flag = false;
		}
	}

}

bool cvor::Srednji() {
	if (!kljucevi[0].flag && !kljucevi[2].flag && kljucevi[1].flag) return true;
	return false;
}
bool cvor::Pozajmi(cvor *&c) {
	cvor *brat = nullptr, *prenos = nullptr;

	int i1 = KojSin();
	if ((brat = DohvatiBrata()) && !(brat->Srednji())) {
		int i2 = brat->KojSin();
		int io = i2 - (i1 > i2 ? 0 : 1);

		if (i1 == 0) {
			kljucevi[1] = otac->DohvatiKljuc(0);
			otac->DohvatiKljuc(0) = brat->DohvatiMin(prenos);
			deca[2] = prenos;
			deca[1] = c;
		}
		if (i1 == 1) {
			if (i1 > i2) {
				kljucevi[1] = otac->DohvatiKljuc(0);
				otac->DohvatiKljuc(0) = brat->DohvatiMax(prenos);
				deca[1] = prenos;
				deca[2] = c;
			}
			else {
				kljucevi[1] = otac->DohvatiKljuc(1);
				otac->DohvatiKljuc(1) = brat->DohvatiMin(prenos);
				deca[2] = prenos;
				deca[1] = c;
			}
		}
		if (i1 == 2) {
			if (i1 > i2) {
				kljucevi[1] = otac->DohvatiKljuc(1);
				otac->DohvatiKljuc(1) = brat->DohvatiMax(prenos);
				deca[1] = prenos;
				deca[2] = c;
			}
			else {
				kljucevi[1] = otac->DohvatiKljuc(2);
				otac->DohvatiKljuc(2) = brat->DohvatiMin(prenos);
				deca[2] = prenos;
				deca[1] = c;
			}
		}
		if (i1 == 3) {
			kljucevi[1] = otac->DohvatiKljuc(2);
			otac->DohvatiKljuc(2) = brat->DohvatiMax(prenos);
			deca[1] = prenos;
			deca[2] = c;
		}
		if (prenos) prenos->DohvatiOca() = this;
		if (c) c->DohvatiOca() = this;

		return true;
	}
	return false;
}

cvor *cvor::NadjiMin() {
	cvor *pom = this;
	while (!pom->List()) {
		for (int i = 0; i < 4; i++) {
			if (pom->deca[i]) {
				pom = pom->DohvatiSina(i);
				break;
			}
		}
	}
	return pom;
}

int cvor::KojSin() const {

	for (int i = 0; i < 4; i++) {
		if (otac)
			if (otac->DohvatiSina(i) == this) return i;
	}
	return 0;
}

cvor *cvor::Sledbenik(int i) const {
	cvor *pom = deca[i + 1];

	if (!pom) return nullptr;
	return pom->NadjiMin();
}