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
    cout<<"gen usutniety /n";*/
}


void Gen::usunListe()
{
    Gen*akt=this;
    Gen*tmp=this;
    while(akt)
    {
        tmp=akt;
        akt=akt->nastepny_;
        //tmp->~Gen();
        delete tmp;
    }

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
