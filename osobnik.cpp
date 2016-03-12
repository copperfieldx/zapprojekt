#include "osobnik.h"
#include "gen.h"
#include<cstdlib>
#include<ctime>
#include<iostream>
using namespace std; //usunac obydwa

Osobnik::Osobnik()
{
    gen_=new Gen;
    nastepny_osobnik_=NULL;
}

Osobnik::~Osobnik()
{
}

/*Osobnik::~Osobnik()
{
    this->gen_->usunListe();
    cout<<"osobnik usuniety \n";
    //delete nastepny_osobnik_;
    /*Osobnik *akt=this;
    Osobnik *tmp=this;
    while(akt)
    {
        tmp=akt;
        akt=akt->nastepny_osobnik_;
        tmp->gen.usunListe();
        //usunListe(tmp->gen);
        delete tmp;

    }
    cout<<"osobnik usuniety /n";
}*/
void Osobnik::wyswietlPopulacje()
{
    Osobnik *akt=this;
    while(akt->nastepny_osobnik_)
    {
        akt->gen_->wyswietl();
        akt=akt->nastepny_osobnik_;
    }

}


void usunPopulacje(Osobnik *wsk)
{
    Osobnik *akt=wsk;
    Osobnik *tmp=wsk;
    while(akt)
    {
        tmp=akt;
        akt=akt->nastepny_osobnik_;
        //tmp->gen.usunListe();
        //usunListe(tmp->gen);
        usunListe(tmp->gen_);
        delete tmp;

    }
    cout<<"populacja usunieta \n\n";
}


Osobnik* tworzPopulacje(int ile_osobnikow, int jaka_dlugosc)
{

    Osobnik *akt=new Osobnik;
    Osobnik *pl=akt;
    for(int i=0;i<ile_osobnikow;i++)
    {
        Osobnik *tmp=new Osobnik();
        akt->gen_->tworz(jaka_dlugosc);
        akt->nastepny_osobnik_=tmp;
        akt=akt->nastepny_osobnik_;
    }

    return pl;
}
