#include "osobnik.h"
#include "algorytmy.h"
#include<cstdlib>
#include<ctime>
#include<iostream>
using namespace std; //usunac obydwa

Osobnik::Osobnik(int x)
{
    rozmiar_=x;
    genotyp_=new bool[x];
    nastepny_osobnik_=NULL;
}

Osobnik::~Osobnik()
{
    delete []genotyp_;
}


bool* Osobnik::zwrocGenotyp()
{
return genotyp_;
}

Osobnik* Osobnik::adresNastepnego()
{
    return nastepny_osobnik_;
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
        for(int i=0;i<akt->rozmiar_;i++)
        {
            cout<<akt->genotyp_[i];
        }
        cout<<endl;
        akt=akt->nastepny_osobnik_;
    }

}

void Osobnik::losuj()
{
    for(int i=0;i<rozmiar_;i++)
    {
        genotyp_[i]=rand()%2;
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
        delete tmp;

    }
    cout<<"populacja usunieta \n\n";
}


Osobnik* tworzPopulacje(int ile_osobnikow, int jaka_dlugosc)
{

    Osobnik *akt=new Osobnik(jaka_dlugosc);
    Osobnik *pl=akt;
    Osobnik *tmp=NULL;
    for(int i=0;i<ile_osobnikow;i++)
    {
        if(i==0)tmp=pl;
        else tmp=new Osobnik(jaka_dlugosc);
        tmp->losuj();
        akt->nastepny_osobnik_=tmp;
        akt=akt->nastepny_osobnik_;
    }

    return pl;
}



void krzyzuj(Osobnik *wsk1, Osobnik *wsk2, int pPodz)
{
    for(int i=0;i<pPodz;i++)
    {
        zamien(wsk1->genotyp_[i],wsk2->genotyp_[i]);
        //wsk1=wsk1->nastepny_osobnik_; //bullshit
        //wsk2=wsk2->nastepny_osobnik_;
    }

}
