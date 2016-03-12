#include "dane.h"
#include<fstream>
#include<iostream>
using namespace std;

Dane::Dane()
{    
}

Dane::~Dane()
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

void Dane::wczytajDane()
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

}


void Dane::drukujDane()
{
    cout<<"poczatek przedzialu "<<poczatek_przedzialu_<<endl;
    cout<<"koniec przedzialu "<<koniec_przedzialu_<<endl;
    cout<<"liczba bitow "<<liczba_bitow_<<endl;
    cout<<"liczba elementow "<<liczba_osobnikow_<<endl;
    cout<<"liczba pokolen "<<liczba_pokolen_<<endl;
}
