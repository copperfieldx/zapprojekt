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
    double xMIN_;
    double yMIN_;

public:
    Dane();
    //5 funkcji zwracajacych odpowiednie pola dla funkcji innych niz metody i f. zaprzyjaznione;
    int Poczatek();
    int Koniec();
    int LBitow();
    int LOsobnikow();
    int LPokolen();
    double Rozdzielczosc();
    double xMIN();
    double yMIN();
    bool wczytajDaneZPliku();
    bool wczytajDaneZKlawiatury();
    //void drukujDane();
    void zapiszDoPliku();
    void ustawRozdzielczosc();
    void ustawWyjscie(double, double);

};

#endif // DANE_H
