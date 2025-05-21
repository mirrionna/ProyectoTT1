// $Header$
//----------------------------------------------------------------------
// AzElPa
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file AzElPa.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función AzElPa.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _AzElPa_
#define _AzElPa_

#include <cmath>
#include <numbers>
#include <tuple>
#include "..\include\matrix.h"
#include "..\include\SAT_Const.hpp"

//----------------------------------------------------------------------
//  tuple<double,double,Matrix&,Matrix&> AzElPa (Matrix &s);
//----------------------------------------------------------------------
/**@brief Calcula el acimut, la elevación y las parciales de las coordenadas locales tangentes.
*
*	@param [in] s Coordenadas locales tangentes.  
*	@return Tupla con el acimut, la elevación y las parciales. 
*/
//----------------------------------------------------------------------
tuple<double,double,Matrix&,Matrix&> AzElPa (Matrix &s);	
#endif