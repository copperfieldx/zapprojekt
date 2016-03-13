#include "osobnik.h"
#include "algorytmy.h"
#include "dane.h"
#include<cstdlib>
#include<ctime>
#include<iostream>
using namespace std; //usunac obydwa

Osobnik::Osobnik(int x)
{
    rozmiar_=x;
    genotyp_=new bool[x];
    //zdekodowany_=0; //dodane potem, zalezne od dlugosci przedzialu!
    nastepny_osobnik_=NULL;
    przystosowanie_=0; //musi być edytowane potem, bo zależne od m.in. od dlugosci przedzialu
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

double Osobnik::zwrocPrzystosowanie()
{
    return przystosowanie_;
}

void Osobnik::wyswietlPopulacje()
{
    Osobnik *akt=this;
    while(akt->nastepny_osobnik_)
    {
        for(int i=0;i<akt->rozmiar_;i++)
        {
            cout<<akt->genotyp_[i];
        }
        cout<<" "<<akt->zwrocPrzystosowanie()<<endl; //do testow
        akt=akt->nastepny_osobnik_;
    }
    cout<<endl;

}

void Osobnik::losuj()
{
    for(int i=0;i<rozmiar_;i++)
    {
        genotyp_[i]=rand()%2;
    }
}

void Osobnik::mutuj()
{
    int x=rand()%8;
    genotyp_[x]=!genotyp_[x];
}

void Osobnik::ustalPrzystosowanie(double wartosc)
{
    przystosowanie_=wartosc;
}

void usunPopulacje(Osobnik *wsk)
{
    Osobnik *akt=wsk;
    Osobnik *tmp=wsk;
    while(akt)
    {
        tmp=akt;
        akt=akt->nastepny_osobnik_;
        delete tmp;
        cout<<"osobnik usuniety \n";

    }
    cout<<"populacja usunieta \n\n";
}


Osobnik* tworzPopulacje(Dane* wejscie)
{

    Osobnik *akt=new Osobnik(wejscie->LBitow());
    Osobnik *pl=akt;
    Osobnik *tmp=NULL;
    for(int i=0;i<wejscie->LOsobnikow();i++)
    {
        if(i==0)tmp=pl;
        else tmp=new Osobnik(wejscie->LBitow());
        tmp->losuj();
        tmp->przystosowanie_=f1(dekoduj(tmp,wejscie->Poczatek(),wejscie->Koniec(),wejscie->LBitow()));
        akt->nastepny_osobnik_=tmp;
        akt=akt->nastepny_osobnik_;
    }

    return pl;
}

void tworzKolejna(Osobnik* stara, Dane* wejscie)
{
    Osobnik *akt=stara;
    for(int i=0;i<wejscie->LOsobnikow()/2;i++)//polowa osobnikow najlepiej rpzysotoswanych zostaje
    {
        akt=akt->adresNastepnego();
    }
    Osobnik *pom1=NULL;
    Osobnik *pom2=NULL;

    for(int i=wejscie->LOsobnikow()/2;i<wejscie->LOsobnikow();i++)//druga polowa jest potomkami
    {
        pom1=stara;
        pom2=stara;
        int x=rand()%(wejscie->LOsobnikow()/2);
        int y=rand()%(wejscie->LOsobnikow()/2);
        for(int i=0;i<x;i++)
        {
            pom1=pom1->adresNastepnego();   //mozna dopisac funkcje zwroc adres i-tego elementu!
        }
        for(int i=0;i<y;i++)
        {
            pom2=pom2->adresNastepnego();
        }
        krzyzuj(pom1,pom2,akt);
        akt=akt->adresNastepnego();
    }
    int prawdmut=0;
    akt=stara;
    for(int i=0;i<wejscie->LOsobnikow();i++)
    {
        prawdmut=rand()%10;
        if(prawdmut>8)//przypadek 1/10, prawdopodobienstwo 10%;
        {
            akt->mutuj();
        }
        akt->przystosowanie_=f1(dekoduj(akt,wejscie->Poczatek(),wejscie->Koniec(),wejscie->LBitow()));
        akt=akt->adresNastepnego();
    }

}


void krzyzuj(Osobnik *wsk1, Osobnik *wsk2, Osobnik *docelowy)
{
    for(int i=0;i<wsk1->rozmiar_/2;i++)
    {
        docelowy->genotyp_[i]=wsk1->genotyp_[i];
    }
    for(int i=wsk1->rozmiar_/2;i<wsk1->rozmiar_;i++)
    {
        docelowy->genotyp_[i]=wsk2->genotyp_[i];
    }

}

void Osobnik::sortuj(int Losobnikow)
{
    double temp=0;
    bool *temp2;
    for(int i = 0; i<Losobnikow; i++)
           for (Osobnik * p = this; p->nastepny_osobnik_; p = p->nastepny_osobnik_)
               if(p->przystosowanie_ > p->nastepny_osobnik_->przystosowanie_)
               {
                   temp = p->przystosowanie_;
                   p->przystosowanie_ = p->nastepny_osobnik_->przystosowanie_;
                   p->nastepny_osobnik_->przystosowanie_ = temp;

                   temp2=p->genotyp_;
                   p->genotyp_=p->nastepny_osobnik_->genotyp_;
                   p->nastepny_osobnik_->genotyp_=temp2;
               }
}
