#include <iomanip>
#include <iostream>
#include "Macierz.h"

template<typename typ_danych>
void Macierz<typ_danych>::alokacja()
{
	dane = new typ_danych[ile_wierszy * dlugosc_wiersza];
	wiersze = new typ_danych*[ile_wierszy];

	for (int i = 0; i < ile_wierszy; ++i) {
		wiersze[i] = (dane + i * dlugosc_wiersza);
	}
}

template<typename typ_danych>
void Macierz<typ_danych>::zeruj() {
  for (int i = 0; i < ile_wierszy*dlugosc_wiersza; ++i) {
    dane[i] = 0;
  }
}

template<typename typ_danych>
void Macierz<typ_danych>::pokaz() const {
  using std::cout;
  using std::endl;
  using std::setw;
  using std::fixed;
  using std::setprecision;
  for (int i = 0; i < ile_wierszy; ++i) {
    for (int j = 0; j < dlugosc_wiersza - 1; ++j) {
      cout << setw(8) << setprecision(4) << fixed << wiersze[i][j];
    }
    cout << "  |" << setw(8) << setprecision(4) << wiersze[i][dlugosc_wiersza - 1] << endl;
  }
}

