// $Header$
//----------------------------------------------------------------------
// NutAngles
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file NutAngles.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función NutAngles.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _NutAngles_
#define _NutAngles_

#include <cmath>
#include <tuple>
#include "..\include\matrix.h"
#include "..\include\SAT_Const.hpp"
//----------------------------------------------------------------------
//  tuple<double,double> NutAngles (double Mjd_TT)
//----------------------------------------------------------------------
/**@brief Calcula la nutación en longitud y oblicuidad.
*
*	@param [in] Mjd_TT Fecha juliana modificada, en tiempo terrestre.  
*	@return Tupla con la nutación en longitud y oblicuidad. 
*/
//----------------------------------------------------------------------
tuple<double,double> NutAngles (double Mjd_TT);
#endif