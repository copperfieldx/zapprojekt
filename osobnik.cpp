#include "osobnik.h"
#include "algorytmy.h"
#include "dane.h"
#include<cstdlib>
#include<ctime>
#include<iostream>
using namespace std; //usunac obydwa

//konstruktor
Osobnik::Osobnik(int x)
{
    rozmiar_=x;
    genotyp_=new bool[x];
    //zdekodowany_=0; //dodane potem, zalezne od dlugosci przedzialu!
    nastepny_osobnik_=NULL;
    przystosowanie_=0; //musi być edytowane potem, bo zależne od m.in. od dlugosci przedzialu
}

//destruktor - poszukaj jeszcze czy napewno dobrze stworzony
Osobnik::~Osobnik()
{
    delete []genotyp_;
}

//3 funkcje zwracajace odpowiednie pola, moga sie przydac przy funkcjach innych niz metody i zaprzyjaznione;
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


//wyswietla kolejno genotypy i wartosc funkcji przystosowania dla nich;
void Osobnik::wyswietlPopulacje()
{
    Osobnik *akt=this;
    while(akt->nastepny_osobnik_)
    {
        for(int i=0;i<akt->rozmiar_;i++)
        {
            cout<<akt->genotyp_[i];
        }
        cout<<" "<<akt->przystosowanie_<<endl; //do testow
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
    int x=rand()%8;
    genotyp_[x]=!genotyp_[x];
}

//po stworzeniu populacji ustawia wartosc przystosowania(podana jako argument i wyliczona inna funkcja)
void Osobnik::ustalPrzystosowanie(double wartosc)
{
    przystosowanie_=wartosc;
}

//usuwanie populacji - sprawdz czy dziala i nie ma wycieku pamieci;
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
        tmp->przystosowanie_=f1(dekoduj(tmp,wejscie->Poczatek(),wejscie->Koniec(),LBitow));
        akt->nastepny_osobnik_=tmp;
        akt=akt->nastepny_osobnik_;
    }

    return pl;
}


//ulomna wersja tworzenia nowej populacji na podstawie poprzedniej - nalezy napisac nowa z metoda rankingowa/turniejow/kola ruletki/jakakolwiek
void tworzKolejna(Osobnik* stara, Dane* wejscie)
{
    int LOsobnikow=wejscie->LOsobnikow(); //zmniejsza liczbe wywolan
    Osobnik *akt=stara;
    for(int i=0;i<LOsobnikow/2;i++)//polowa osobnikow najlepiej rpzysotoswanych zostaje
    {
        akt=akt->nastepny_osobnik_;
    }
    Osobnik *pom1=NULL;
    Osobnik *pom2=NULL;

    for(int i=LOsobnikow/2;i<LOsobnikow;i++)//druga polowa jest potomkami
    {
        pom1=stara;
        pom2=stara;
        int x=rand()%(LOsobnikow/2);
        int y=rand()%(LOsobnikow/2);
        for(int i=0;i<x;i++)
        {
            pom1=pom1->nastepny_osobnik_;   //mozna dopisac funkcje zwroc adres i-tego elementu!
        }
        for(int i=0;i<y;i++)
        {
            pom2=pom2->nastepny_osobnik_;
        }
        krzyzuj(pom1,pom2,akt);
        akt=akt->nastepny_osobnik_;
    }
    int prawdmut=0;
    akt=stara;
    for(int i=0;i<LOsobnikow;i++)
    {
        prawdmut=rand()%10;
        if(prawdmut>8)//przypadek 1/10, prawdopodobienstwo 10%; do przemyslenia
        {
            akt->mutuj();
        }
        akt->przystosowanie_=f1(dekoduj(akt,wejscie->Poczatek(),wejscie->Koniec(),wejscie->LBitow()));
        akt=akt->nastepny_osobnik_;
    }

}

//krzyzuje material genetyczny osobnika wsk1 i wsk2 i zapisuje do docelowy;
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

//sortuje populacje(liste osobnikow) od NAJMNIEJSZEGO do najwiekszego
void Osobnik::sortuj(int Losobnikow) //narazie dziala poprzez zamiane odpowiednich pol; ZMIEN POTEM NA WSKAZNIKI!
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
