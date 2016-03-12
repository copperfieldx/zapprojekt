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
    Gen* zwrocGenotyp();
    Osobnik* adresNastepnego();
    void wyswietlPopulacje();
    friend Osobnik* tworzPopulacje(int ile_osobnikow, int jaka_dlugosc);
    friend void usunPopulacje(Osobnik *wsk);
    friend Gen* tworz(int dlugosc);
    friend double dekoduj(Osobnik *, int , int , int );
    friend void krzyzuj(Osobnik *, Osobnik *, int);
    friend void zamien(Gen*, Gen*);

};

Osobnik* tworzPopulacje(int ile_osobnikow, int jaka_dlugosc);
void krzyzuj(Osobnik *, Osobnik *, int);

#endif // OSOBNIK_H
