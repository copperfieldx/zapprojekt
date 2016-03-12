#include"algorytmy.h"
#include"gen.h"
#include <cmath>
#include<iostream>
using namespace std; //do testow


int binToDec(Gen *genotyp, int liczba_bitow)
{
    int wynik=0;
    int potegadwojki=pow(2,liczba_bitow-1);
    Gen *akt=genotyp;
    for(int i=0;i<liczba_bitow;i++)
    {
        wynik=wynik+akt->wartosc_*potegadwojki;
        akt=akt->nastepny_;
        potegadwojki/=2;
    }
    cout<<wynik<<" ";

    return wynik;
}

float dekoduj(Osobnik *os1, int poczatek_przedzialu, int koniec_przedzialu, int liczba_bitow )
{
    float rozdzielczosc=1.0*(koniec_przedzialu-poczatek_przedzialu)/(pow(2,liczba_bitow)-1);
    float wynik=poczatek_przedzialu+binToDec(os1->gen_, liczba_bitow)*rozdzielczosc;
    return wynik;

}
