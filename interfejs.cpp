#include "interfejs.h"
#include "algorytmy.h"
#include "dane.h"
#include "osobnik.h"
#include "gen.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std; //do prototypu, potem usunac

void start()
{
    srand(time(NULL));
    Dane *wejscie=new Dane;
    wejscie->wczytajDane();
    //wejscie->drukujDane();
    Osobnik* populacja=new Osobnik;
    populacja=tworzPopulacje(8,5);  //jako argument funkcji daj obiekt DANE!!!!!!
    populacja->wyswietlPopulacje();
    cout<<dekoduj(populacja,0,5,5);
    usunPopulacje(populacja);
    delete populacja;
    populacja->wyswietlPopulacje();
    delete wejscie;
    wejscie->drukujDane();
}\


//napisz nowa funkcje z argumentem Dane *wejscie i tam operuj na podanych w pliku!!!!
