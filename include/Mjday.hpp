// $Header$
//----------------------------------------------------------------------
// Mjday
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file Mjday.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función Mjday.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _Mjday_
#define _Mjday_

#include <cmath>
//----------------------------------------------------------------------
//  double Mjday (int yr, int mon, int day, int hr, int min, int sec)
//----------------------------------------------------------------------
/**@brief Calcula la fecha juliana modificada de una dada.
*
*	@param [in] yr Año de la fecha.  
*	@param [in] mon Mes de la fecha.  
*	@param [in] day Día de la fecha.  
*	@param [in] hr Horas de la fecha.  
*	@param [in] min Minutos de la fecha.  
*	@param [in] sec Segundos de la fecha.   
*	@return Fecha juliana modificada. 
*/
//----------------------------------------------------------------------
double Mjday (int yr, int mon, int day, int hr, int min, int sec);	
//----------------------------------------------------------------------
//  double Mjday (int yr, int mon, int day)
//----------------------------------------------------------------------
/**@brief Calcula la fecha juliana modificada de una dada.
*
*	@param [in] yr Año de la fecha.  
*	@param [in] mon Mes de la fecha.  
*	@param [in] day Día de la fecha.   
*	@return Fecha juliana modificada. 
*/
//----------------------------------------------------------------------
double Mjday (int yr, int mon, int day);	
#endif