// $Header$
//----------------------------------------------------------------------
// Mjday_TDB
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file Mjday_TDB.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función Mjday_TDB.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _Mjday_TDB_
#define _Mjday_TDB_

#include <cmath>
//----------------------------------------------------------------------
//  double Mjday_TDB (int yr, int mon, int day, int hr, int min, int sec)
//----------------------------------------------------------------------
/**@brief Calcula la fecha juliana modificada para un tiempo dinámico baricéntrico.
*
*	@param [in] Mjd_TT Fecha juliana modificada (TT).    
*	@return Fecha juliana modificada (TDB). 
*/
//----------------------------------------------------------------------
double Mjday_TDB (double Mjd_TT);	
#endif