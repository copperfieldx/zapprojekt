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
    //wejscie->drukujDane(); //test dzialania
    operujNaDanych(wejscie); //zasadnicza czesc programu
    delete wejscie;
   // wejscie->drukujDane();
}\

//napisz nowa funkcje z argumentem Dane *wejscie i tam operuj na podanych w pliku!!!!
