#include "interfejs.h"
#include "algorytmy.h"
#include "dane.h"
#include "osobnik.h"
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
    //wejscie->drukujDane();
}\

