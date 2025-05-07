// $Header$
//----------------------------------------------------------------------
// gast
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file gast.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función gast.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _gast_
#define _gast_

#include <cmath>
#include "..\include\matrix.h"
#include "..\include\gmst.hpp"
#include "..\include\EqnEquinox.hpp"
#include "..\include\SAT_Const.hpp"
//----------------------------------------------------------------------
//  double gast (double Mjd_UT1)
//----------------------------------------------------------------------
/**@brief Calcula el tiempo sidéreo aparente Greenwich.
*
*	@param [in] Mjd_UT1 Fecha juliana modificada.
*	@return Double con el tiempo sidéreo aparente Greenwich. 
*/
//----------------------------------------------------------------------
double gast (double Mjd_UT1);	
#endif