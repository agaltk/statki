#include "GUI.h"


GUI::GUI(void)
{
	al_init();			
	al_init_image_addon();
	display = al_create_display(640,480 );

	start = al_load_bitmap("obrazki\\start.jpg");
	ustawienia = al_load_bitmap("obrazki\\ustawienia.jpg");
	koniec = al_load_bitmap("obrazki\\koniec.jpg");
	statki = al_load_bitmap("obrazki\\statki.jpg");
	otaczanie = al_load_bitmap("obrazki\\otaczanie.jpg");
	poziom = al_load_bitmap("obrazki\\poziom.jpg");
	latwe_a = al_load_bitmap("obrazki\\latwe.jpg");
	trudne_a = al_load_bitmap("obrazki\\trudny.jpg");
	latwe_na = al_load_bitmap("obrazki\\latwe_na.jpg");
	trudne_na = al_load_bitmap("obrazki\\trudny_na.jpg");
	ot_automatyczne_a = al_load_bitmap("obrazki\\ot_auto.jpg");
	ot_bez_a = al_load_bitmap("obrazki\\ot_bez.jpg");
	ot_automatyczne_na = al_load_bitmap("obrazki\\ot_auto_na.jpg");
	ot_bez_na = al_load_bitmap("obrazki\\ot_bez_na.jpg");
	nacisniety = al_load_bitmap("obrazki\\st_nacisniety.jpg");
	nienacisniety = al_load_bitmap("obrazki\\st_nie.jpg");
	zapisz = al_load_bitmap("obrazki\\zapisz.jpg");
	wroc = al_load_bitmap("obrazki\\wroc.jpg");
	tlo = al_load_bitmap("obrazki\\tlo.jpg");
	tlo2 = al_load_bitmap("obrazki\\tlo2.jpg");
	spr_ust = al_load_bitmap("obrazki\\spr_ust.jpg");
	dom = al_load_bitmap("obrazki\\domyslne.jpg");
	anuluj = al_load_bitmap("obrazki\\anuluj.jpg");
	gra_info = al_load_bitmap("obrazki\\info.jpg");
	ekran_startowy = al_load_bitmap("obrazki\\ekran_startowy.jpg");
	
	info.ilosc=10;
	info.dlugosci=new int [info.ilosc];
	int temp[] = {4,3,3,2,2,2,1,1,1,1};
	for(int i=0;i<10;i++) info.dlugosci[i]=temp[i];
	info.OTACZANIE_AUTOMATYCZNE = true;
	info.poziom = HARD;
	klik = true;

}

GUI::~GUI(void)
{
	al_destroy_bitmap(start);
	al_destroy_bitmap(ustawienia);
	al_destroy_bitmap(koniec);
	al_destroy_bitmap(statki);
	al_destroy_bitmap(otaczanie);
	al_destroy_bitmap(poziom);
	al_destroy_bitmap(latwe_a);
	al_destroy_bitmap(latwe_na);
	al_destroy_bitmap(trudne_a);
	al_destroy_bitmap(trudne_na);
	al_destroy_display(display);
	al_destroy_bitmap(nacisniety);
	al_destroy_bitmap(nienacisniety);
	al_destroy_bitmap(zapisz);
	al_destroy_bitmap(wroc);
	al_destroy_bitmap(spr_ust);
	al_destroy_bitmap(dom);
	al_destroy_bitmap(anuluj);
	al_destroy_bitmap(gra_info);
	al_destroy_bitmap(ot_automatyczne_a);
	al_destroy_bitmap(ot_automatyczne_na);
	al_destroy_bitmap(ot_bez_a);
	al_destroy_bitmap(ot_bez_na);
	al_destroy_bitmap(ekran_startowy);
	delete[] info.dlugosci;
	
}

void GUI::StartGra()
{
	Ekran ekran;
	al_draw_bitmap(ekran_startowy,0,0,0);
	al_flip_display();
	while(ekran.MyszButton()!=1)
	{
		ekran.Mysz();
	}
			
	
	while(1)
	{
		if(Menu())// Menu - return tur - zaczyna sie GRA
		{
			if(GRA()); //GRA - return true - wraca do Menu
			else return; //GRA - return fasle - ktos wygral i konczy program
		}
		else return; //Menu - return false - Koniec prograu
	}
	
	
}
bool GUI::Menu()
{
	Ekran ekran; 
	int x,y,przycisk;
	klik = false;
	
	while(1)
	{
		
		WyswietlMenu();
		ekran.Mysz();
		if((przycisk=ekran.MyszButton())==0)klik=true;
		if((przycisk=ekran.MyszButton())==1&&klik)
		{
			x = ekran.MyszX();
			y = ekran.MyszY();
			if(x>=240&&x<=400)
			{
				if(y>=50&&y<=110){klik = false; return true;}
				else if(y>=130&&y<=190){klik = false; Ustawienia();}
				else if(y>=210&&y<=270){klik = false; return false;}
			}
		}
	}
}
void GUI::WyswietlMenu()
{	
	al_clear_to_color( al_map_rgb(116,186,224) ); //tlo ekranu
	al_draw_bitmap(tlo,0,0,0);
	
	al_draw_bitmap(start,240,50,0);
	al_draw_bitmap(ustawienia,240,130,0);
	al_draw_bitmap(koniec,240,210,0);

	al_flip_display();
}

