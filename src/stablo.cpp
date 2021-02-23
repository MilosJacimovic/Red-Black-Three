#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include "stablo.h"
#include "cvor.h"
#include <fstream>
using namespace std;

Stablo::Stablo(Stablo &&t) {
	koren = t.koren;
	t.koren = nullptr;
}

Stablo::Stablo(const Stablo&) {}


void Stablo::IzbrisiStablo() {

	cvor *pom = koren;
	stack<cvor*>stek;
	stek.push(koren);
	while (!stek.empty()) {
		pom = stek.top();
		stek.pop();
		for (int i = 0; i < 4; i++) stek.push(pom->DohvatiSina(i));
		delete pom;
	}
	koren = nullptr;
}

cvor *Stablo::PretraziPoVremenuCekanja(int kriterijum, int &i) {
	kljuc *keys;
	cvor *pom = koren;

	while (pom) {
		keys = pom->DohvatiKljuceve();
		for (i = 0; i < 3; i++) {
			if (keys[i].flag && keys[i].vc == kriterijum)
				return pom;
			if (keys[i].flag && keys[i].vc > kriterijum) break;
		}
		if (i == 3 && !keys[2].flag) i = 2;
		pom = pom->DohvatiSina(i);
	}
	return nullptr;
}

cvor *Stablo::PretraziPoVremenuIzvrsavanja(int k, int x) {
	stack<cvor*> stek;
	if (!koren) return nullptr;
	stek.push(koren);
	cvor *nadjen = nullptr;

	while (!stek.empty()) {
		nadjen = stek.top();
		stek.pop();

		for (int i = 0; i < 3; i++) {
			if (nadjen->DohvatiKljuc(i).flag && nadjen->DohvatiKljuc(i).vi == k) {
				x = i;
				return nadjen;
			}
		}
		for (int i = 0; i < 4; i++)
			if (nadjen->DohvatiSina(i)) stek.push(nadjen->DohvatiSina(i));
	}
	return nullptr;
}

void Stablo::Pretraga() {
	int vreme, izbor, i;
	cvor *nadjen = nullptr;

	cout << endl << "Unesite kriterijem pertrage." << endl << "1. Vreme cekanja." << endl << "2. Vreme egzekucije." << endl;
	cin >> izbor;
	if (izbor == 1) {
		cout << "Pretraga po vremenu cekanja";
		cin >> vreme;
		nadjen = PretraziPoVremenuCekanja(vreme, i);
	}
	if (izbor == 2) {
		cout << "Pretraga po vremenu izvrsavanja";
		cin >> vreme;
		nadjen = PretraziPoVremenuIzvrsavanja(vreme, i);
	}
	if (nadjen) {
		cout << nadjen->DohvatiKljuc(i).ime << endl;
	}
	else cout << "Nije nadjentakav kljuc." << endl;

}
void Stablo::Obilazak() const {
	queue<cvor*> r1;
	queue<cvor*>r2;

	if (!koren) {
		cout << "Prazno stablo." << endl;
		return;
	}

	r1.push(koren);
	cvor *pom;
	while (!r1.empty() || !r2.empty()) {
		cout << endl;
		while (!r1.empty()) {
			pom = r1.front();
			r1.pop();
			cout << "    ";
			cout << " (" << pom->KojSin() << ")";
			if (pom->DohvatiKljuc(0).flag) cout << " " << pom->DohvatiKljuc(0).vc;
			if (pom->DohvatiKljuc(1).flag) cout << " " << pom->DohvatiKljuc(1).vc;
			if (pom->DohvatiKljuc(2).flag) cout << " " << pom->DohvatiKljuc(2).vc;

			for (int i = 0; i < 4; i++)
				if (pom->DohvatiSina(i)) r2.push(pom->DohvatiSina(i));
		}
		cout << endl;
		while (!r2.empty()) {
			pom = r2.front();
			r2.pop();
			cout << "   ";
			cout << " (" << pom->KojSin() << ")";
			if (pom->DohvatiKljuc(0).flag) cout << " " << pom->DohvatiKljuc(0).vc;
			if (pom->DohvatiKljuc(1).flag) cout << " " << pom->DohvatiKljuc(1).vc;
			if (pom->DohvatiKljuc(2).flag) cout << " " << pom->DohvatiKljuc(2).vc;

			for (int i = 0; i < 4; i++)
				if (pom->DohvatiSina(i)) r1.push(pom->DohvatiSina(i));
		}
	}
	cout << endl;

}
ostream &operator<<(ostream &stream, const Stablo &st) {
	st.Obilazak();
	return stream;
}

