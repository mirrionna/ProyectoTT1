// $Header$
//----------------------------------------------------------------------
// EccAnom
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file EccAnom.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función EccAnom.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _EccAnom_
#define _EccAnom_
#include <iostream>
#include <cmath>

using namespace std;
//----------------------------------------------------------------------
//  double EccAnom (double M, double e)
//----------------------------------------------------------------------
/**@brief Calcula la anomalía excéntrica de una órbita elíptica.
*
*	@param [in] M Anomalía media en radianes.  
*	@param [in] E Excentricidad de la órbita, en el intervalo [0,1].  
*	@return Double con la anomalía excéntrica de una órbita elíptica. 
*/
//----------------------------------------------------------------------
double EccAnom (double M, double e);
#endif