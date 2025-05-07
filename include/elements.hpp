// $Header$
//----------------------------------------------------------------------
// elements
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file elements.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función elements.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _elements_
#define _elements_

#include <cmath>
#include "..\include\matrix.h"
#include "..\include\SAT_Const.hpp"
//----------------------------------------------------------------------
//  tuple<double,double,double,double,double,double,double> elements (Matrix& y)
//----------------------------------------------------------------------
/**@brief Calcula el semilatus rectum, el semieje mayor, la excentricidad, la inclinación, la longitud del nodo ascendente, el argumento del periastro y la anomalía media a partir del vector estado.
*
*	@param [in] y Vector estado (x,y,z,vx,vy,vz).  
*	@return Tupla con el semilatus rectum en metros, el semieje mayor, la execentricidad, la inclinación en radianes, la longitud del nodo ascendente en radianes, el argumento del periastro en radianes y la anomalía media en radianes.
*/
//----------------------------------------------------------------------
tuple<double,double,double,double,double,double,double> elements (Matrix& y);	
#endif