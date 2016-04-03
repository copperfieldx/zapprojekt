#include "interfejs.h"
#include "algorytmy.h"
#include "dane.h"
#include <ctime> //do losowania
#include <cstdlib>
#include <iostream>
using namespace std;

//funkcja ustawiona w mainie(), jedna z nadrzednych;
void start()
{
    srand(time(NULL)); //losowosc
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
         //wejscie->drukujDane(); //test dzialania
    operujNaDanych(wejscie); //zasadnicza czesc programu
    delete wejscie;
}\

