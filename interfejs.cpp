#include "interfejs.h"
#include "algorytmy.h"
#include "dane.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;


void start()
{
    srand(time(NULL));
    Dane *wejscie=new Dane;
    bool metoda=0;
    cout<<"Wybierz sposob wprowadzania danych:\n 0-dane z klawiatury \n 1-dane z pliku\n";
    cin>>metoda;
    if(metoda)
    {
        while(!wejscie->wczytajDaneZPliku()){}
    }
    else
    {
        while(!wejscie->wczytajDaneZKlawiatury()){}
    }
    operujNaDanych(wejscie);
    wejscie->zapiszDoPliku();
    delete wejscie;
}\

