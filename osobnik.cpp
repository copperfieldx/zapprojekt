#include "osobnik.h"
#include "algorytmy.h"
#include "dane.h"
#include<cstdlib>
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

//destruktor(?)
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
void Osobnik::mutuj(int y)
{
    int x=rand()%y;
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


Osobnik* Osobnik::zwrocAdresITegoElementu(int x)
{
    Osobnik* tmp=this;
    for(int i=1;i<x;i++)
    {
        tmp=tmp->adresNastepnego();
    }
    return tmp;
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
        tmp->przystosowanie_=g(dekoduj(tmp->zwrocGenotyp(),wejscie->Poczatek(),wejscie->Koniec(),LBitow));
        akt->nastepny_osobnik_=tmp;
        akt=akt->nastepny_osobnik_;
    }

    return pl;
}

//ułomna metoda rankingowa
void tworzKolejnaPopulacjeVol2(Osobnik* &stara, Dane* wejscie)
{

    int LOsobnikow=wejscie->LOsobnikow();
    int sumaPrzystosowan=((1+LOsobnikow)/2)*LOsobnikow; //(1+n)/2*n - suma ciagu liczb od 1 do n;
    int* tablicaPrzystosowan=new int[LOsobnikow];
    int x=0;
    for(int i=0;i<LOsobnikow;i++)
    {
        x=x+i+1; //1, 1+2, (1+2)+3, etc.
        tablicaPrzystosowan[i]=x; //zawiera "przedzialy"
    }
    Osobnik *akt=new Osobnik(wejscie->LBitow());
    Osobnik *tmp=akt;
    Osobnik *pom1=NULL;
    Osobnik *pom2=NULL;


    for(int i=0;i<LOsobnikow;i++)
    {
        int los1=rand()%sumaPrzystosowan+1;
        pom1=stara;
        pom2=stara;

        for(int j=1;j<LOsobnikow-1;j++)
        {
            if(los1==1)
            {
                pom1=stara->zwrocAdresITegoElementu(1);
                break;
            }
            if(los1>tablicaPrzystosowan[j] && los1<=tablicaPrzystosowan[j+1])
            {
              pom1=stara->zwrocAdresITegoElementu(j+2);
                 break;
            }
        }

       do
       {
        int los2=rand()%sumaPrzystosowan+1;
        for(int j=1;j<LOsobnikow-1;j++)
        {
            if(los2==1)
            {
                pom2=stara->zwrocAdresITegoElementu(1);
                break;
            }
            if(los2>tablicaPrzystosowan[j] && los2<=tablicaPrzystosowan[j+1])
            {
               pom2=stara->zwrocAdresITegoElementu(j+2);
                break;
            }
        }
       }
      while(pom1==pom2); //zabezpieczenie, zeby nie losowal tych samych

        krzyzuj(pom1,pom2,akt);
        //akt->przystosowanie_=f1(dekoduj(akt->zwrocGenotyp(),wejscie->Poczatek(),wejscie->Koniec(),wejscie->LBitow()));
        if(i+1<LOsobnikow)
        {
        akt->nastepny_osobnik_=new Osobnik(wejscie->LBitow());
        akt=akt->adresNastepnego();
        }

    }

    //mutacja skopiowana
    int prawdmut=0;
    akt=tmp;
    for(int i=0;i<LOsobnikow;i++)
    {
        prawdmut=rand()%10;
        if(prawdmut>8)//przypadek 1/10, prawdopodobienstwo 10%; do przemyslenia
        {
            akt->mutuj(wejscie->LBitow());
        }
        //!!!!
        akt->przystosowanie_=g(dekoduj(akt->zwrocGenotyp(),wejscie->Poczatek(),wejscie->Koniec(),wejscie->LBitow()));
        akt=akt->nastepny_osobnik_;
    }



    delete []tablicaPrzystosowan;
    stara->~Osobnik(); //hmm?
    stara=tmp;
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
            akt->mutuj(wejscie->LBitow());
        }
        akt->przystosowanie_=g(dekoduj(akt->zwrocGenotyp(),wejscie->Poczatek(),wejscie->Koniec(),wejscie->LBitow()));
        akt=akt->nastepny_osobnik_;
    }

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

//sortuje populacje(liste osobnikow) od NAJMNIEJSZEGO do najwiekszego przystosowania
void Osobnik::sortuj(int Losobnikow) //narazie dziala poprzez zamiane odpowiednich pol; ZMIEN POTEM NA WSKAZNIKI!
{
    double temp=0;
    bool *temp2;
    for(int i = 0; i<Losobnikow; i++)
           for (Osobnik * p = this; p->nastepny_osobnik_; p = p->nastepny_osobnik_)
               if(p->przystosowanie_ < p->nastepny_osobnik_->przystosowanie_) //!!!!!!!!!
               {
                   temp = p->przystosowanie_;
                   p->przystosowanie_ = p->nastepny_osobnik_->przystosowanie_;
                   p->nastepny_osobnik_->przystosowanie_ = temp;

                   temp2=p->genotyp_;
                   p->genotyp_=p->nastepny_osobnik_->genotyp_;
                   p->nastepny_osobnik_->genotyp_=temp2;
               }
}
