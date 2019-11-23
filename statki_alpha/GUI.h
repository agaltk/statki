#pragma once
#include "Gra.h"

class GUI
{
private:
	ALLEGRO_DISPLAY *display;

	ALLEGRO_BITMAP *start;
	ALLEGRO_BITMAP *ustawienia;
	ALLEGRO_BITMAP *koniec;
	ALLEGRO_BITMAP *statki;
	ALLEGRO_BITMAP *otaczanie;
	ALLEGRO_BITMAP *poziom;
	ALLEGRO_BITMAP *latwe_a;
	ALLEGRO_BITMAP *trudne_a;
	ALLEGRO_BITMAP *latwe_na;
	ALLEGRO_BITMAP *trudne_na;
	ALLEGRO_BITMAP *ot_automatyczne_a;
	ALLEGRO_BITMAP *ot_bez_a;
	ALLEGRO_BITMAP *ot_automatyczne_na;
	ALLEGRO_BITMAP *ot_bez_na;
	ALLEGRO_BITMAP *nacisniety;
	ALLEGRO_BITMAP *nienacisniety;
	ALLEGRO_BITMAP *wroc;
	ALLEGRO_BITMAP *zapisz;
	ALLEGRO_BITMAP* tlo;
	ALLEGRO_BITMAP *tlo2;
	ALLEGRO_BITMAP* spr_ust;
	ALLEGRO_BITMAP* dom;
	ALLEGRO_BITMAP *anuluj;
	ALLEGRO_BITMAP *gra_info;
	ALLEGRO_BITMAP *ekran_startowy;
	
	INFO info;
	bool klik;
	

	

public:
	
	GUI(void);
	void StartGra();
	bool Menu();
	void WyswietlMenu();
	void Ustawienia();
	void Poziom();
	void Statki();
	void UstawINFO(bool statki[5][5]);
	void Otaczanie();
	bool GRA();
	bool GraczUstaw(Gracz &gracz);
	bool Wygral(AKCJA akcja);
	void UstawieniaAktualne();
	void PrzywrocDomyslne();
	
	~GUI(void);
};

