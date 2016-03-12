#include"interfejs.h"
#include"algorytmy.h"
#include"dane.h"
#include"osobnik.h"
//#include"gen.h"
#include <ctime>
#include <cstdlib>
//#include <windows.h>

void start()
{
    srand(time(NULL));
    Dane *wejscie=new Dane;
    wejscie->wczytajDane();
    //wejscie->drukujDane();
    Osobnik* populacja=new Osobnik;
    populacja->tworzPopulacje(8,5);  //jako argument funkcji daj obiekt DANE!!!!!!
    populacja->wyswietlPopulacje();
    populacja->usunPopulacje();
    delete populacja;
   // Sleep(5000);
    populacja->wyswietlPopulacje();
    delete wejscie;
}
