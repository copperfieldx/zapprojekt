#ifndef OSOBNIK_H
#define OSOBNIK_H
#include "dane.h"


class Osobnik
{
    bool* genotyp_;
    int rozmiar_;
    double zdekodowany_;
    double przystosowanie_;
    Osobnik *nastepny_osobnik_;

public:
    Osobnik(int);
    ~Osobnik();
    bool* zwrocGenotyp();
    double zdekodowany();
    double przystosowanie();
    Osobnik* adresNastepnego();
    void wyswietlPopulacje();
    void losuj();
    void mutuj();
    void sortuj();
    Osobnik* zwrocAdresITegoElementu(int);
    friend void usunPopulacje(Osobnik *&wsk);
    friend Osobnik* tworzPopulacje(Dane *);
    friend void tworzKolejnaPopulacje(Osobnik*&, Dane*, int, int*);
    friend void krzyzuj(Osobnik *, Osobnik *, Osobnik *);
};


void usunPopulacje(Osobnik *&wsk);
Osobnik* tworzPopulacje(Dane *); //pierwsza populacja
void tworzKolejnaPopulacje(Osobnik *&, Dane *, int, int*);//metoda rankingu liniowego - z 2 osobnikow zawsze 2;podzial pol na pol
void krzyzuj(Osobnik *, Osobnik *, Osobnik*);

#endif // OSOBNIK_H