void GUI::Ustawienia()
{	
	Ekran ekran;
	int x,y;
	
	while(1)
	{
		al_draw_bitmap(tlo,0,0,0);
		al_draw_bitmap(otaczanie,240,50,0);
		al_draw_bitmap(statki,240,130,0);
		al_draw_bitmap(poziom,240,210,0);
		al_draw_bitmap(spr_ust,240,290,0);
		al_draw_bitmap(wroc,460,360,0);
		
		al_flip_display();


		ekran.Mysz();
		if(ekran.MyszButton() ==0) klik = true;
		if(ekran.MyszButton()==1&&klik)
		{
			klik = false;
			x = ekran.MyszX();
			y = ekran.MyszY();
			if(x>=460&&x<=620&&y>=360&&y<=420) return; 
			if(x>=240&&x<=400)
			{
				if(y>=50&&y<=110) Otaczanie();
				else if(y>=130&&y<=190) Statki(); 
				else if(y>=210&&y<=270) Poziom();
				else if(y>=290&&y<=350) UstawieniaAktualne();
			}
		}
	}

}

void GUI::Statki()
{
	
	Ekran ekran;
	bool statki[5][5],domyslne = false;
	int dl=0;

	al_draw_bitmap(tlo,0,0,0);
	int st=0;
	for(int i=0;i<5;i++)
		for(int j=0;j<5;j++)
		{
			if(info.dlugosci[st]==5-i) 
			{
				statki[i][j] = true;
				if(st<info.ilosc)st++;
			}
			else statki[i][j]=false;

			if(j==4&&i==0);
			else if(statki[i][j])al_draw_bitmap(nacisniety,200+60*j,50+60*i,0);
			else al_draw_bitmap(nienacisniety,200+60*j,50+60*i,0);
		}
	for(int i=0;i<info.ilosc;i++)
	dl += info.dlugosci[i];

	ekran.Tekst(140,55,"5");
	ekran.Tekst(140,115,"4");
	ekran.Tekst(140,175,"3");
	ekran.Tekst(140,235,"2");
	ekran.Tekst(140,295,"1");
	ekran.TekstM(270,10,"ILOSC STATKOW"); 
	ekran.TekstM(260,30,"(MAX SUMA DLUGOSCI 1 - 25)");
	ekran.TekstM(140,10,"ILOSC");
	ekran.TekstM(120,30,"MASZTOW");

	ekran.TekstM(100,350,"UWAGA");
	ekran.TekstM(100,370,"KAZDA KRATKA TO JEDEN");
	ekran.TekstM(100,390,"STATEK DANEJ DLUGOSCI");
	al_draw_bitmap(anuluj,460,360,0);
	al_draw_bitmap(zapisz,290,360,0);
	
	al_flip_display();

	
	int x,y;
	
	while(1)
	{
		
		ekran.Mysz();
		if(ekran.MyszButton()==1&&klik)
		{
			klik = false;
			x=ekran.MyszX();
			y=ekran.MyszY();
			if(x>=460&&x<=620&&y>=360&&y<=420) 
				return;
			if(x>=290&&x<=450&&y>=360&&y<=420&&dl>0) 
			{
				UstawINFO(statki);
				return;
			}
			int i=0,j=0;
			while(i<5)
			{	
				for(j=0;j<5;j++)
				{
					if(j==4)i++;
					if(i>4);
					else if(i==0&&j==4){i=5;j=5;}
					else if((((x-220-j*60)/40)==0)&&(((y-50-i*60)/40)==0))
					{
					  if(!statki[i][j]&&(dl+5-i)>info.MAX);
					  else 
					  {
						statki[i][j]=!statki[i][j];
					  
						if(statki[i][j]) dl+=5-i;
						else dl-=5-i;

						if(statki[i][j]) al_draw_bitmap(nacisniety,200+60*j,50+60*i,0);
						else if(!statki[i][j]) al_draw_bitmap(nienacisniety,200+60*j,50+60*i,0);

						al_flip_display();

						}
					  i=5;
						j=5;
					 }
				}
			}
	

		}
		if(ekran.MyszButton()==0) klik = true;

	}
}

