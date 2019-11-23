#include "Lista.h"
#include <iostream>

Lista::Lista(void)
:Pierwszy(0)
,Ostatni(0)
,ilosc(0)
{
}

Lista::~Lista(void)
{
}
void Lista::Usun()
{
	  while(ilosc!=0)
   {
       this->UsunPierwszy();
   }
}

void Lista::Ilosc(int i)
{
	this->ilosc=i;
}

int Lista::Ilosc(void)
{
	return ilosc;
}

void Lista::DodajNaKoniec (int x )
{
   WAR *nowy = new WAR();
   nowy->x=x;
   
   if(Pierwszy==0)
   {
       Ostatni = nowy;
       Pierwszy=nowy;
   }
   else
   {
	   Ostatni->Nastepny = nowy;
       Ostatni=nowy;
   }
   ilosc++;

}


void Lista::UsunPierwszy()
{
   WAR *temp ;

   if(Pierwszy!=NULL)
   {
       temp = Pierwszy->Nastepny;
       delete [] Pierwszy;
       Pierwszy = temp;
   }
   ilosc--;
}

void Lista::UsunOstatni()
{
   
   WAR *temp ;
   
   int i, n;
   n=ilosc;
   temp = Pierwszy;
   for(i=1;i<n-1;i++) temp = temp->Nastepny;

   if(Ostatni!=NULL)
   {
       delete [] Ostatni;
       Ostatni = temp;
   }
   ilosc--;


}
void Lista::UsunWybrany(int war)
{
   
   WAR *temp = Pierwszy;
   WAR *usun;
   int i;
   if(temp->x==war) 
   {
	   this->UsunPierwszy();
	   return;
   }
   if(temp->x==Ostatni->x)
   {
	   this->UsunOstatni();
	   return;
   }
   for(i=0;i<ilosc;i++)
   {	
	   
	   usun = temp->Nastepny;
	   if(war==usun->x)
	   {
		   temp->Nastepny=usun->Nastepny;
		   delete [] usun;
		   ilosc--;
		   return;

	   }
	    temp = temp ->Nastepny;
   }
  return;

}


int Lista::Zwroc (int n)
{
   WAR *temp = Pierwszy;
   int i;
   if(n==0) return Pierwszy->x;
   else
   {
       for(i=0;i<n;i++)temp = temp ->Nastepny;
	   return temp->x;
   }
   temp = Pierwszy;
   return temp->x;

}

int Lista::CzyJest(int wsp)
{
	WAR *temp = Pierwszy;
	int i;
	for(i=0;i<ilosc;i++)
		{
			if(temp->x==wsp) return 1;
			temp = temp->Nastepny;
	}
	return 0 ;

}