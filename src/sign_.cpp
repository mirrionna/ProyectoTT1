// $Source$
//----------------------------------------------------------------------
// sign_
//----------------------------------------------------------------------
// Proyecto TT1
//
/**@file sign_.cpp
*	@brief Cálculo del valor absoluto de un número con el signo de otro.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\sign_.hpp"

double sign_ (double a, double b){
	double result=0;
	if (b>=0.0){
		result = abs(a);
	}
	else{
		result = - abs(a);
	}
	return result;
}