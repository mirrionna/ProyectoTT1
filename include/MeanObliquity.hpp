// $Header$
//----------------------------------------------------------------------
// MeanObliquity
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file MeanObliquity.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función MeanObliquity.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _MeanObliquity_
#define _MeanObliquity_
#include "..\include\SAT_Const.hpp"
//----------------------------------------------------------------------
//  double MeanObliquity(double Mjd_TT)
//----------------------------------------------------------------------
/**@brief Calcula la oblicuidad media de la eclíptica, en radianes.
*
*	@param [in] Mjd_TT Fecha juliana modificada(Tiempo terrestre)
*	@return Oblicuidad media de la eclíptica, en radianes.
*/
//----------------------------------------------------------------------
double MeanObliquity(double Mjd_TT);
#endif