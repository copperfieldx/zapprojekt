#ifndef ALGORYTMY_H
#define ALGORYTMY_H
#include"osobnik.h"
#include"dane.h"

void operujNaDanych(Dane*);
int binToDec(bool *, int );
double dekoduj(bool *, int , int , int );
double g(double);
double f1(double);
double f2(double);//funkcja celu, f1- w domyśle do dodania następne; funkcja CIĄGŁA!(przynajmniej narazie) //do przemyślenia
void zamien(bool &, bool &);
void cykl(Osobnik *&, Dane*);


#endif // ALGORYTMY_H
