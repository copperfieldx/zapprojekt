#ifndef GEN_H
#define GEN_H

class Gen
{
    bool wartosc_;
    Gen *nastepny_;
public:
    Gen();
    ~Gen();
    Gen* tworz(int);
    void wyswietl();
    friend void usunListe(Gen *);
    friend int binToDec(Gen *, int);
};


#endif // GEN_H
