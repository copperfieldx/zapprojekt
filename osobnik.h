#ifndef OSOBNIK_H
#define OSOBNIK_H
//#include"algorytmy.h"


class Osobnik
{
    //Gen *gen_;
    int rozmiar_;
    bool* genotyp_;
    Osobnik *nastepny_osobnik_;
public:
    Osobnik(int);
    ~Osobnik();
    bool* zwrocGenotyp();
    Osobnik* adresNastepnego();
    void wyswietlPopulacje();
    void losuj();
    friend Osobnik* tworzPopulacje(int ile_osobnikow, int jaka_dlugosc);
    friend void usunPopulacje(Osobnik *wsk);
    //friend Gen* tworz(int dlugosc);
    friend double dekoduj(Osobnik *, int , int , int );
    friend void krzyzuj(Osobnik *, Osobnik *, int);
    //friend void zamien(Gen*, Gen*);
    friend void zamien(bool&,bool&);
};

Osobnik* tworzPopulacje(int ile_osobnikow, int jaka_dlugosc);
void krzyzuj(Osobnik *, Osobnik *, int);

#endif // OSOBNIK_H
