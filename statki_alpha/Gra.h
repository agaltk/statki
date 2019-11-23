#pragma once
#include "Gracz.h"

enum AKCJA {MENU,GRA_DALEJ,WYGRAL_GRACZ,WYGRAL_KOMPUTER}; //potrzebne do zwracania w StrzalGracz i komputer


class Gra
{
private:
	int PustaPlansza[10][10];
	Lista lista; //wszystkie wspolrzedne
	Lista *ustawianie; //wspolrzedne na ktorych mozna postawic i-ty statek
	POZIOM poziom;
	
public:
	Gra(INFO info);
	bool CzyWygral(Gracz gracz);
	AKCJA StrzalKomputer(Ekran &ekran,int &i,int &j,Gracz &gracz); //zwroci true jesli trafiony 
	AKCJA StrzalGracz(Ekran &ekran,int &ii, int &jj, Gracz &gracz);
	void OtoczZatopiony(int j,Gracz &gracz,int typ,int ust); 
	bool CzyZatopiony(int j,Gracz &gracz);//sprawdza czy zatopiony po ilosc pol nietrafionych i jesli 0 to ustawia ze statek zatopniony i zwraca true
	

	void Wyswietl(Gracz gracz,int STRONA);
	
	void losujXY(int &x,int &y,int i,int n);
	
	~Gra(void);
};