void GUI::UstawINFO(bool statki[5][5])
{

	int ilosc=0,licz=0;
	for(int i=0;i<5;i++)
		for(int j=0;j<5;j++)
			if(statki[i][j])ilosc++;

	info.ilosc=ilosc;
	info.dlugosci = new int[info.ilosc];
	for(int i=0;i<5;i++)
		for(int j=0;j<5;j++)
			if(statki[i][j])
			{
				info.dlugosci[licz]=5-i;
				licz++;
			}
		

}

void GUI::Otaczanie()
{
	Ekran ekran;
	int x,y,przycisk=0;
	
	while(1)
	{
		al_draw_bitmap(tlo,0,0,0);
		if(info.OTACZANIE_AUTOMATYCZNE)
		{
			al_draw_bitmap(ot_automatyczne_a,240,50,0);
			al_draw_bitmap(ot_bez_na,240,130,0);
		}
		else if(!info.OTACZANIE_AUTOMATYCZNE)
		{
			al_draw_bitmap(ot_automatyczne_na,240,50,0);
			al_draw_bitmap(ot_bez_a,240,130,0);
		}
		al_draw_bitmap(wroc,460,360,0);
		
		al_flip_display();


		ekran.Mysz();
		if((przycisk=ekran.MyszButton())==0) klik = true;
		if((przycisk=ekran.MyszButton())==1&&klik)
		{
			klik = false;
			x = ekran.MyszX();
			y = ekran.MyszY();

			if(x>=460&&x<=620&&y>=360&&y<=420) 
				return;
			if(x>=240&&x<=400)
			{
				if(y>=50&&y<=110) info.OTACZANIE_AUTOMATYCZNE = true;
				else if(y>=130&&y<=190) info.OTACZANIE_AUTOMATYCZNE = false;
			}
			
		}
	}
}

void GUI::Poziom()
{
		Ekran ekran;
	int x,y,przycisk=0;
	
	while(1)
	{
		al_draw_bitmap(tlo,0,0,0);
		if(info.poziom==HARD)
		{
			al_draw_bitmap(trudne_a,240,50,0);
			al_draw_bitmap(latwe_na,240,130,0);
		}
		else if(info.poziom==EASY)
		{
			al_draw_bitmap(trudne_na,240,50,0);
			al_draw_bitmap(latwe_a,240,130,0);
		}
		al_draw_bitmap(wroc,460,360,0);
		
		al_flip_display();


		ekran.Mysz();
		if((przycisk=ekran.MyszButton())==0) klik = true;
		if((przycisk=ekran.MyszButton())==1&&klik)
		{
			klik = false;
			x = ekran.MyszX();
			y = ekran.MyszY();

			if(x>=460&&x<=620&&y>=360&&y<=420) 
				return;
			if(x>=240&&x<=400)
			{
				if(y>=50&&y<=110) info.poziom = HARD;
				else if(y>=130&&y<=190) info.poziom = EASY;
			}
			
		}
	}
}
bool GUI::GRA()
{
	Gracz komputer(info); 
	while(!komputer.UstawLosowo());  
	Gra KPusta(info); 
	
	Ekran ekran1;
	ekran1.inf(info);
	
	
	
	Gracz gracz(info); 
	gracz.init(); 
	Gra GPusta(info); 
	if(GraczUstaw(gracz));
	else return true;
		
	enum AKCJA akcja;
		
	ekran1.Statki();
	Ekran ekran;

	int ii=0,jj=0,x=0,y=0;
	gracz.Wyswietl(L);
	ekran.Linie(L);
	ekran.Linie(P);

	while(1)
	{
		al_flip_display();
		
		
		
		akcja = GPusta.StrzalGracz(ekran,ii,jj,komputer);
		if(akcja==GRA_DALEJ) akcja = KPusta.StrzalKomputer(ekran,x,y,gracz);
		if(akcja==GRA_DALEJ);
		else if(akcja==MENU) return true;
		else if(akcja==WYGRAL_GRACZ||akcja==WYGRAL_KOMPUTER)
		{
			if(akcja==WYGRAL_KOMPUTER) ekran.Tekst(100,145,"WYGRAL KOMPUTER",237,237,140);
			else if(akcja==WYGRAL_GRACZ)ekran.Tekst(100,145,"WYGRAL GRACZ",237,237,140);
			ekran.TekstM(20,245,"NACISNIJ LEWY PRZYCISK MYSZKI ABY KONTYNUOWAC...",255,255,255);
			al_flip_display();

			klik = false;
			bool done = true;
			while(done)
			{
				ekran.Mysz();
				if(ekran.MyszButton()==0) klik = true;
				while(ekran.MyszButton()==0&&klik)
				{
					ekran.Mysz();
					done = false;

				}
			}
			if(Wygral(akcja))return true;
			else return false;
			
		}
		
	}
	
	
}

