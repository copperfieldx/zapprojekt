#include"algorytmy.h"
#include <cmath>
#include<iostream>
using namespace std;



//zasadnicza czesc programu; dziala po wczytaniu danych i jest odpowiedzialna za caly przebieg
void operujNaDanych(Dane* wejscie)
{
    wejscie->ustawRozdzielczosc();
    Osobnik* populacja=new Osobnik(wejscie->LBitow());
    populacja=tworzPopulacje(wejscie);
    populacja->sortuj();
    populacja->wyswietlPopulacje();
    cykl(populacja,wejscie); // !! tutaj się dzieje !!

    double xMIN=populacja->zwrocAdresITegoElementu(wejscie->LOsobnikow())->zdekodowany();
    double yMIN=populacja->zwrocAdresITegoElementu(wejscie->LOsobnikow())->przystosowanie();
    wejscie->ustawWyjscie(xMIN,yMIN);
    usunPopulacje(*& populacja);
}


//majac populacje poczatkowa, funkcja ta przeprowadza tworzenie nowych pokolen
void cykl(Osobnik* &populacja, Dane* wejscie)
{
    //mniej wywolan
    int suma=sumaPrzystosowan(wejscie->LOsobnikow());
    int *tablica=tablicaPrzystosowan(wejscie->LOsobnikow());

    for(int i=0;i<wejscie->LPokolen();i++)
    {
    tworzKolejnaPopulacje(populacja,wejscie,suma,tablica); //metoda rankingu liniowego
    populacja->sortuj();
    populacja->wyswietlPopulacje(); //do sledzenia na biezaco
    }
}

//przeksztalca liczbe z systemu binarnego na dziesietny;
int binToDec(bool *tab_bool, int liczba_bitow) //tablica boolowska i jej rozmiar;
{
    int wynik=0;
    int potegadwojki=pow(2,liczba_bitow-1);
    for(int i=0;i<liczba_bitow;i++)
    {
        wynik=wynik+tab_bool[i]*potegadwojki;
        potegadwojki/=2;
    }
    return wynik;
}

//wywolana raz i zapisana wartosc - oszczednosc wywolan
double rozdzielczosc(int poczatek_przedzialu, int koniec_przedzialu, int liczba_bitow)
{
    double tmp=1.0*(koniec_przedzialu-poczatek_przedzialu)/(pow(2,liczba_bitow)-1);
    return tmp;
}



//dekoduje liczbe reprezentowana przez Osobnika na liczbe(punkt) w przedziale w ktorym szukamy minimum
double dekoduj( bool* tab_bool, int poczatek_przedzialu, int liczba_bitow, double rozdzielczosc)
{
    double wynik=poczatek_przedzialu+binToDec(tab_bool, liczba_bitow)*rozdzielczosc;
    return wynik;
}


/*
funkcja celu nr 1, przykladowo 7x^6-4x^4+3,5x^3-24*x^2+14/(x^2+1);
posiada ekstrema minimum w x1=-1.20496 rowne f(x1)=-22.2665 oraz w x2=1.10024 rowne f(x2)=-11.5021
*/

double f1(double x)
{

    double y=7*pow(x,6)-4*pow(x,4)+3.5*pow(x,3)-24*pow(x,2)+14/(pow(x,2)+1);
    return y;
}

//zamienia wartosciami dwie zmienne boolowskie - do operacji krzyzowania
void zamien(bool &x1, bool &x2)
{
    bool y=x1;
    x1=x2;
    x2=y;
}

int sumaPrzystosowan(int LOsobnikow)
{
    int tmp=((1+LOsobnikow)/2)*LOsobnikow; //(1+n)/2*n - suma ciagu liczb od 1 do n;
    return tmp;
}

int* tablicaPrzystosowan(int LOsobnikow)
{

    int* tmp=new int[LOsobnikow];
    int x=0;
    for(int i=0;i<LOsobnikow;i++)
    {
        x=x+i+1; //1, 1+2, (1+2)+3, etc.
        tmp[i]=x; //zawiera "przedzialy"
    }
    return tmp;
}


