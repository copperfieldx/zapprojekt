#include "dane.h"
#include "algorytmy.h"
#include<fstream> //wczytanie z pliku
#include<iostream> //wczytanie z klawiatury i drukowanie
using namespace std;

Dane::Dane()
{    
}

int Dane::Poczatek()
{
    return poczatek_przedzialu_;
}

int Dane::Koniec()
{
    return koniec_przedzialu_;
}

int Dane::LOsobnikow()
{
    return liczba_osobnikow_;
}

int Dane::LBitow()
{
    return liczba_bitow_;
}

int Dane::LPokolen()
{
    return liczba_pokolen_;
}

double Dane::Rozdzielczosc()
{
    return rozdzielczosc_;
}

double Dane::xMIN()
{
    return xMIN_;
}

double Dane::yMIN()
{
    return yMIN_;
}

bool Dane::wczytajDaneZPliku()
{
    fstream wejscie;
    string nazwa;
    cout<<"podaj nazwe pliku *.txt";
    cin>>nazwa;
    wejscie.open(nazwa.c_str());
    while(!wejscie.good())
    {
        wejscie.close();
        wejscie.clear();
        cout<<"podaj poprawna nazwe pliku:";
        cin>>nazwa;
        wejscie.open(nazwa.c_str());
    }
    wejscie>>poczatek_przedzialu_>>koniec_przedzialu_>>liczba_bitow_>>liczba_osobnikow_>>liczba_pokolen_;
    wejscie.close();
    if(poczatek_przedzialu_>=koniec_przedzialu_)cout<<"BLAD: Koniec przedzialu nie moze byc mniejszy lub rowny poczatkowi"<<endl;
    if(liczba_bitow_<=1)cout<<"BLAD: Liczba bitow musi byc wieksza od 1"<<endl;
    if(liczba_osobnikow_<=1)cout<<"BLAD: Liczba osobnikow musi byc wieksza od 1"<<endl;
    if(liczba_pokolen_<=1)cout<<"BLAD: Liczba pokolen musi byc wieksza od 1"<<endl;
    if(poczatek_przedzialu_>=koniec_przedzialu_ || liczba_bitow_<=1 || liczba_osobnikow_<=1 || liczba_pokolen_<=1){cout<<endl;return 0;}
    return 1;
}

bool Dane::wczytajDaneZKlawiatury()
{
    cout<<"Podawaj kolejno liczby calkowite oznaczajace:\n1)poczatek przedzialu\n2)koniec przedzialu\n3)liczba bitow\n4)liczba osobnikow\n5)liczba pokolen\n";
    cin>>poczatek_przedzialu_>>koniec_przedzialu_>>liczba_bitow_>>liczba_osobnikow_>>liczba_pokolen_;
    if(poczatek_przedzialu_>=koniec_przedzialu_)cout<<"BLAD: Koniec przedzialu nie moze byc mniejszy lub rowny poczatkowi"<<endl;
    if(liczba_bitow_<=1)cout<<"BLAD: Liczba bitow musi byc wieksza od 1"<<endl;
    if(liczba_osobnikow_<=1)cout<<"BLAD: Liczba osobnikow musi byc wieksza od 1"<<endl;
    if(liczba_pokolen_<=1)cout<<"BLAD: Liczba pokolen musi byc wieksza od 1"<<endl;
    if(poczatek_przedzialu_>=koniec_przedzialu_ || liczba_bitow_<=1 || liczba_osobnikow_<=1 || liczba_pokolen_<=1){cout<<endl;return 0;}
    return 1;
}


/*
void Dane::drukujDane()
{
    cout<<"poczatek przedzialu "<<poczatek_przedzialu_<<endl;
    cout<<"koniec przedzialu "<<koniec_przedzialu_<<endl;
    cout<<"liczba bitow "<<liczba_bitow_<<endl;
    cout<<"liczba elementow "<<liczba_osobnikow_<<endl;
    cout<<"liczba pokolen "<<liczba_pokolen_<<endl;
}
*/

void Dane::zapiszDoPliku()
{
    fstream wyjscie;
    string nazwa;
    cout<<"Podaj nazwe pliku do ktorego chcesz zapisac wynik:(z koncowka *.txt):"<<endl;
    cin>>nazwa;
    wyjscie.open(nazwa.c_str(), ios::out);
    wyjscie<<this->xMIN()<<"\t"<<this->yMIN();
    wyjscie.close();
}

void Dane::ustawRozdzielczosc()
{
    this->rozdzielczosc_=rozdzielczosc(this->poczatek_przedzialu_, this->koniec_przedzialu_, this->liczba_bitow_);
}

void Dane::ustawWyjscie(double xMIN, double yMIN)
{
    this->xMIN_=xMIN;
    this->yMIN_=yMIN;
}

