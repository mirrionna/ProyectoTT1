// $Header$
//----------------------------------------------------------------------
// IERS
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file IERS.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función IERS.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _IERS_
#define _IERS_

#include <cmath>
#include <tuple>
#include "..\include\matrix.h"
#include "..\include\SAT_Const.hpp"
//----------------------------------------------------------------------
//  tuple<double,double,double,double,double,double,double,double,double> IERS(Matrix &eop,double Mjd_UTC,char interp);
//----------------------------------------------------------------------
/**@brief Calcula los tiempos IERS y los datos de movimiento polar.
*
*	@param [in] eop Matriz eop.   
*	@param [in] Mjd_UTC Tiempo juliano en UTC.  
*	@param [in] interp Tipo de interpolación, 'n' o 'l'.  
*	@return Tupla con los tiempos IERS y los datos de movimiento polar. 
*/
//----------------------------------------------------------------------
tuple<double,double,double,double,double,double,double,double,double> IERS(Matrix &eop,double Mjd_UTC,char interp);
//----------------------------------------------------------------------
//  tuple<double,double,double,double,double,double,double,double,double> IERS(Matrix &eop,double Mjd_UTC);
//----------------------------------------------------------------------
/**@brief Calcula los tiempos IERS y los datos de movimiento polar.
*
*	@param [in] eop Matriz eop.   
*	@param [in] Mjd_UTC Tiempo juliano en UTC.  
*	@return Tupla con los tiempos IERS y los datos de movimiento polar. 
*/
//----------------------------------------------------------------------
tuple<double,double,double,double,double,double,double,double,double> IERS(Matrix &eop,double Mjd_UTC);
#endif