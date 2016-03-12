#ifndef GEN_H
#define GEN_H

class Gen
{
    bool wartosc_;
    Gen *nastepny_;
public:
    Gen();
    ~Gen();
    Gen* tworz(int dlugosc);
    void wyswietl();
    void usunListe();
};

#endif // GEN_H
