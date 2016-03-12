#include "gen.h"
#include<cmath>
#include<ctime>
#include<cstdlib>
#include<iostream>
using namespace std;

Gen::Gen()
{
    wartosc_=0;
    nastepny_=NULL;
}

Gen::~Gen()
{
}

bool Gen::zwrocWartosc()
{
    return wartosc_;
}

Gen* Gen::zwrocAdresNastepnego()
{
    return nastepny_;
}

/*Gen::~Gen()
{
    delete nastepny_;
    //delete wartosc_;
    //delete nastepny_;
   /* Gen*akt=this;
    Gen*tmp=this;
    while(akt)
    {
        tmp=akt;
        akt=akt->nastepny_;
        delete tmp;
    }
    cout<<"gen usutniety /n";
}*/


void usunListe(Gen *wsk)
{
    Gen*akt=wsk;
    Gen*tmp=wsk;
    while(akt)
    {
        tmp=akt;
        akt=akt->nastepny_;
        delete tmp;
    }
    cout<<"osobnik usuniety \n";

}


Gen* Gen::tworz(int dlugosc)
{
    Gen *pl=this;
    Gen *akt=this;
    for(int i=0;i<dlugosc;i++)
    {
        Gen *tmp=new Gen();
        akt->nastepny_=tmp;
        akt->wartosc_=rand()%2;
        akt=akt->nastepny_;
    }
    return pl;
}

void Gen::wyswietl()
{
    Gen *akt=this;
    while(akt->nastepny_)
    {
        cout<<akt->wartosc_;
        akt=akt->nastepny_;
    }
    cout<<endl;
}


/*void usunListe(Gen &pl)
{
    Gen *akt=&pl;
    Gen*tmp=akt;
    while(akt)
    {
        tmp=akt;
        akt=akt->nastepny_;
        tmp->~Gen();
    }
}

Gen::~Gen()
{
    delete this;
}*/
void zamien(Gen* wsk1, Gen* wsk2)
{
    bool x;
    x=wsk1->wartosc_;
    wsk1->wartosc_=wsk2->wartosc_;
    wsk2->wartosc_=x;
}
