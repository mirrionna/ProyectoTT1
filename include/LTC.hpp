// $Header$
//----------------------------------------------------------------------
// LTC
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file LTC.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función LTC.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _LTC_
#define _LTC_

#include <cmath>
#include "..\include\matrix.h"
#include "..\include\R_y.hpp"
#include "..\include\R_z.hpp"
//----------------------------------------------------------------------
//  Matrix& LTC (Matrix& r, Matrix& s, double GM)
//----------------------------------------------------------------------
/**@brief Calcula la matriz de rotación desde el ecuador norte y el meridiano de Greenwich hasta el sistema de coordenadas de la tangente local.
*
*	@param [in] lon Longitud geodésica este.  
*	@param [in] lat Latitud geodésica.
*	@return Matriz de rotación desde el ecuador norte y el meridiano de Greenwich hasta el sistema de coordenadas de la tangente local. 
*/
//----------------------------------------------------------------------
Matrix& LTC (double lon, double lat);	
#endif