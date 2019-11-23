#include "Gracz.h"


Gracz::Gracz(INFO info)
{
	ilosc = info.ilosc;
	wszystkie = new STATEK[ilosc];
	for(int i=0;i<ilosc;i++)
	{
		wszystkie[i].dlugosc = info.dlugosci[i];
		wszystkie[i].zatopiony = false;
		wszystkie[i].zostaloPolNietrafionych = info.dlugosci[i];
	}

	ustawianie = new Lista[ilosc];
	otaczanie = info.OTACZANIE_AUTOMATYCZNE;

}


Gracz::~Gracz(void)
{
}

void Gracz::init()
{
	int i,j;
	lista.Usun();
	if(wszystkie[0].polozenie.Ilosc()!=0)
	{
		
		for(i=0;i<ilosc;i++)
		{
			wszystkie[i].polozenie.Usun();
			ustawianie[i].Usun();
		}
	}
	
	for(i=0;i<100;i++) lista.DodajNaKoniec(i);
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
		{
			plansza[i][j].wartosc=0;
			plansza[i][j].nrStatku=0;
		}
		
}


bool Gracz::UstawLosowo()
{
	int x=0,y=0,ii,jj;
	init();
	
	for(ii=0;ii<ilosc;ii++)		//ustawia "ilosc" statkow
		{
			for(jj=0;jj<wszystkie[ii].dlugosc;jj++) // ustawia od 0 do dlugosci statku
			{
				if(!CzySaTrojki()&&DL(ii)!=1&&jj!=0) return false;
				losujXY(x,y,ii,jj);
				UstawStatek(x,y,ii);
				
				
			}
			Zmiana();
			ustawianie[ii].Usun();
		}
		
	lista.Usun();
	return true;
}


void Gracz::UstawStatek(int x,int y,int i)
{
	int ii,jj;
	plansza[x][y].wartosc = 2;
	wszystkie[i].polozenie.DodajNaKoniec(10*x+y);
	plansza[x][y].nrStatku = i;

	for(ii=(x-1);ii<(x+2);ii++)
		for(jj=(y-1);jj<(y+2);jj++)
			if((ii<10)&&(ii>-1)&&(jj<10)&&(jj>-1)&&(plansza[ii][jj].wartosc!=1)&&(plansza[ii][jj].wartosc!=2)) //jesli wspolrzedne sa w planszy
			{
				if(ii!=x&&jj!=y&&plansza[ii][jj].wartosc!=3) //jesli jest to pole sasiednie z ustawionym i nie jest tam nic ustawione
				{
					plansza[ii][jj].wartosc=4;
									
				}
				else if(plansza[ii][jj].wartosc!=3)
				{
					ustawianie[i].DodajNaKoniec(ii*10+jj);
					plansza[ii][jj].wartosc=3;
					
				}
				
			}		
}


void Gracz::Zmiana(void)
{
	int i,j;

	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			if(plansza[i][j].wartosc==3||plansza[i][j].wartosc==4) 
			{
				plansza[i][j].wartosc=1;
				lista.UsunWybrany(10*i+j);
			}
}

void Gracz::Wyswietl(int STRONA)
{
	Ekran ekran;
	int temp[10][10];
	for(int i=0;i<10;i++)
		for(int j=0;j<10;j++)
			temp[i][j]=plansza[i][j].wartosc;

	ekran.Wyswietl(temp,STRONA);
	
}


bool Gracz::UstawMyszka()
{
	bool done = false;
	int i=0,j=0,x=-1,y=-1;
	init();
	Ekran ekran;
	Wyswietl(L);
	while(1)
	{
		ekran.Mysz();
		
		if(done) // zeruje wszystko jesli cos zostanie tak postawione ze juz nic nie bedzie mozna zrobic
		{
			done = false;
			init();
			i=0;
			j=0;
			x=-1;
			y=-1;
			ekran.Tekst(70,240,"ZLE USTAWIONE");
		}
	
		if(ekran.MyszButton()==1) //  pobiera x i y gdy zostanie nacisniety prawy przycisk
		{
			ekran.MyszkaXY(x,y,L);
		}
			
		
		if((x>-1)&&(x<10)&&(y>-1)&&(y<10)) // jesli pobrane x i y sa w "planszy" gracza idzie dalej
				{
					
					if(CzyPoprawnie(x,y,j)) // jesli statek jest ustawiany poprawnie to go tam ustawia
					{
						UstawStatek(x,y,i);
						j++;
						if(!CzySaTrojki()&&DL(i)!=1) done = true; // sprawdza w statku dluzszym niz 1 czy jest miejsce na ustawienie kolejnego masztu
						if(j==DL(i)) //przechodzi do ustawiania kolejnego statku (i++) jesli zostal ustawiony caly i-ty statek
						{
							j=0;
							Zmiana();
							i++;
						}
						Wyswietl(L);
					}
					
				}
		if(x>=21&&x<=29&&y>=18&&y<=20) return false; //zostalo nacisniete "MENU"
		if(x>=21&&x<=29&&y>=14&&y<=17)
		{
			while(!UstawLosowo());
			return true;
		}
		if(i==ilosc)
		{
			Wyswietl(L);
			return true;
		}

	}
}


bool Gracz::CzyPoprawnie(int x,int y,int j)
{
	if(j==0&&plansza[x][y].wartosc==0) return true;
	if(j!=0&&plansza[x][y].wartosc==3) return true;
	return false;
}

bool Gracz::CzySaTrojki()
{
	int i,j;
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
		if(plansza[i][j].wartosc==3)return true;

	return false;
}


void Gracz::losujXY(int &x,int &y,int i, int n)
{
	int strzal,wsp;
	srand(time(NULL));
	if(n==0)
	{
		strzal = rand () %lista.Ilosc();
		wsp = lista.Zwroc(strzal);
	}
	else 
	{
		wsp = ustawianie[i].Ilosc()-1;
		if(wsp==0) strzal = 0;
		else strzal = rand () %wsp;
		wsp = ustawianie[i].Zwroc(strzal);
		ustawianie[i].UsunWybrany(wsp);
	}
	lista.UsunWybrany(wsp);

	if(wsp<10) 
	{
		x=0;
		y=wsp;
	}
	else
	{
		x = wsp/10;
		y = wsp - 10*x;
	}


}
