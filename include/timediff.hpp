// $Header$
//----------------------------------------------------------------------
// timediff
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file timediff.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función timediff.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _timediff_
#define _timediff_

#include <tuple>

using namespace std;
//----------------------------------------------------------------------
//  tuple<double,double,double,double,double> timediff (double UT1_UTC, double TAI_UTC)
//----------------------------------------------------------------------
/**@brief Calcula las diferencias de tiempo de dos dados.
*
*	@param [in] UT1_UTC Primer tiempo. 
*	@param [in] TAI_UTC Segundo tiempo.  
*	@return Tupla con las diferencias de tiempo. 
*/
//----------------------------------------------------------------------
tuple<double,double,double,double,double> timediff (double UT1_UTC, double TAI_UTC);	
#endif