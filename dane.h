    #ifndef DANE_H
#define DANE_H

class Dane
{
    int poczatek_przedzialu_;
    int koniec_przedzialu_;
    int liczba_bitow_;
    int liczba_osobnikow_;
    int liczba_pokolen_;

public:
    Dane();
    //~Dane();
    int Poczatek();
    int Koniec();
    int LBitow();
    int LOsobnikow();
    int LPokolen();
    void wczytajDane();
    void drukujDane();

};

#endif // DANE_H
