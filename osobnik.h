#ifndef OSOBNIK_H
#define OSOBNIK_H
#include "dane.h"


class Osobnik
{
    int rozmiar_; //rozmiar bedzie staly dla kadzego osobnika - przemysl, poszukaj jak oszczedzic pamiec, ale zmienna moze sie przyspieszyc dzialanie
    bool* genotyp_;
    double zdekodowany_; //propozycja, moze sie przydac
    Osobnik *nastepny_osobnik_;
    double przystosowanie_;
public:
    Osobnik(int);
    ~Osobnik();
    bool* zwrocGenotyp();
    Osobnik* adresNastepnego();
    void wyswietlPopulacje();
    void losuj();
    void mutuj();
    void sortuj(int);
    Osobnik* zwrocAdresITegoElementu(int);
    friend void usunPopulacje(Osobnik *&wsk);
    friend void usunPopulacje2(Osobnik *&wsk);
    friend Osobnik* tworzPopulacje(Dane *);
    friend void tworzKolejna(Osobnik*, Dane *);
    friend void tworzKolejnaPopulacjeVol2(Osobnik*&, Dane*, int, int*);
    friend void tworzKolejnaPopulacjeVol3(Osobnik*&, Dane*, int, int*);

    //friend double dekoduj(bool *, int , int , int );
    friend void krzyzuj(Osobnik *, Osobnik *, Osobnik *);
    //friend void zamien(bool&,bool&);
};

//poszukaj czy to jest konieczne; bez tego prosi o deklaracje
void usunPopulacje(Osobnik *&wsk);
void usunPopulacje2(Osobnik *&wsk);
Osobnik* tworzPopulacje(Dane *); //pierwsza populacja
void tworzKolejna(Osobnik *, Dane*); //kolejna populacja, ulomna, ale napisana jako pierwsza :D
void tworzKolejnaPopulacjeVol2(Osobnik *&, Dane *, int, int*);//metoda rankingu liniowego - z 2 osobnikow zawsze 1 i znowu to samo
void tworzKolejnaPopulacjeVol3(Osobnik *&, Dane *, int, int*);//metoda rankingu liniowego - z 2 osobnikow zawsze 2 podzial pol na pol
void krzyzuj(Osobnik *, Osobnik *, Osobnik*);

#endif // OSOBNIK_H
