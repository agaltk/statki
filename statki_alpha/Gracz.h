#pragma once
#include "Lista.h"
#include "Ekran.h"

#include <time.h>

typedef struct
{
	int wartosc;
	int nrStatku;	
}POLE;

typedef struct
{
	bool zatopiony;
	int dlugosc;
	int zostaloPolNietrafionych;
	Lista polozenie;
}STATEK;

class Gracz
{
private:
	POLE plansza[10][10];
	STATEK *wszystkie;
	int ilosc;
	Lista lista; //wszystkie wspolrzedne
	Lista *ustawianie; //wspolrzedne na ktorych mozna postawic i-ty statek
	bool otaczanie;
	
public:
		
	void init();
	bool UstawLosowo();
	bool UstawMyszka();

	void UstawStatek(int x, int y, int i);
	
	
	bool CzyPoprawnie(int x,int y,int j);
	bool CzySaTrojki();

	void Wyswietl(int STRONA);
	void Zmiana(void);
	void losujXY(int &x,int &y,int i,int n);

	
	//plansza
	int Wartosc(int x,int y) {return plansza[x][y].wartosc;}
	void Wartosc(int x,int y, int war){plansza[x][y].wartosc=war;}
	int Nr(int x,int y) {return plansza[x][y].nrStatku;}
	void Nr(int x,int y, int war){plansza[x][y].nrStatku=war;}
	
	//wszystkie
	bool Zatopiony(int i) {return wszystkie[i].zatopiony;}
	void Zatopiony(int i, bool zm){wszystkie[i].zatopiony=zm;}
	int DL(int i) {return wszystkie[i].dlugosc ;}
	void DL(int i, int war){wszystkie[i].dlugosc=war;}
	int ZPN(int i) {return wszystkie[i].zostaloPolNietrafionych;}
	void ZPN(int i, int war){wszystkie[i].zostaloPolNietrafionych-=war;}

	void PolozenieNaKoniec(int i,int war){wszystkie[i].polozenie.DodajNaKoniec(war);}
	void PolozenieUsunElement(int i, int war){wszystkie[i].polozenie.UsunWybrany(war);}
	int PolozenieElement(int i, int j){return wszystkie[i].polozenie.Zwroc(j);}

	bool OTACZANIE(){return otaczanie;}
	int Ilosc(){return ilosc;}
	Gracz(INFO info);
	~Gracz(void);
};

