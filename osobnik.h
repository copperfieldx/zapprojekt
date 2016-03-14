#ifndef OSOBNIK_H
#define OSOBNIK_H
//#include"algorytmy.h"
#include "dane.h"


class Osobnik
{

    int rozmiar_; //rozmiar bedzie staly dla kadzego osobnika - przemysl, poszukaj jak oszczedzic pamiec, ale zmienna moze sie przyspieszyc dzialanie
    bool* genotyp_;
    //double zdekodowany_; //propozycja, moze sie przydac
    Osobnik *nastepny_osobnik_;
    double przystosowanie_;
public:
    Osobnik(int);
    ~Osobnik();
    //funkcje zwroc moga sie przydac poza metodami i funkcjami zaprzyjaznionymi
    bool* zwrocGenotyp();
    Osobnik* adresNastepnego();
    double zwrocPrzystosowanie();
    void wyswietlPopulacje();
    void losuj();
    void mutuj();
    void ustalPrzystosowanie(double);
    void sortuj(int);
    friend Osobnik* tworzPopulacje(Dane *);
    friend void tworzKolejna(Osobnik*, Dane *);
    friend void usunPopulacje(Osobnik *wsk);
    friend double dekoduj(Osobnik *, int , int , int );
    friend void krzyzuj(Osobnik *, Osobnik *, Osobnik *);
    friend void zamien(bool&,bool&);
};

//poszukaj czy to jest konieczne; bez tego prosi o deklaracje
Osobnik* tworzPopulacje(Dane *);
void tworzKolejna(Osobnik *, Dane*); // do cyklu
void krzyzuj(Osobnik *, Osobnik *, Osobnik*);

#endif // OSOBNIK_H
