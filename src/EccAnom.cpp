// $Source$
//----------------------------------------------------------------------
// EccAnom
//----------------------------------------------------------------------
// Proyecto TT1
//
/**@file EccAnom.cpp
*	@brief Cálculo de la anomalía excéntrica de una órbita elíptica.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\EccAnom.hpp"

//----------------------------------------------------------------------
//  double modeccanom(double a,double b)
//----------------------------------------------------------------------
/**@brief Función auxiliar para adaptar la funcion fmod a la correspondiente en Matlab.
*
*	@param [in] a Dividendo.
*	@param [in] b Divisor.
*	@return Devuelve el resto de dividir a/b, entre 0 y b.
*/
//----------------------------------------------------------------------
double modeccanom(double a,double b){
	double r=fmod(a,b);
	if(r<0){
		r+=b;
	}
	return r;
}


double EccAnom (double M, double e){
	int maxit = 15;
	int i = 1;

	// Starting value
	M = modeccanom(M,2.0*std::numbers::pi);
	double E = 0;
	if (e<0.8){
		E = M;
	}
	else{
		E = std::numbers::pi;
	}

	double f = E - e*sin(E) - M;
	E = E - f / ( 1.0 - e*cos(E) );
	
	double eps=1e-10;
	// Iteration
	while (abs(f) > 1e2*eps){    
		f = E - e*sin(E) - M;
		E = E - f / ( 1.0 - e*cos(E) );
		i = i+1;
		if (i==maxit){
			cout<<" convergence problems in EccAnom";
			exit(EXIT_FAILURE);
		}  
	}
	
	return E;

}
