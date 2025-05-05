// $Header$
//----------------------------------------------------------------------
// gmst
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file gmst.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función gmst.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _gmst_
#define _gmst_

#include <cmath>
#include <iostream>
using namespace std;
#include "..\include\SAT_Const.hpp"
//----------------------------------------------------------------------
//  double gmst(double Mjd_UT1)
//----------------------------------------------------------------------
/**@brief Calcula el tiempo medio sidéreo de Greenwich.
*
*	@param [in] Mjd_UT1 Fecha juliana modificada.  
*	@return GMST en radianes. 
*/
//----------------------------------------------------------------------
double gmst(double Mjd_UT1);	
#endif