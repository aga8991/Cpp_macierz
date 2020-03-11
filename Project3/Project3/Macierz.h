#include <iomanip>
#include <iostream>
#pragma once

template <typename typ_danych>
class Macierz {
  const int ile_wierszy;
  const int dlugosc_wiersza;
  typ_danych *dane;
  typ_danych **wiersze;

 public:
	Macierz(int _N) : ile_wierszy(_N), dlugosc_wiersza(_N + 1), dane(nullptr) {};
	void operator=(const Macierz& other_) = delete;
	Macierz(const Macierz& other_) = delete;

	void alokacja();
	void zeruj();
	void pokaz() const;

	int getIleWierszy() { 
		return ile_wierszy; 
	}
	typ_danych& element(int i, int j) {
		if (i > ile_wierszy || j > dlugosc_wiersza) throw 1;
		return wiersze[i][j]; 
	}

	typ_danych& wolny(int i) {
		if (i > ile_wierszy) throw 1;
		return wiersze[i][dlugosc_wiersza - 1];
	}
};

template<typename typ_danych>
void Macierz<typ_danych>::alokacja()
{
	dane = new typ_danych[ile_wierszy * dlugosc_wiersza];
	wiersze = new typ_danych * [ile_wierszy];

	for (int i = 0; i < ile_wierszy; ++i) {
		wiersze[i] = (dane + i * dlugosc_wiersza);
	}
}

template<typename typ_danych>
void Macierz<typ_danych>::zeruj() {
	for (int i = 0; i < ile_wierszy * dlugosc_wiersza; ++i) {
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