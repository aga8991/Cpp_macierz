#include <iostream>
#include "Macierz.h"
#include "Solver.h"
#include <exception>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>


void usun_znak_ze_strumienia(int kod_ASCII, std::string& strumien, bool czy_wstawiac_spacje);
void wczytaj_zmienne(std::string& strumien, int _ilosc_wierszy, char* zmienne);
template <typename typ_danych>
void odczyt_z_pliku(std::ifstream& plik);
int drukuj_menu();
int obsluga_pliku(std::ifstream& plik);
std::string usun_znaki_wez_zmienne(std::string& strumien, int _ilosc_wierszy, char* tab_zmienych);


int main()
{
	while (1)
	{
		system("cls");
		std::ifstream plik;

		switch (drukuj_menu())
			{
			case 1:
			{
				int x = obsluga_pliku(plik);

				if (x == 1)
				{
					odczyt_z_pliku<float>(plik);
				}
				if (x == 2)
				{
					odczyt_z_pliku<double>(plik);
				}
				if (x == 3)
				{
					odczyt_z_pliku<int>(plik);
				}
				break;
			}
			case 2:
			{
				return 0;
				break;
			}
		}
	}
}

void usun_znak_ze_strumienia(int kod_ASCII, std::string& strumien, bool czy_wstawiac_spacje)
{
	for (int i = 0; i < strumien.size(); i++)
	{
		if (strumien[i] == kod_ASCII)
		{
			int znaleziono = i;
			strumien.erase(znaleziono, 1);

			if (czy_wstawiac_spacje)
			{
				strumien.insert(znaleziono, " ");
			}
		}
	}
}

void wczytaj_zmienne(std::string& strumien, int _ilosc_wierszy, char* zmienne)
{
	char znak;
	int x = 0;

	for (int i = 1; i < strumien.size(); i++)
	{
		znak = strumien[i - 1];
		if ((znak >= 48 && znak <= 57) && (strumien[i] > 64 && strumien[i] < 123))
		{
			if (x + 1 <= _ilosc_wierszy)
			{
				zmienne[x] = strumien[i];
				x++;
			}
			strumien.erase(i, 1);
		}
	}
}

std::string usun_znaki_wez_zmienne(std::string& strumien, int _ilosc_wierszy, char* tab_zmienych)
{
	usun_znak_ze_strumienia(42, strumien, false);	//usuwa gwiazdki
	usun_znak_ze_strumienia(' ', strumien, false);  //usuwa spacje

	wczytaj_zmienne(strumien, _ilosc_wierszy, tab_zmienych);

	usun_znak_ze_strumienia(61, strumien, true);   //usuwa =
	usun_znak_ze_strumienia(43, strumien, true);   //usuwa +

	return strumien;
}

template <typename typ_danych>
void odczyt_z_pliku(std::ifstream & plik)
{
	std::string	wczytywany_wiersz;
	std::stringstream ciag_wczytanych_znakow;
	int	ilosc_wczytanych_wierszy = 0;

	while (std::getline(plik, wczytywany_wiersz))
	{
		ilosc_wczytanych_wierszy++;
		ciag_wczytanych_znakow << wczytywany_wiersz << "\n";
	}

	Macierz<typ_danych> macierz(ilosc_wczytanych_wierszy - 1);		// - 1 poniewaz pierwszy znak byl liter¹
	try
	{
		macierz.alokacja();
	}
	catch (std::bad_alloc) { std::cout << "Blad alokacji"; return; }

	char* tab_zmiennych;

	try
	{
		tab_zmiennych = new char[ilosc_wczytanych_wierszy - 1];
		tab_zmiennych[0] = (char)0;
	}
	catch (std::bad_alloc) { tab_zmiennych = nullptr; }

	std::string przetwarzane_dane = ciag_wczytanych_znakow.str();
	std::string czysty_strumien = usun_znaki_wez_zmienne(przetwarzane_dane, ilosc_wczytanych_wierszy - 1, tab_zmiennych);
	std::stringstream dane2;
	dane2 << czysty_strumien.c_str();

	typ_danych liczba;
	std::vector<typ_danych>	dane;

	for (int i = 0; i < (ilosc_wczytanych_wierszy * (ilosc_wczytanych_wierszy - 1)); i++)
	{
		dane2 >> liczba;		//wczytanie liczb i dodanie do wektora
		dane.push_back(liczba);
	}

	for (int i = (ilosc_wczytanych_wierszy - 1); i > 0; i--)
	{
		try
		{ 
		macierz.wolny(i - 1) = dane.back();
		dane.pop_back();
		}
		catch (...) { std::cout << "Niepoprawna wspolrzedna macierzy. \n"; }

		for (int j = (ilosc_wczytanych_wierszy - 1); j > 0; j--)
		{
			try
			{
				macierz.element(i - 1, j - 1) = dane.back();
				dane.pop_back();
			}
			catch (...) { std::cout << "Bledne wspolrzedne macierzy. \n"; }
		}
	}

	macierz.pokaz();
	std::cout << std::endl;
	Solver<typ_danych> solver_macierzy(macierz);
	solver_macierzy.rozwiaz();
	std::cout << "\nSprowadzenie do macierzy jednostkowej: " << std::endl;
	macierz.pokaz();
	
	if (tab_zmiennych != nullptr)
	{
		if (tab_zmiennych[0] != 0)
		{
			std::cout << "\nWynik: " << std::endl;
			for (int i = 0; i < ilosc_wczytanych_wierszy - 1; i++)
			{
				std::cout << tab_zmiennych[i] << " = " << macierz.element(i, ilosc_wczytanych_wierszy - 1) << "   ";
			}
		}
		delete[] tab_zmiennych;
	}

	std::cout << std::endl << std::endl;
	system("PAUSE");
}

int drukuj_menu()
{
	int x = 0;
	do
	{
		std::cout << "\t*Menu uzytkownika*\n" << std::endl << "1. Wczytaj macierz lub rownanie\n2. Zakoncz\n\n\tWybieram: ";
		std::cin >> x;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(100, '\n');
		}
	} while (x > 2 && x < 0);
	return x;
}

int obsluga_pliku(std::ifstream & plik)
{
	std::string nazwa_pliku;
	char typ;

	std::cout << "\nNazwa pliku: ";
	std::cin >> nazwa_pliku;
	nazwa_pliku += ".txt";

	plik.open(nazwa_pliku.c_str(), std::ifstream::in);
	if (!plik.fail())
	{
		plik >> typ;
		if (typ == 'F')
		{
			return 1;
		}
		else if (typ == 'D')
		{
			return 2;
		}
		else if (typ == 'I')
		{
			return 3;
		}
		else std::cout << "Wybrany plik jest bledny." << std::endl;
		plik.close();
		system("pause");
	}
	else
	{
		std::cout << "Nie udalo sie otworzyc pliku." << std::endl;
		system("pause");
		return 0;
	}
}