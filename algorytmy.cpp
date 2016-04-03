#include"algorytmy.h"
#include <cmath>
#include<iostream>
using namespace std; //COUTy do testow



//zasadnicza czesc programu; dziala po wczytaniu danych i jest odpowiedzialna za caly przebieg
void operujNaDanych(Dane* wejscie)
{
    ustawRozdzielczosc(wejscie);
    Osobnik* populacja=new Osobnik(wejscie->LBitow());
    //tworze pierwsza populacje, wyswietlam, sortuje i znow wyswietlam - test poprawnosci
    populacja=tworzPopulacje(wejscie);
    populacja->wyswietlPopulacje();
    populacja->sortuj(wejscie->LOsobnikow());
    populacja->wyswietlPopulacje();
    cykl(populacja,wejscie); // !! tutaj się dzieje !!
    //populacja->wyswietlPopulacje();
    usunPopulacje2(*& populacja);
    //populacja->wyswietlPopulacje();
}


//majac populacje poczatkowa, funkcja ta przeprowadza tworzenie nowych pokolen
void cykl(Osobnik* &populacja, Dane* wejscie)
{
    //mniej wywolan
    int suma=sumaPrzystosowan(wejscie->LOsobnikow());
    int *tablica=tablicaPrzystosowan(wejscie->LOsobnikow());

    for(int i=0;i<wejscie->LPokolen();i++)
    {
    tworzKolejnaPopulacjeVol3(populacja,wejscie,suma,tablica); //metoda rankingu liniowego(ma przedwczesna zbieznosc)
   // tworzKolejna(populacja, wejscie); //ułomna metoda nr1
    populacja->sortuj(wejscie->LOsobnikow());
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
//    cout<<" "<<wynik<<" ";

    return wynik;
}

//wywolana raz i zapisana wartosc - oszczednosc wywolan
double rozdzielczosc(int poczatek_przedzialu, int koniec_przedzialu, int liczba_bitow)
{
    double tmp=1.0*(koniec_przedzialu-poczatek_przedzialu)/(pow(2,liczba_bitow)-1);
    return tmp;
}

void ustawRozdzielczosc(Dane *tmp)
{
    tmp->rozdzielczosc_=rozdzielczosc(tmp->poczatek_przedzialu_, tmp->koniec_przedzialu_, tmp->liczba_bitow_);
}

//dekoduje liczbe reprezentowana przez Osobnika na liczbe(punkt) w przedziale w ktorym szukamy minimum
double dekoduj( bool* tab_bool, int poczatek_przedzialu, int liczba_bitow, double rozdzielczosc)
{
    double wynik=poczatek_przedzialu+binToDec(tab_bool, liczba_bitow)*rozdzielczosc;
    return wynik;
}

//minimum w x=-0.422884; f(x)=-2.24537;
double g(double x)
{
    double y=pow(x,3)-pow(x,2)+sin(4*x)-cos(15*x);
    return y;
}

/*funkcja celu nr 1, przykladowo 7x^6-4x^4+3,5x^3-24*x^2+14/(x^2+1);
posiada ekstrema minimum w x1=-1.20496 rowne f(x1)=-22.2665 oraz w x2=1.10024 rowne f(x2)=-11.5021
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
