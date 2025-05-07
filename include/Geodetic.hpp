// $Header$
//----------------------------------------------------------------------
// Geodetic
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file Geodetic.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función Geodetic.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _Geodetic_
#define _Geodetic_

#include <cmath>
#include <tuple>
#include "..\include\matrix.h"
#include "..\include\SAT_Const.hpp"
//----------------------------------------------------------------------
//  tuple<double,double,double> Geodetic (Matrix &r)
//----------------------------------------------------------------------
/**@brief Calcula las coordenadas geodésicas a partir de un vector de posición.
*
*	@param [in] r Vector de posición en metros.  
*	@return Tupla con la longitud en radianes, latitud en radines y la altitud en metros. 
*/
//----------------------------------------------------------------------
tuple<double,double,double> Geodetic (Matrix &r);	
#endif