#ifndef ALGORYTMY_H
#define ALGORYTMY_H
#include"osobnik.h"
#include"dane.h"

void operujNaDanych(Dane*);
void cykl(Osobnik *&, Dane*);
int binToDec(bool *, int );
double rozdzielczosc(int, int, int);
double dekoduj(bool *, int , int , double);
double f1(double);
void zamien(bool &, bool &);
int sumaPrzystosowan(int);
int* tablicaPrzystosowan(int);

#endif // ALGORYTMY_H
