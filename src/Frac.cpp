// $Source$
//----------------------------------------------------------------------
// Frac
//----------------------------------------------------------------------
// Proyecto TT1
//
/**@file Frac.cpp
*	@brief Cálculo de la parte fraccional de un número.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\Frac.hpp"

double Frac (double x){
	double res = x-floor(x);
	return res;
}
