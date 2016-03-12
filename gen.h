#ifndef GEN_H
#define GEN_H
#include "osobnik.h"

class Gen
{
    bool wartosc_;
    Gen *nastepny_;
public:
    Gen();
    ~Gen();
    Gen* tworz(int);
    bool zwrocWartosc();
    Gen* zwrocAdresNastepnego();
    void wyswietl();
    friend void usunListe(Gen *);
    friend int binToDec(Gen *, int);
    friend void krzyzuj(Osobnik*, Osobnik*, int);
    friend void zamien(Gen*, Gen*);
};


#endif // GEN_H
