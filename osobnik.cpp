#include "osobnik.h"
#include "algorytmy.h"
#include "dane.h"
#include<cstdlib>
#include<iostream>
using namespace std;

//konstruktor
Osobnik::Osobnik(int x)
{
    rozmiar_=x;
    genotyp_=new bool[x];
    zdekodowany_=0; //dodane potem, zalezne od dlugosci przedzialu!
    nastepny_osobnik_=NULL;
    przystosowanie_=0; //musi być edytowane potem, bo zależne od m.in. od dlugosci przedzialu
}

//destruktor
Osobnik::~Osobnik()
{
    delete []genotyp_;
    nastepny_osobnik_=NULL;
}

//4 funkcje zwracajace odpowiednie pola
bool* Osobnik::zwrocGenotyp()
{
    return genotyp_;
}

double Osobnik::przystosowanie()
{
    return przystosowanie_;
}

double Osobnik::zdekodowany()
{
    return zdekodowany_;
}

Osobnik* Osobnik::adresNastepnego()
{
    return nastepny_osobnik_;
}

//wyswietla kolejno genotypy, wartosc zdekodowana i  wartosc funkcji przystosowania dla nich;
void Osobnik::wyswietlPopulacje()
{
    Osobnik *akt=this;
    while(akt)
    {
        for(int i=0;i<akt->rozmiar_;i++)
        {
            cout<<akt->genotyp_[i];
        }
        cout<<" "<<akt->zdekodowany_<<"\t";
        cout<<" "<<akt->przystosowanie_<<endl;
        akt=akt->nastepny_osobnik_;
    }
    cout<<endl;

}

//losuje genotyp, potrzebne przy populacji poczatkowej
void Osobnik::losuj()
{
    for(int i=0;i<rozmiar_;i++)
    {
        genotyp_[i]=rand()%2;
    }
}

//mutacja, neguje losowy bit z Osobnika; funkcja odpalana w funkcji nadrzednej z okreslonym prawdopodobienstwem.
void Osobnik::mutuj()
{
    int x=rand()%this->rozmiar_;
    genotyp_[x]=!genotyp_[x];
}


//sortuje populacje(liste osobnikow) od NAJMNIEJSZEGO do najwiekszego przystosowania
void Osobnik::sortuj()
{
    double temp=0;
    bool *temp2;
    double temp3=0;
   for (Osobnik * p = this; p->nastepny_osobnik_; p = p->nastepny_osobnik_)
           for (Osobnik * p = this; p->nastepny_osobnik_; p = p->nastepny_osobnik_)
               if(p->przystosowanie_ < p->nastepny_osobnik_->przystosowanie_)
               {
                   temp = p->przystosowanie_;
                   p->przystosowanie_ = p->nastepny_osobnik_->przystosowanie_;
                   p->nastepny_osobnik_->przystosowanie_ = temp;

                   temp2=p->genotyp_;
                   p->genotyp_=p->nastepny_osobnik_->genotyp_;
                   p->nastepny_osobnik_->genotyp_=temp2;

                   temp3=p->zdekodowany_;
                   p->zdekodowany_=p->nastepny_osobnik_->zdekodowany_;
                   p->nastepny_osobnik_->zdekodowany_=temp3;
               }
}


Osobnik* Osobnik::zwrocAdresITegoElementu(int x)
{
    Osobnik* tmp=this;
    for(int i=1;i<x;i++)
    {
        tmp=tmp->adresNastepnego();
    }
    return tmp;
}


//usuwanie populacji
void usunPopulacje(Osobnik *&wsk)
{
    Osobnik *akt=wsk;
    Osobnik *tmp=wsk;
    while(akt)
    {
        tmp=akt;
        akt=akt->nastepny_osobnik_;
        delete tmp;
    }
}

//tworzy PIERWSZA populacje, wykorzystuje losowanie genotypu;
Osobnik* tworzPopulacje(Dane* wejscie)
{
    int LBitow=wejscie->LBitow();
    Osobnik *akt=new Osobnik(LBitow);
    Osobnik *pl=akt;
    Osobnik *tmp=NULL;
    for(int i=0;i<wejscie->LOsobnikow();i++)
    {
        if(i==0)tmp=pl;
        else tmp=new Osobnik(LBitow);
        tmp->losuj();
        tmp->zdekodowany_=dekoduj(tmp->zwrocGenotyp(),wejscie->Poczatek(),wejscie->LBitow(),wejscie->Rozdzielczosc());
        tmp->przystosowanie_=f1(tmp->zdekodowany_);
        akt->nastepny_osobnik_=tmp;
        akt=akt->nastepny_osobnik_;
    }

    return pl;
}

//metoda rankingu liniowego
void tworzKolejnaPopulacje(Osobnik* &stara, Dane* wejscie, int sumaPrzystosowan, int* tablicaPrzystosowan)
{
    int LOsobnikow=wejscie->LOsobnikow();
    Osobnik *akt=new Osobnik(wejscie->LBitow());
    Osobnik *tmp=akt;
    Osobnik *pom1=NULL;
    Osobnik *pom2=NULL;

    for(int i=0;i<(LOsobnikow+1)/2;i++)
    {
        int los1=rand()%sumaPrzystosowan+1;
        pom1=stara;
        pom2=stara;

        if(los1==1)
        {
            pom1=stara;
        }

        else
        for(int j=1;j<LOsobnikow;j++)
        {

            if(los1>tablicaPrzystosowan[j-1] && los1<=tablicaPrzystosowan[j])
            {
                 pom1=stara->zwrocAdresITegoElementu(j+1);
                 break;
            }
        }

        do
        {
            int los2=rand()%sumaPrzystosowan+1;

            if(los2==1)
            {
                pom2=stara;
            }

            else
            for(int j=1;j<LOsobnikow;j++)
            {

                if(los2>tablicaPrzystosowan[j-1] && los2<=tablicaPrzystosowan[j])
                {
                    pom2=stara->zwrocAdresITegoElementu(j+1);
                    break;
                }
            }
        }
        while(pom1==pom2);  //zabezpieczenie, zeby nie losowal tych samych

        krzyzuj(pom1,pom2,akt);
        if(i<(LOsobnikow/2))
        {
            akt->nastepny_osobnik_=new Osobnik(wejscie->LBitow());
            akt=akt->nastepny_osobnik_;
            krzyzuj(pom2,pom1,akt);
            if(i+1<((LOsobnikow+1)/2))
            {
            akt->nastepny_osobnik_=new Osobnik(wejscie->LBitow());
            akt=akt->nastepny_osobnik_;
            }
        }
    }

    int prawdmut=0;
    akt=tmp;
    for(int i=0;i<LOsobnikow;i++)
    {
        prawdmut=rand()%10;
        if(prawdmut>8)//przypadek 1/10, prawdopodobienstwo 10%;
        {
            for(int j=0;j<wejscie->LBitow()/2;j++) //mutacja dla polowy bitow
            akt->mutuj();
        }
        // !!!!
        akt->zdekodowany_=dekoduj(akt->zwrocGenotyp(),wejscie->Poczatek(),wejscie->LBitow(),wejscie->Rozdzielczosc());
        akt->przystosowanie_=f1(akt->zdekodowany_);
        akt=akt->nastepny_osobnik_;
    }

    usunPopulacje(*&stara);
    stara=tmp;
}


//krzyzuje material genetyczny osobnika wsk1 i wsk2 i zapisuje do docelowy; polowa materialu od osobnika pierwszego i polowa od drugiego
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