bool GUI::Wygral(AKCJA akcja)
{
	Ekran ekran;
	ALLEGRO_BITMAP *komp = al_load_bitmap("obrazki\\wygral_komputer.jpg");
	ALLEGRO_BITMAP *gr = al_load_bitmap("obrazki\\wygral_gracz.jpg");
	ALLEGRO_BITMAP *tak = al_load_bitmap("obrazki\\tak.jpg");
	ALLEGRO_BITMAP *nie = al_load_bitmap("obrazki\\nie.jpg");
	
	
	
	
	
		
	if(akcja==WYGRAL_KOMPUTER) 
	{
		al_draw_bitmap(komp,0,0,0);
	}
	else if(akcja==WYGRAL_GRACZ)
	{
		al_draw_bitmap(gr,0,0,0);
	}
	
	al_draw_bitmap(tak,250,150,0);
	al_draw_bitmap(nie,350,150,0);
	al_flip_display();
	int x=-1,y=-1;
	klik = false;
	while(1)
	{	
		ekran.Mysz();
		if(ekran.MyszButton()==0)klik=true;
		if(ekran.MyszButton()==1&&klik)
		{
			x=ekran.MyszX();
			y=ekran.MyszY();

			if((y-150)/32==0)
				if(((x-250)/73)==0)
				{
					al_destroy_bitmap(komp);
					al_destroy_bitmap(tak);
					al_destroy_bitmap(nie);
					al_destroy_bitmap(gr);
					return true;
				}
				else if(((x-350)/73)==0)
				{
					al_destroy_bitmap(komp);
					al_destroy_bitmap(tak);
					al_destroy_bitmap(nie);
					al_destroy_bitmap(gr);
					return false;
				}


		}

	}
	
	
	
}

bool GUI::GraczUstaw(Gracz &gracz)
{
	Ekran ekran;
	ekran.inf(info);
	al_draw_bitmap(tlo2,0,0,0);
	int x=-1,y=-1;

	ekran.Linie(L);
	ekran.Linie(P);
	gracz.Wyswietl(L);
	ekran.Statki();
	al_draw_bitmap(gra_info,280,40,0);
	ekran.Info();
	al_flip_display();

	if(gracz.UstawMyszka()) return true;
	else return false;

}

void GUI::UstawieniaAktualne()
{
	Ekran ekran;
	char temp[][2] = {"0","1","2","3","4","5"};
	int zm;
	al_draw_bitmap(tlo,0,0,0);
	al_draw_bitmap(wroc,460,360,0);
	al_draw_bitmap(dom,290,360,0);
	ekran.Tekst(200,10,"Ustawienia aktualne:");
	ekran.Tekst(100,50,"Poziom:");
		if(info.poziom==HARD) ekran.Tekst(220,50,"TRUDNY");
		else if(info.poziom==EASY) ekran.Tekst(220,50,"LATWY");
	ekran.Tekst(100,90,"Otaczanie:");
		if(info.OTACZANIE_AUTOMATYCZNE) ekran.Tekst(220,90,"AUTOMATYCZNE");
		else if(!info.OTACZANIE_AUTOMATYCZNE) ekran.Tekst(220,90,"BRAK");
	ekran.Tekst(100,130,"Ilosc masztow");
	ekran.Tekst(300,130,"Ilosc statkow");
	for(int i=0;i<5;i++)
		{
			zm=0;
			ekran.Tekst(150,170+i*30,temp[5-i]);
			
			for(int j=0;j<info.ilosc;j++)
				if(info.dlugosci[j]==5-i) zm++;
			ekran.Tekst(350,170+30*i,temp[zm]);
		}
	al_flip_display();
	klik = false;
	int ilosc=0;
	while(1)
	{
		if(ilosc!=0)
		{
			ilosc--;
			return;
		}
		ekran.Mysz();
		if(ekran.MyszButton()==0) klik = true;
		if(ekran.MyszButton()==1&&klik)
		{
			klik = false;
			int x = ekran.MyszX();
			int y = ekran.MyszY();
			if(x>=460&&x<=620&&y>=360&&y<=420)return;
			if(x>=290&&x<=450&&y>=360&&y<=420){ PrzywrocDomyslne();UstawieniaAktualne();ilosc++;}
		}	
	}
}

void GUI::PrzywrocDomyslne()
{
	info.ilosc=10;
	info.dlugosci=new int [info.ilosc];
	int temp[] = {4,3,3,2,2,2,1,1,1,1};
	for(int i=0;i<10;i++) info.dlugosci[i]=temp[i];
	
	info.OTACZANIE_AUTOMATYCZNE = true;
	info.poziom = HARD;
	klik = true;
}

