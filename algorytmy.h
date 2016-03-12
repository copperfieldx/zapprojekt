#ifndef ALGORYTMY_H
#define ALGORYTMY_H
#include"osobnik.h"
#include"gen.h"
#include"dane.h"

void operujNaDanych(Dane*);
int binToDec(Gen *, int );
double dekoduj(Osobnik *, int , int , int );
double f1(double); //funkcja celu, f1- w domyśle do dodania następne; funkcja CIĄGŁA!(przynajmniej narazie)


#endif // ALGORYTMY_H
