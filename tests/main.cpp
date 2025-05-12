// $Source$
//----------------------------------------------------------------------
// main
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file main.cpp
*	@brief Archivo principal del proyecto de TTI.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\matrix.h"
#include "..\include\rpoly.h"
#include <iostream>

using namespace std;
double calcularmayorraizrealmain(Matrix& poly){
	double coef[10], zeror[10], zeroi[10];
	coef[0]=1;
	coef[1]=0;
	coef[2]=0;
	coef[3]=0;
	coef[4]=-1;
	int nr = real_poly_roots(coef, 4, zeror, zeroi);
	for (int i=0; i<nr; ++i) {
        printf("Raiz %d   preal = %.20lf  pimag =  %.20lf\n", i+1, zeror[i], zeroi[i]);
    }
    printf("Raices reales\n");
    for (int i=0; i<nr; ++i) {
        if(fabs(zeroi[i]) < 10e-12)
            printf("Raiz %d   preal = %.20lf  pimag =  %.20lf\n", i+1, zeror[i], zeroi[i]);
    }
	double bigr2= -99999990.0;
	for (int i=0; i<nr; ++i) {
			if((fabs(zeroi[i]) < 10e-12) && (zeror[i]>bigr2)){
					bigr2 = zeror[i];
				}
    }
	return bigr2;
} 
int main() {
    Matrix poly(5);
	poly(1)=1;
	poly(5)=-1;
	cout<<calcularmayorraizrealmain(poly);
    return 0;
}