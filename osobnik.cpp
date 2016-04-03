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
    zdekodowany_=0; //dodane potem, zalezne od dlugosci przedzialu!
    nastepny_osobnik_=NULL;
    przystosowanie_=0; //musi być edytowane potem, bo zależne od m.in. od dlugosci przedzialu
}

//destruktor(?)
Osobnik::~Osobnik()
{
    delete []genotyp_;
    nastepny_osobnik_=NULL;
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
    while(akt)
    {
        for(int i=0;i<akt->rozmiar_;i++)
        {
            cout<<akt->genotyp_[i];
        }
        cout<<" "<<akt->zdekodowany_<<"\t";
        cout<<" "<<akt->przystosowanie_<<endl;//do testow
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


//usuwanie populacji - sprawdz czy dziala i nie ma wycieku pamieci;
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


//do ostatniej nadrzednej(w operujnadanych())- z wyswietleniem - do testow
void usunPopulacje2(Osobnik *&wsk)
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
        tmp->zdekodowany_=dekoduj(tmp->zwrocGenotyp(),wejscie->Poczatek(),wejscie->Koniec(),wejscie->LBitow());
        tmp->przystosowanie_=f1(tmp->zdekodowany_);
        akt->nastepny_osobnik_=tmp;
        akt=akt->nastepny_osobnik_;
    }

    return pl;
}

//metoda rankingu linowego
void tworzKolejnaPopulacjeVol2(Osobnik* &stara, Dane* wejscie, int sumaPrzystosowan, int* tablicaPrzystosowan)
{

   //dla met.rankingowej mozna to zrobic raz i sie odwolywac!!
    int LOsobnikow=wejscie->LOsobnikow();
    /*
    int sumaPrzystosowan=((1+LOsobnikow)/2)*LOsobnikow; //(1+n)/2*n - suma ciagu liczb od 1 do n;
    int* tablicaPrzystosowan=new int[LOsobnikow];
    int x=0;
    for(int i=0;i<LOsobnikow;i++)
    {
        x=x+i+1; //1, 1+2, (1+2)+3, etc.
        tablicaPrzystosowan[i]=x; //zawiera "przedzialy"
    }*/



    Osobnik *akt=new Osobnik(wejscie->LBitow());
    Osobnik *tmp=akt;
    Osobnik *pom1=NULL;
    Osobnik *pom2=NULL;


    for(int i=0;i<LOsobnikow;i++) //sprawdz inna metode z 2 osobnikow powstaje 2 osobniki!!
    {
        int los1=rand()%sumaPrzystosowan+1;
        pom1=stara;
        pom2=stara;

        if(los1==1)
        {
            pom1=stara->zwrocAdresITegoElementu(1);
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
                pom2=stara->zwrocAdresITegoElementu(1);
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
        akt->zdekodowany_=dekoduj(akt->zwrocGenotyp(),wejscie->Poczatek(),wejscie->Koniec(),wejscie->LBitow());
        akt->przystosowanie_=f1(akt->zdekodowany_);
        akt=akt->nastepny_osobnik_;
    }



    //delete []tablicaPrzystosowan;
    usunPopulacje(*&stara); //hmm?
    stara=tmp;
}

void tworzKolejnaPopulacjeVol3(Osobnik* &stara, Dane* wejscie, int sumaPrzystosowan, int* tablicaPrzystosowan)
{

   //dla met.rankingowej mozna to zrobic raz i sie odwolywac!!
    int LOsobnikow=wejscie->LOsobnikow();
    /*
    int sumaPrzystosowan=((1+LOsobnikow)/2)*LOsobnikow; //(1+n)/2*n - suma ciagu liczb od 1 do n;
    int* tablicaPrzystosowan=new int[LOsobnikow];
    int x=0;
    for(int i=0;i<LOsobnikow;i++)
    {
        x=x+i+1; //1, 1+2, (1+2)+3, etc.
        tablicaPrzystosowan[i]=x; //zawiera "przedzialy"
    }
    */


    Osobnik *akt=new Osobnik(wejscie->LBitow());
    Osobnik *tmp=akt;
    Osobnik *pom1=NULL;
    Osobnik *pom2=NULL;


    for(int i=0;i<LOsobnikow;i++) //sprawdz inna metode z 2 osobnikow powstaje 2 osobniki!!
    {
        int los1=rand()%sumaPrzystosowan+1;
        pom1=stara;
        pom2=stara;

        if(los1==1)
        {
            pom1=stara->zwrocAdresITegoElementu(1);
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
                pom2=stara->zwrocAdresITegoElementu(1);
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
       //akt->przystosowanie_=f1(dekoduj(akt->zwrocGenotyp(),wejscie->Poczatek(),wejscie->Koniec(),wejscie->LBitow()));
       if(i+1<(LOsobnikow/2+1))
       {
            akt->nastepny_osobnik_=new Osobnik(wejscie->LBitow());
            akt=akt->adresNastepnego();
            krzyzuj(pom2,pom1,akt);
            if(i<(LOsobnikow/2))
            {
            akt->nastepny_osobnik_=new Osobnik(wejscie->LBitow());
            akt=akt->adresNastepnego();
            }

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
        // !!!!
        akt->zdekodowany_=dekoduj(akt->zwrocGenotyp(),wejscie->Poczatek(),wejscie->Koniec(),wejscie->LBitow());
        akt->przystosowanie_=f1(akt->zdekodowany_);
        akt=akt->nastepny_osobnik_;
    }



   // delete []tablicaPrzystosowan;
    usunPopulacje(*&stara);
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
        akt->zdekodowany_=dekoduj(akt->zwrocGenotyp(),wejscie->Poczatek(),wejscie->Koniec(),wejscie->LBitow());
        akt->przystosowanie_=f1(akt->zdekodowany_);
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
    double temp3=0;
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

                   temp3=p->zdekodowany_;
                   p->zdekodowany_=p->nastepny_osobnik_->zdekodowany_;
                   p->nastepny_osobnik_->zdekodowany_=temp3;
               }
}
