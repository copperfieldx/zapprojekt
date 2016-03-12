#ifndef OSOBNIK_H
#define OSOBNIK_H
#include"gen.h"



class Osobnik
{
    Gen *gen_;
    Osobnik *nastepny_osobnik_;
public:
    Osobnik();
    ~Osobnik();
    void wyswietlPopulacje();
    friend Osobnik* tworzPopulacje(int ile_osobnikow, int jaka_dlugosc);
    friend void usunPopulacje(Osobnik *wsk);
    friend Gen* tworz(int dlugosc);
    friend float dekoduj(Osobnik *, int , int , int );

};

Osobnik* tworzPopulacje(int ile_osobnikow, int jaka_dlugosc);

#endif // OSOBNIK_H
