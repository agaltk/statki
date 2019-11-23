#pragma once


class WAR
{
public:
	int x;
	WAR *Nastepny;
};

class Lista
{
private:
	WAR* Pierwszy;
	WAR* Ostatni;
	int ilosc;
public:
	Lista(void);
	~Lista(void);
	void Ilosc(int i);
	int Ilosc(void);
	void DodajNaKoniec (int x);
	void UsunPierwszy();
	void UsunOstatni();
	void UsunWybrany(int n);
	int Zwroc (int n);
	void Usun();
	int CzyJest(int wsp);


};

