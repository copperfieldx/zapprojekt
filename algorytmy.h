#ifndef ALGORYTMY_H
#define ALGORYTMY_H
#include"osobnik.h"
#include"dane.h"

void operujNaDanych(Dane*);
void cykl(Osobnik *&, Dane*);
int binToDec(bool *, int );
double rozdzielczosc(int, int, int);
void ustawRozdzielczosc(Dane *);
double dekoduj(bool *, int , int , double);
double g(double);
double f1(double);
double f2(double);//funkcja celu, f1- w domyśle do dodania następne; funkcja CIĄGŁA!(przynajmniej narazie) //do przemyślenia
void zamien(bool &, bool &);
int sumaPrzystosowan(int);
int* tablicaPrzystosowan(int);




#endif // ALGORYTMY_H