cvor *Stablo::GdeJeKljuc(int &x, string s) {
	cvor *pom;
	queue<cvor*> q;
	q.push(koren);
	while (!q.empty()) {
		pom = q.front();
		q.pop();
		for (int i = 0; i < 3; i++) {
			if (pom->DohvatiKljuc(i).flag) {
				if (pom->DohvatiKljuc(i).ime == s) {
					x = i;
					return pom;
				}
			}
		}
		for (int i = 0; i < 4; i++)
			if (pom->DohvatiSina(i)) q.push(pom->DohvatiSina(i));
	}
	return nullptr;
}
void Stablo::Simulacija() {
	if (!koren) {
		cout << "Stablo ne postoji." << endl;
		return;
	}

	int nkraj = 1;
	int deo_vremena;
	cout << "Deo vremena: ";
	cin >> deo_vremena;
	while (koren && nkraj) {
		cvor *levo = koren->NadjiMin();
		kljuc k;
		for (int i = 0; i < 3; i++) {
			if (levo->DohvatiKljuc(i).flag) {
				k = levo->DohvatiKljuc(i);
				break;
			}
		}
		Brisanje(k);
		if (!koren) break;
		queue<cvor*>q;
		q.push(koren);
		cvor *pom;
		vector<string>arr;

		while (!q.empty()) {
			pom = q.front();
			q.pop();
			if (!pom) break;
			for (int i = 0; i < 3; i++) {
				if (pom->DohvatiKljuc(i).flag) {
					pom->DohvatiKljuc(i).vc += deo_vremena;
					if (pom->DohvatiKljuc(i).mvc <= pom->DohvatiKljuc(i).vc) {
						arr.push_back(pom->DohvatiKljuc(i).ime);
					}
				}
			}
			for (int i = 0; i < 4; i++)
				if (pom->DohvatiSina(i)) q.push(pom->DohvatiSina(i));
		}
		string s;
		kljuc kk;
		int x;
		cvor *tren;

		while (!arr.empty()) {
			s = arr.back();
			arr.pop_back();
			tren = GdeJeKljuc(x, s);
			if (!tren) continue;
			kk = tren->DohvatiKljuc(x);
			Brisi(tren, x);
			kk.vc = kk.vc - kk.mvc;
			Ubacivanje(kk);
		}
		k.vi += deo_vremena;
		if (k.vi < k.vzi) Ubacivanje(k);
		Obilazak();
		cout << "1 za nastavak ili 0 za kraj.";
		cin >> nkraj;

	}
	if (!koren) cout << "Zavrseni su svi procesi.";
}

void Stablo::UbaciNePunCvor(cvor *&c, kljuc k, cvor *&lprenos, cvor *&dprenos) {
	cvor *prethodni = c;
	int x;
	if (prethodni && !prethodni->PunCvor()) {
		if (k.vc < prethodni->DohvatiKljuc(1).vc) {
			if (prethodni->DohvatiKljuc(0).flag) {
				if (prethodni->DohvatiKljuc(0).vc < k.vc)
					prethodni->UbaciSredinaDesno(k, x);
				else prethodni->UbaciLevo(k, x);
			}
			else {
				prethodni->DohvatiKljuc(0) = k;
				x = 0;
			}
		}
		else {
			if (prethodni->DohvatiKljuc(2).flag) {
				if (prethodni->DohvatiKljuc(2).vc <= k.vc)
					prethodni->UbaciDesno(k, x);
				else prethodni->UbaciSredinaLevo(k, x);
			}
			else {
				prethodni->DohvatiKljuc(2) = k;
				x = 2;
			}
		}
	}
	prethodni->DohvatiSina(x) = lprenos;
	prethodni->DohvatiSina(x + 1) = dprenos;
	return;
}
cvor *Stablo::NadjiGde(kljuc k) const {
	cvor *pom1 = koren, *pom2 = nullptr;
	kljuc *klj;
	int vrednost = k.vc, poslednji = 0;

	while (pom1) {
		pom2 = pom1;
		klj = pom1->DohvatiKljuceve();
		for (int i = 0; i < 3; i++) {
			if (klj[i].flag) {
				poslednji = i;
				int vred = klj[i].vc;
				if (vrednost < vred) {
					pom1 = pom1->DohvatiSina(i);
					break;
				}
				if (vrednost >= vred && !klj[i + 1].flag && i < 3) {
					pom1 = pom1->DohvatiSina(i + 1);
					break;
				}
			}
		}
		if (pom1 == pom2) pom1 = pom1->DohvatiSina(3);
	}
	return pom2;
}

