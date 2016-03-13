#include"algorytmy.h"
#include <cmath>
#include<iostream>
using namespace std; //do testow


void operujNaDanych(Dane* wejscie)
{
    Osobnik* populacja=new Osobnik(wejscie->LBitow());
    populacja=tworzPopulacje(wejscie->LOsobnikow(),wejscie->LBitow());  //jako argument funkcji daj obiekt DANE!!!!!!
    populacja->wyswietlPopulacje();
    cout<<dekoduj(populacja,0,5,5);  //testy dzialania
    cout<<f1(-1.20496)<<"\n\n";
    krzyzuj(populacja,populacja->adresNastepnego(),5);//rowniez test
    populacja->wyswietlPopulacje();
    populacja->mutuj();
    populacja->wyswietlPopulacje();
    usunPopulacje(populacja);
    delete populacja;
    populacja->wyswietlPopulacje();
}





int binToDec(bool *genotyp, int liczba_bitow)
{
    int wynik=0;
    int potegadwojki=pow(2,liczba_bitow-1);
   // bool *akt=genotyp;
    for(int i=0;i<liczba_bitow;i++)
    {
        wynik=wynik+genotyp[i]*potegadwojki;
       // wynik=wynik+akt->wartosc_*potegadwojki;
       // akt=akt->nastepny_;
        potegadwojki/=2;
    }
    cout<<" "<<wynik<<" ";

    return wynik;
}

double dekoduj(Osobnik *os1, int poczatek_przedzialu, int koniec_przedzialu, int liczba_bitow )
{
    double rozdzielczosc=1.0*(koniec_przedzialu-poczatek_przedzialu)/(pow(2,liczba_bitow)-1);
    double wynik=poczatek_przedzialu+binToDec(os1->genotyp_, liczba_bitow)*rozdzielczosc;
    return wynik;
}


/*funkcja celu nr 1, przykladowo 7x^6-4x^4+3,5x^3-24*x^2+14/(x^2+1);
posiada ekstrema minimum w x1=-1.20496 rowne f(x1)=-22.2665 oraz w x2=1.10024 rowne f(x2)=-11.0521
f(x1) jest ekstremum globalnym */

double f1(double x)
{
    double y=7*pow(x,6)-4*pow(x,4)+3.5*pow(x,3)-24*pow(x,2)+14/(pow(x,2)+1);
    return y;
}

void zamien(bool &x1, bool &x2)
{
    bool y=x1;
    x1=x2;
    x2=y;
}
