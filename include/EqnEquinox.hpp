// $Header$
//----------------------------------------------------------------------
// EqnEquinox
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file EqnEquinox.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función EqnEquinox.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _EqnEquinox_
#define _EqnEquinox_

#include <cmath>
#include "..\include\NutAngles.hpp"
#include "..\include\MeanObliquity.hpp"
//----------------------------------------------------------------------
//  double EqnEquinox (double Mjd_TT)
//----------------------------------------------------------------------
/**@brief Calcula ecuación de los equinoccios.
*
*	@param [in] Mjd_TT Fecha juliana modificada (tiempo terrestre).  
*	@return Ecuación de los equinoccios. 
*/
//----------------------------------------------------------------------
double EqnEquinox (double Mjd_TT);	
#endif