void Stablo::UbaciPunCvor(cvor *&c, kljuc &k, cvor *&lprenos, cvor *&dprenos, bool &kraj) {
	int i;
	cvor *cv = nullptr;
	cvor *pom = new cvor(c->DohvatiKljuc(2));
	kljuc sred = c->DohvatiKljuc(1);
	pom->DohvatiOca() = c->DohvatiOca();
	c->DohvatiKljuc(1) = c->DohvatiKljuc(0);
	c->DohvatiKljuc(0).flag = false;
	c->DohvatiKljuc(2).flag = false;
	pom->DohvatiSina(1) = c->DohvatiSina(2);
	pom->DohvatiSina(2) = c->DohvatiSina(3);
	c->DohvatiSina(2) = c->DohvatiSina(1);
	c->DohvatiSina(1) = c->DohvatiSina(0);
	c->DohvatiSina(0) = nullptr;
	c->DohvatiSina(3) = nullptr;

	for (int j = 0; j < 4; j++) {
		if (c->DohvatiSina(j)) c->DohvatiSina(j)->DohvatiOca() = c;
		if (pom->DohvatiSina(j)) pom->DohvatiSina(j)->DohvatiOca() = pom;
	}
	if (k.vc < sred.vc) {
		cv = c;
		if (k.vc >= c->SredV()) {
			i = 2;
			c->DohvatiKljuc(2) = k;
			c->DohvatiKljuc(2).flag = true;
		}
		else {
			i = 0;
			c->DohvatiKljuc(0) = k;
			c->DohvatiKljuc(0).flag = true;
		}
	}
	else {
		cv = pom;
		if (k.vc >= pom->SredV()) {
			i = 2;
			pom->DohvatiKljuc(2) = k;
			pom->DohvatiKljuc(2).flag = true;
		}
		else {
			i = 0;
			pom->DohvatiKljuc(0) = k;
			pom->DohvatiKljuc(0).flag = true;
		}
	}

	cv->DohvatiSina(i) = lprenos;
	cv->DohvatiSina(i + 1) = dprenos;

	if (c == koren) {
		koren = new cvor(sred);
		koren->DohvatiSina(1) = c;
		koren->DohvatiSina(2) = pom;
		c->DohvatiOca() = koren;
		pom->DohvatiOca() = koren;
		kraj = true;
		return;
	}
	else {
		lprenos = c;
		c = c->DohvatiOca();
		k = sred;
		dprenos = pom;
	}

}

void Stablo::UcitajIzFajla() {
	ifstream file;
	file.open("KljuceviZaUbacivanje.txt");
	if (file.is_open()) {
		char c;
		string ime;
		int v1, v2;
		while (!file.eof()) {
			file >> ime;
			file >> v1;
			file >> v2;
			Ubacivanje(kljuc(ime, v1, v2));
		}
		file.close();
	}
	else cout << "Neuspesno otvaranja fajla." << endl;
}
void Stablo::Ubaci(cvor *pom, kljuc k, cvor *lprenos, cvor *dprenos) {
	bool kraj = false;
	while (!kraj) {
		if (!pom->PunCvor()) {
			UbaciNePunCvor(pom, k, lprenos, dprenos);
			kraj = true;
		}
		else UbaciPunCvor(pom, k, lprenos, dprenos, kraj);
	}
}

Stablo &Stablo::Ubacivanje(kljuc k) {

	if (!koren) {
		koren = new cvor(k);
		koren->DohvatiOca() = nullptr;

		for (int i = 0; i < 4; i++) koren->DohvatiSina(i) = nullptr;
		return *this;
	}
	cvor *pom = NadjiGde(k);
	Ubaci(pom, k, nullptr, nullptr);
	return *this;
}

