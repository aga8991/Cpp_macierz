#include "Solver.h"
#include <iostream>
#include <exception>

template<typename typ_danych>
void Solver<typ_danych>::skalujWiersz(int ktory, typ_danych skala) {
  // mnozy kazdy element wiersza przez skalar
  for (int i = 0; i < n + 1; ++i) {
    mat.element(ktory, i) *= skala;
  }
}

template<typename typ_danych>
void Solver<typ_danych>::addWiersze(int ktory, int do_ktorego, typ_danych skala) {
  // dodaje pierwszy rzad do drugiego, mnozac wczesniej jego wartosci przez skalar
  for (int i = 0; i < n + 1; ++i) {
    mat.element(do_ktorego, i) += skala * mat.element(ktory, i);
  }
}

template<typename typ_danych>
void Solver<typ_danych>::rozwiaz() {
  // rozwiazuj kazda kolumne z osobna

	int x = 0;
	do {
		for (int i = 0; i < n; ++i) {
			// znormalizuj dany wiersz (na diagonalnej musza byc same 1)
			typ_danych pierwszy = mat.element(i, i);

			try {
				if (pierwszy == 0) throw n;
				skalujWiersz(i, 1.0 / pierwszy);

				// uzyj i-tego wiersza do wyeliminowania wszystkich pozostalych
				for (int j = 0; j < n; ++j) {
					if (i == j) continue; // nie wyeliminuj siebie
					// przemnoz wiersz przez te wartosc, by wyeliminowac element na i-tym miejscu
					double skala = -1.0 * mat.element(j, i);
					addWiersze(i, j, skala);
				}
			}
			catch (int kod) { x = i; }

			if (pierwszy == 1) x = 0;
		}
	} while (x != 0);
}
