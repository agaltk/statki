#include "Gra.h"


Gra::Gra(INFO info)
{
	for(int i=0;i<100;i++) lista.DodajNaKoniec(i);

	for(int i=0;i<10;i++)
		for(int j=0;j<10;j++)
			PustaPlansza[i][j]=0;
	ustawianie = new Lista[info.ilosc];
	poziom = info.poziom;
}


Gra::~Gra(void)
{
}
bool Gra::CzyWygral(Gracz gracz)
{
	int i;
	for(i=0;i<gracz.Ilosc();i++)
		if(!gracz.Zatopiony(i)) return false;
	return true;
}
	
bool Gra::CzyZatopiony(int j,Gracz &gracz)
{
	if(gracz.ZPN(j)<1)
	{
		gracz.Zatopiony(j,true);
		return true;
	}
	return false;

}

void Gra::OtoczZatopiony(int j,Gracz &gracz,int typ,int ust)
{
	int i,dl,ii,jj,x,y;
	dl=gracz.DL(j);
	for(i=0;i<dl;i++)
	{
		x = gracz.PolozenieElement(j,i)/10;
		y = gracz.PolozenieElement(j,i) - 10*x;
		for(ii=(x-1);ii<(x+2);ii++)
		for(jj=(y-1);jj<(y+2);jj++)
			if((ii<10)&&(ii>-1)&&(jj<10)&&(jj>-1)) //jesli jest tam 0
			{
				if(typ==G&&(PustaPlansza[ii][jj]==0)) PustaPlansza[ii][jj]=5;
				else if(typ==K&&(gracz.Wartosc(ii,jj)!=5)&&(gracz.Wartosc(ii,jj)!=6)&&(gracz.Wartosc(ii,jj)!=7))
					{
						gracz.Wartosc(ii,jj,5);
						
						lista.UsunWybrany(10*ii+jj);
				}
			}
	}
	if(typ==K) ustawianie[ust].Usun();
}

AKCJA Gra::StrzalKomputer(Ekran &ekran,int &i,int &j,Gracz &gracz)
{
	int x,y,nr=0;
	Wyswietl(gracz,L);
	while(1)
	{
		
		if(poziom == HARD)	losujXY(x,y,i,j);
		else if(poziom == EASY)	losujXY(x,y,i,0);
		
		if(gracz.Wartosc(x,y) == 2) gracz.Wartosc(x,y,6);
		else gracz.Wartosc(x,y,5);


		if(gracz.Wartosc(x,y)!=6){Wyswietl(gracz,L);return GRA_DALEJ;}
		else
		{
			nr = gracz.Nr(x,y);
			gracz.ZPN(nr,1);
			if(CzyZatopiony(nr,gracz))
			{
				OtoczZatopiony(nr,gracz,K,i);
				for(int kk=0;kk<10;kk++)
					for(int nn=0;nn<10;nn++)
						if(gracz.Wartosc(kk,nn)==6&&gracz.Nr(kk,nn)==nr)gracz.Wartosc(kk,nn,7);

				j=0;
				i++;
			}

			else
			{
				for(int ii=(x-1);ii<(x+2);ii++)
				for(int jj=(y-1);jj<(y+2);jj++)
				if((ii<10)&&(ii>-1)&&(jj<10)&&(jj>-1)) //jesli jest tam 0
				{
					if(ii==x&&jj==y);
					else if((gracz.Wartosc(ii,jj)!=6)&&(gracz.Wartosc(ii,jj)!=5)&&(ii==x||jj==y)) 
					{
						if(!ustawianie[i].CzyJest(ii*10+jj)) ustawianie[i].DodajNaKoniec(ii*10+jj);
					}
				
				}
				j++;

			}
		
			if(CzyWygral(gracz)) {;Wyswietl(gracz,L);return WYGRAL_KOMPUTER;}
			Wyswietl(gracz,L);

		}
	
	}
	
}

AKCJA Gra::StrzalGracz(Ekran &ekran,int &ii, int &jj, Gracz &gracz)
{	
	bool klik = false; 
	ekran.Wyswietl(PustaPlansza,P);
	while(1)
	{

		
		
		int x=-1,y=-1;

		ekran.Mysz();
		if(ekran.MyszButton()==0) klik = true;		
		int nr;//numer statku
	
		if(ekran.MyszButton()==1&&klik) //  pobiera x i y gdy zostanie nacisniety prawy przycisk
		{
			klik = false;
			ekran.MyszkaXY(x,y,P);
			
			
		}
		if((x<10)&&(x>-1)&&(y<10)&&(y>-1)&&PustaPlansza[x][y]!=5&&PustaPlansza[x][y]!=6)
		{
			if(gracz.Wartosc(x,y) == 2) PustaPlansza[x][y] = 6;
			else PustaPlansza[x][y] = 5;

			if(PustaPlansza[x][y]!=6){ekran.Wyswietl(PustaPlansza,P);return GRA_DALEJ;}
				else
				{
					nr = gracz.Nr(x,y);
					gracz.ZPN(nr,1);
					if(CzyZatopiony(nr,gracz))
					{
						if(gracz.OTACZANIE())OtoczZatopiony(nr,gracz,G,ii);
						for(int kk=0;kk<10;kk++)
							for(int nn=0;nn<10;nn++)
								if(PustaPlansza[nn][kk]==6&&gracz.Nr(nn,kk)==nr)PustaPlansza[nn][kk]=7;
						ii++;
						jj=0;
					}
					if(CzyWygral(gracz)){ekran.Wyswietl(PustaPlansza,P); return WYGRAL_GRACZ;}
					jj++;

				}
			ekran.Wyswietl(PustaPlansza,P);
		}

		if(x>=9&&x<=17&&y>=18&&y<=20) return MENU;
		
	}
}


void Gra::Wyswietl(Gracz gracz,int STRONA)
{
	Ekran ekran;
	int temp[10][10];
	for(int i=0;i<10;i++)
		for(int j=0;j<10;j++)
			temp[i][j]=gracz.Wartosc(i,j);

	ekran.Wyswietl(temp,STRONA);
}

void Gra::losujXY(int &x,int &y,int i, int n)
{
	int strzal=0,wsp=0;
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









	
