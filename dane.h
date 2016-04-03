#ifndef DANE_H
#define DANE_H

class Dane
{
    int poczatek_przedzialu_;
    int koniec_przedzialu_;
    int liczba_bitow_;
    int liczba_osobnikow_;
    int liczba_pokolen_;
    double rozdzielczosc_; //wyliczana w trakcie

public:
    Dane();
    //~Dane();
    //5 funkcji zwracajacych odpowiednie pola dla funkcji innych niz metody i f. zaprzyjaznione;
    int Poczatek();
    int Koniec();
    int LBitow();
    int LOsobnikow();
    int LPokolen();
    double Rozdzielczosc();
    bool wczytajDaneZPliku();
    bool wczytajDaneZKlawiatury();
    void drukujDane();
    friend void ustawRozdzielczosc(Dane*);

};

#endif // DANE_H
