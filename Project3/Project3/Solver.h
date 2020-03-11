#pragma once
#include "Macierz.h"
#include <iostream>
#include <exception>

template<typename typ_danych>
class Solver 
{
  Macierz<typ_danych>& mat;
  const int n;

  void skalujWiersz(int ktory, double skala);
  void addWiersze(int ktory, int do_ktorego, typ_danych skala = 1.0);

 public:
  Solver(Macierz<typ_danych>& mat_) : mat(mat_), n(mat.getIleWierszy()) {}

  void rozwiaz();
};


template<typename typ_danych>
//void Solver<typ_danych>::skalujWiersz(int ktory, typ_danych skala)
void Solver<typ_danych>::skalujWiersz(int ktory, double skala)
{
	for (int i = 0; i < n + 1; ++i) {
		mat.element(ktory, i) *= skala;
	}
}

template<typename typ_danych>
void Solver<typ_danych>::addWiersze(int ktory, int do_ktorego, typ_danych skala) 
{
	for (int i = 0; i < n + 1; ++i) {
		mat.element(do_ktorego, i) += skala * mat.element(ktory, i);
	}
}

template<typename typ_danych>
void Solver<typ_danych>::rozwiaz() 
{
	int x = 0;
	do {
		for (int i = 0; i < n; ++i) {
			typ_danych pierwszy = mat.element(i, i);

			try {
				if (pierwszy == 0) throw n;
				skalujWiersz(i, 1.0 / pierwszy);

				for (int j = 0; j < n; ++j) {
					if (i == j) continue;
					double skala = -1.0 * mat.element(j, i);
					addWiersze(i, j, skala);
				}
			}
			catch (int kod) { x = i; }

			if (pierwszy == 1) x = 0;
		}
	} while (x != 0);
}