void Stablo::Brisi(cvor *trenutni, int x) {

	if (!koren) return;
	if (!trenutni->List()) trenutni = trenutni->zamena(trenutni, trenutni->Sledbenik(x), x);
	if (trenutni == koren) {
		int j = 0;
		for (int i = 0; i < 3; i++)
			if (trenutni->DohvatiKljuc(i).flag)j++;
		if (j == 1) {
			delete (trenutni);
			koren = nullptr;
			return;
		}
	}

	cvor *c = nullptr;
	bool kraj = false;

	if (!trenutni->Srednji()) {
		trenutni->Obrisi(x);
		return;
	}
	while (!kraj) {
		if (trenutni->Pozajmi(c))
			return;
		if (trenutni == koren) {
			delete trenutni;
			koren = nullptr;
			return;
		}
		Spajanje(trenutni, c, koren);
		if (trenutni && !(trenutni->Prazan()))
			return;

		if (trenutni == koren) {
			for (int i = 0; i < 4; i++)
				if (trenutni->DohvatiSina(i))
					koren = trenutni->DohvatiSina(i);
			kraj = true;
			delete trenutni;
		}
	}


}

void Stablo::Brisanje(kljuc k) {
	cvor *tr = koren;
	int x;

	if (!koren) return;
	tr = PretraziPoVremenuCekanja(k.vc, x);
	if (!tr) return;
	Brisi(tr, x);
}

struct elem {
	cvor *c;
	int x;
	elem(cvor *cv, int i) :c(cv), x(i) {}
};
void Stablo::IspisCrvenoCrno() {

	string boja;
	queue<elem>r1, r2;

	if (!koren) return;
	r1.push(elem(koren, 1));
	cvor *pom;
	int i1;

	while (!r1.empty() || !r2.empty()) {
		cout << endl << "  ";
		while (!r1.empty()) {
			pom = r1.front().c;
			i1 = r1.front().x;
			r1.pop();
			if (i1 == 1)
				boja = " (B) ";
			else boja = " (R) ";

			if (i1 == 1) {
				if (pom->DohvatiKljuc(0).flag) r2.push(elem(pom, 0));
				else if (pom->DohvatiSina(1)) r2.push(elem(pom->DohvatiSina(1), 1));
				if (pom->DohvatiKljuc(2).flag) r2.push(elem(pom, 2));
				else if (pom->DohvatiSina(2)) r2.push(elem(pom->DohvatiSina(2), 1));
			}
			else {
				if (pom->DohvatiSina(i1)) r2.push(elem(pom->DohvatiSina(i1), 1));
				if (pom->DohvatiSina(i1 + 1)) r2.push(elem(pom->DohvatiSina(i1 + 1), 1));
			}
			cout << pom->DohvatiKljuc(i1).vc << boja;
		}

		cout << endl << "   ";
		while (!r2.empty()) {
			pom = r2.front().c;
			i1 = r2.front().x;
			r2.pop();
			if (i1 == 1)
				boja = " (B) ";
			else boja = " (R) ";

			if (i1 == 1) {
				if (pom->DohvatiKljuc(0).flag) r2.push(elem(pom, 0));
				else if (pom->DohvatiSina(1)) r2.push(elem(pom->DohvatiSina(1), 1));

				if (pom->DohvatiKljuc(2).flag) r2.push(elem(pom, 2));
				else if (pom->DohvatiSina(2)) r2.push(elem(pom->DohvatiSina(2), 1));
			}
			else {
				if (pom->DohvatiSina(i1)) r2.push(elem(pom->DohvatiSina(i1), 1));
				if (pom->DohvatiSina(i1 + 1)) r2.push(elem(pom->DohvatiSina(i1 + 1), 1));
			}
			cout << pom->DohvatiKljuc(i1).vc << boja;
		}
	}



}

void Stablo::BrisiUlaz() {
	bool kraj = false;
	cout << "Unesite -1 za kraj" << endl;
	kljuc k;
	while (!kraj) {
		cout << "Unesite vc za brisanje.";
		cin >> k.vc;
		k.flag = true;
		if (k.vc < 0) kraj = true;
		else Brisanje(k);
	}
}

void Stablo::UcitajUlaz() {
	bool kraj = false;
	cout << "Unesi -1 za kraj unosa." << endl;
	kljuc k;
	while (!kraj) {
		cout << "Unesi ime procesa";
		cin >> k.ime;
		cout << "Unesite vz.";
		cin >> k.vzi;
		cout << "Unesite maksimalno vc.";
		cin >> k.mvc;
		k.flag = true;
		if (k.vzi < 0 || k.mvc < 0) kraj = true;
		else Ubacivanje(k);
	}
}