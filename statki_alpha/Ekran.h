#pragma once


#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>

#pragma comment (lib,"allegro-5.0.4-monolith-mt-debug.lib")
#pragma comment (lib,"allegro_ttf-5.0.4-mt-debug.lib")
#pragma comment (lib,"allegro_font-5.0.4-mt-debug.lib")


#define K 1
#define P 1 
#define G 0
#define L 0
#define BP 20 //szerokosc bitmapy z elelementem planszy do wyswietlenia



enum POZIOM{EASY,HARD};

typedef struct
{
	int ilosc;
	POZIOM poziom;
	int *dlugosci;
	static const int MAX=25;
	bool OTACZANIE_AUTOMATYCZNE;
	
}INFO;


class Ekran
{
private:
	ALLEGRO_FONT *font1;
	ALLEGRO_FONT *font2;
	ALLEGRO_BITMAP *woda;
	ALLEGRO_BITMAP *statek;
	ALLEGRO_BITMAP *puste;
	ALLEGRO_BITMAP *strzelony;
	ALLEGRO_BITMAP *trafiony;
	ALLEGRO_BITMAP *zatopiony;
	ALLEGRO_BITMAP *menu;
	ALLEGRO_BITMAP *statki[5];
	ALLEGRO_BITMAP *tlo2_k;
	ALLEGRO_BITMAP *ust_los;


	ALLEGRO_MOUSE_STATE mouse_state;		//myszka

	int dane[11];


public:
	Ekran();
	~Ekran(void);



	void inf(INFO info);
	
	bool MyszkaXY(int &x,int &y,int strona);

	void Statki();
	void Wyswietl(int plansza[10][10],int typ);
	void Linie(int strona);
	void Tekst(int x,int y, char napis[50],int r=0, int g=0 ,int b=0);
	
	void Info();
	void TekstM(int x,int y, char napis[50],int r=0, int g=0 ,int b=0);
	
	
	
	void Mysz(){al_get_mouse_state(&mouse_state);}
	int MyszButton(){return mouse_state.buttons;}
	int MyszX(){return mouse_state.x;}
	int MyszY(){return mouse_state.y;}

	







};

