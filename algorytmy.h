#ifndef ALGORYTMY_H
#define ALGORYTMY_H
#include"osobnik.h"
#include"dane.h"

void operujNaDanych(Dane*);
int binToDec(bool *, int );
double dekoduj(Osobnik *, int , int , int );
double f1(double); //funkcja celu, f1- w domyśle do dodania następne; funkcja CIĄGŁA!(przynajmniej narazie)
void zamien(bool &, bool &);


#endif // ALGORYTMY_H
