#include"algorytmy.h"
#include <cmath>
#include<iostream>
//#include<iostream>
using namespace std; //do testow



//zasadnicza czesc programu; dziala po wczytaniu danych i jest odpowiedzialna za caly przebieg
void operujNaDanych(Dane* wejscie)
{
    Osobnik* populacja=new Osobnik(wejscie->LBitow());
    populacja=tworzPopulacje(wejscie);
    populacja->wyswietlPopulacje();
    populacja->sortuj(wejscie->LOsobnikow());
    populacja->wyswietlPopulacje();
    cykl(populacja,wejscie);
    //populacja->wyswietlPopulacje();
    delete populacja;
   // populacja->wyswietlPopulacje();
}


//majac populacje poczatkowa, funkcja ta przeprowadza tworzenie nowych pokolen
void cykl(Osobnik* &populacja, Dane* wejscie)
{
    for(int i=0;i<wejscie->LPokolen();i++)
    {
    tworzKolejnaPopulacjeVol2(populacja,wejscie); //metoda rankingu liniowego
   // tworzKolejna(populacja, wejscie); //ułomna metoda nr1
    populacja->sortuj(wejscie->LOsobnikow());
    populacja->wyswietlPopulacje(); //do sledzenia na biezaco
    }
}

//przeksztalca liczbe z systemu binarnego na dziesietny;
int binToDec(bool *genotyp, int liczba_bitow)
{
    int wynik=0;
    int potegadwojki=pow(2,liczba_bitow-1);
    for(int i=0;i<liczba_bitow;i++)
    {
        wynik=wynik+genotyp[i]*potegadwojki;
        potegadwojki/=2;
    }
//    cout<<" "<<wynik<<" ";

    return wynik;
}

//dekoduje liczbe reprezentowana przez Osobnika na liczbe(punkt) w przedziale w ktorym szukamy minimum
double dekoduj(Osobnik *os1, int poczatek_przedzialu, int koniec_przedzialu, int liczba_bitow )
{
    double rozdzielczosc=1.0*(koniec_przedzialu-poczatek_przedzialu)/(pow(2,liczba_bitow)-1);
    double wynik=poczatek_przedzialu+binToDec(os1->genotyp_, liczba_bitow)*rozdzielczosc;
    return wynik;
}


/*funkcja celu nr 1, przykladowo 7x^6-4x^4+3,5x^3-24*x^2+14/(x^2+1);
posiada ekstrema minimum w x1=-1.20496 rowne f(x1)=-22.2665 oraz w x2=1.10024 rowne f(x2)=-11.0521
f(x1) jest ekstremum globalnym, f(x2) moze powodowac przedwczesna zbieznosc */

double f1(double x)
{
    double y=7*pow(x,6)-4*pow(x,4)+3.5*pow(x,3)-24*pow(x,2)+14/(pow(x,2)+1);
    return y;
}

//prosta funkcja - do testow;
double f2(double x)
{
    double y=pow(x,2)-6*x+5;
    return y;
}

//zamienia wartosciami dwie zmienne boolowskie - do operacji krzyzowania(?)
void zamien(bool &x1, bool &x2)
{
    bool y=x1;
    x1=x2;
    x2=y;
}
