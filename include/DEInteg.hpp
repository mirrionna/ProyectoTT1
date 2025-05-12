#ifndef _DEINTEG_
#define _DEINTEG_

#include "..\include\matrix.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <ctime>

using namespace std;

void DEInteg(Matrix& f (double t, Matrix &y), double &t, double tout, double relerr,
  double abserr, int n_eqn, Matrix &y, int &iflag, double work[], int iwork[]);

void de ( Matrix& f (double t, Matrix &y), int neqn, double y[], 
  double &t, double tout, double relerr, double abserr, int &iflag, double yy[], 
  double wt[], double p[], double yp[], double ypout[], double phi[], 
  double alpha[], double beta[], double sig[], double v[], double w[], 
  double g[], bool &phase1, double psi[], double &x, double &h, double &hold, 
  bool &start, double &told, double &delsgn, int &ns, bool &nornd, int &k, int &kold, 
  int &isnold );
  
int i4_sign ( int i );

void intrp ( double x, double y[], double xout, double yout[], double ypout[], 
  int neqn, int kold, double phi[], double psi[] );
  
void ode ( Matrix& f (double t, Matrix &y), int neqn, double y[], 
  double &t, double tout, double relerr, double abserr, int &iflag, 
  double work[], int iwork[] );
  
double r8_epsilon ( );

double r8_max ( double x, double y );

double r8_min ( double x, double y );

double r8_sign ( double x );

void step ( double &x, double y[], Matrix& f (double t, Matrix &y), 
  int neqn, double &h, double &eps, double wt[], bool &start, double &hold, 
  int &k, int &kold, bool &crash, double phi[], double p[], double yp[], 
  double psi[], double alpha[], double beta[], double sig[], double v[], 
  double w[], double g[], bool &phase1, int &ns, bool &nornd );
  
void timestamp ( );

#endif