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
    Osobnik* tworzPopulacje(int ile_genow, int jaka_dlugosc);
    void wyswietlPopulacje();
    void usunPopulacje();
};

#endif // OSOBNIK_H
