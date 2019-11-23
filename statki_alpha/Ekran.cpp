#include "Ekran.h"

Ekran::Ekran()
{
	al_init();				/// Instalowanie : allegro
	al_init_image_addon();	// obrazkow
	al_install_mouse();		//myszki
	al_init_font_addon(); //fonty 
	al_init_ttf_addon();  //ttf-y

	font1 = al_load_ttf_font("piece.ttf",15,0);
	font2 = al_load_ttf_font("piece.ttf",30,0);
	woda = al_load_bitmap("obrazki\\woda.jpg");
	statek = al_load_bitmap("obrazki\\statek.jpg");
	puste = al_load_bitmap("obrazki\\puste.jpg");
	strzelony = al_load_bitmap("obrazki\\strzelony.jpg");
	trafiony = al_load_bitmap("obrazki\\trafiony.jpg");
	menu = al_load_bitmap("obrazki\\menu.jpg");
	zatopiony = al_load_bitmap("obrazki\\zatopiony.jpg");
	tlo2_k = al_load_bitmap("obrazki\\tlo2_kawalek.jpg");
	ust_los = al_load_bitmap("obrazki\\ust_los.jpg");

	statki[0] = al_load_bitmap("obrazki\\1_ust.jpg");
	statki[1] = al_load_bitmap("obrazki\\2_ust.jpg");
	statki[2] = al_load_bitmap("obrazki\\3_ust.jpg");
	statki[3] = al_load_bitmap("obrazki\\4_ust.jpg");
	statki[4] = al_load_bitmap("obrazki\\5_ust.jpg");



	
}


Ekran::~Ekran(void)
{	
	
	al_destroy_font(font1);
	al_destroy_font(font2);
	al_destroy_bitmap(woda);
	al_destroy_bitmap(statek);
	al_destroy_bitmap(puste);
	al_destroy_bitmap(strzelony);
	al_destroy_bitmap(trafiony);
	al_destroy_bitmap(zatopiony);
	al_destroy_bitmap(menu);
	al_destroy_bitmap(tlo2_k);
	al_destroy_bitmap(ust_los);

	for(int i=0;i<5;i++)
	{
		al_destroy_bitmap(statki[i]);
	}
	
}

void Ekran::inf(INFO info)
{	
	int k=1,licz=1;	
	for(int i=0;i<info.ilosc;i++)
		{
			if(i+1!=info.ilosc&&info.dlugosci[i]==info.dlugosci[i+1]) k++;
			else
			{
				dane[licz]=k;
				k=1;
				licz++;
				dane[licz]=info.dlugosci[i];
				licz++;
			
			}
		}
		dane[0]=licz-1;
}


bool Ekran::MyszkaXY(int &x,int &y,int strona)
{
	int xx = mouse_state.x;
	int yy = mouse_state.y;
	x = (xx - 40 - 240*strona)/20;
	y = (yy - 40)/20;
	if(x>=0&&x<10&&y>=0&&y<10)return true;
	return false;		
}


void Ekran::Wyswietl(int plansza[10][10],int typ)
{
	int xx,yy;
																	///WYSWIETLA PLANSZE PRZEKAZANEGO GRACZA
		for(xx=0;xx<10;xx++)
		for(yy=0;yy<10;yy++)																							///
		{
			if(plansza[xx][yy]==0) al_draw_bitmap(woda,(40+(10*BP+40)*typ+BP*xx),(40+BP*yy),0); //puste pole nic nie ma
			else if(plansza[xx][yy]==1) al_draw_bitmap(woda,(40+(10*BP+40)*typ+BP*xx),(40+BP*yy),0); //otoczenie ustawionego statku
			else if(plansza[xx][yy]==2) al_draw_bitmap(statek,(40+(10*BP+40)*typ+BP*xx),(40+BP*yy),0); // statek ustawiony
			else if(plansza[xx][yy]==3) al_draw_bitmap(puste,(40+(10*BP+40)*typ+BP*xx),(40+BP*yy),0); // tam gdzie mozna postawic jeszcze statek w trakcie ustawiania
			else if(plansza[xx][yy]==4) al_draw_bitmap(woda,(40+(10*BP+40)*typ+BP*xx),(40+BP*yy),0); // "rogi" ustawianego statku
			else if(plansza[xx][yy]==5) al_draw_bitmap(strzelony,(40+(10*BP+40)*typ+BP*xx),(40+BP*yy),0); // pole strzelone ale nie ma tam statku
			else if(plansza[xx][yy]==6) al_draw_bitmap(trafiony,(40+(10*BP+40)*typ+BP*xx),(40+BP*yy),0); // pole strzelone i jest tam statek
			else if(plansza[xx][yy]==7) al_draw_bitmap(zatopiony,(40+(10*BP+40)*typ+BP*xx),(40+BP*yy),0); //statek zatopiony 
		}

		al_draw_bitmap(ust_los,460,320,0);
		al_draw_bitmap(menu,460,400,0);
		al_flip_display();

}
void Ekran::Linie(int strona)
{
	const char litery[][2] = {"A","B","C","D","E","F","G","H","I","J"};
	char cyfry[][3] = {"1","2","3","4","5","6","7","8","9","10"};
	for(int i=0;i<10;i++)
	{
		al_draw_text(font1,al_map_rgb( 255, 255, 0 ),strona*240+46+BP*i,21,0,litery[i]);
	}
	for(int i=0;i<10;i++)
		al_draw_text(font1,al_map_rgb( 255, 255, 0 ),strona*240+21,46+BP*i,0,cyfry[i]);
	al_draw_text(font1,al_map_rgb( 255, 255, 0 ),100,0,0,"GRACZ");
	al_draw_text(font1,al_map_rgb(255, 255, 0 ),320,0,0,"KOMPUTER");
	
	al_flip_display();

}

void Ekran::Tekst(int x,int y, char napis[50],int r, int g ,int b)
{
	al_draw_text(font2,al_map_rgb( r, g, b ),x,y,0,napis);
	al_flip_display();
}

void Ekran::TekstM(int x,int y, char napis[50],int r, int g ,int b)
{
	al_draw_text(font1,al_map_rgb( r, g, b ),x,y,0,napis);
	al_flip_display();
}


void Ekran::Statki()
{
	int k=1,i=0;
	char temp[][2] = {"0","1","2","3","4","5"};
	
	while(k<=dane[0])
	{
		Tekst(500,20+60*i,temp[dane[k]]);
		k++;
		al_draw_bitmap(statki[dane[k]-1],520,20+60*i,0);
		al_flip_display();
					k++;
					i++;
				
	}
}
void Ekran::Info()
{
	TekstM(10,300,"INFO:",255,247,85);
	al_draw_bitmap(woda,10,320,0);
	TekstM(35,320,"- PUSTE POLE",255,247,85);
	al_draw_bitmap(statek,10,345,0);
	TekstM(35,345,"- POSTAWIONY JEDEN MASZ STATKU",255,247,85);
	al_draw_bitmap(puste,10,370,0);
	TekstM(35,370,"- MIEJSCE DO POSTAWIENIA KOLEJNEGO MASZTU",255,247,85);
	al_draw_bitmap(strzelony,10,395,0);
	TekstM(35,395,"- STRZELONE POLE",255,247,85);
	al_draw_bitmap(trafiony,10,420,0);
	TekstM(35,420,"- TRAFIONY STATEK",255,247,85);
	al_draw_bitmap(zatopiony,10,445,0);
	TekstM(35,445,"- ZATOPIONY STATEK",255,247,85);
}

