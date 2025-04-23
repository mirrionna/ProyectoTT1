// $Header$
//----------------------------------------------------------------------
// Legendre
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file Legendre.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función Legendre.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _Legendre_
#define _Legendre_

#include <cmath>
#include <tuple>
#include "..\include\matrix.h"
//----------------------------------------------------------------------
//  tuple<Matrix,Matrix> Legendre (int n, int m, double fi);	
//----------------------------------------------------------------------
/**@brief Calcula la aceleración perturbacional debido a un punto de masas.
*
*	@param [in] n Grado del polinomio. 
*	@param [in] m Orden del polinomio.
*	@param [in] fi Ángulo en radianes.  
*	@return Matriz con la aceleración pertubacional. 
*/
//----------------------------------------------------------------------
tuple<Matrix,Matrix> Legendre (int n, int m, double fi);	
#endif