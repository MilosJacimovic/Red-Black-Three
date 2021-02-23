#include "stablo.h"
#include <iostream>

int main() {
	int izbor = 1;
	Stablo stablo;
	char cekanje;
	while (izbor) {
		cout << "1. Ubacivanje preko standardnog inputa" << endl
			<< "2. Brisanje preko standardnog inputa" << endl
			<< "3. Ucitavanje procesa iz datoteke" << endl
			<< "4. Simulacija" << endl
			<< "5. Ispis 2-3-4 stabla" << endl
			<< "6. Ispis kao crveno-crno stablo" << endl
			<< "7. Pretraga kljuca" << endl
			<< "0. Kraj programa" << endl;
		cin >> izbor;
		switch (izbor) {
		case 1: stablo.UcitajUlaz(); break;
		case 2: stablo.BrisiUlaz(); break;
		case 3: stablo.UcitajIzFajla(); break;
		case 4: stablo.Simulacija(); break;
		case 5: cout << stablo; break;
		case 6: stablo.IspisCrvenoCrno(); break;
		case 7: stablo.Pretraga(); break;
		case 0: break;
		default: izbor = 9;
		}
		cin >> cekanje;
		system("cls");
	}
	return 0;
}