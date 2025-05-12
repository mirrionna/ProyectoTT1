// $Header$
//----------------------------------------------------------------------
// Accel
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file Accel.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función Accel.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _Accel_
#define _Accel_

#include <cmath>
#include "..\include\matrix.h"
#include "..\include\global.hpp"
#include "..\include\SAT_Const.hpp"
#include "..\include\IERS.hpp"
#include "..\include\timediff.hpp"
#include "..\include\Mjday_TDB.hpp"
#include "..\include\JPL_Eph_DE430.hpp"
#include "..\include\AccelHarmonic.hpp"
#include "..\include\AccelPointMass.hpp"
#include "..\include\PrecMatrix.hpp"
#include "..\include\NutMatrix.hpp"
#include "..\include\PoleMatrix.hpp"
#include "..\include\GHAMatrix.hpp"
//----------------------------------------------------------------------
//  Matrix& Accel (double x, Matrix& Y)
//----------------------------------------------------------------------
/**@brief Calcula la aceleración de un satélite orbitando la Tierra debido al campo gravitacional armónico de la Tierra, las perturbaciones gravitacionales del Sol y la Luna, la presión de la radiación solar y la resistencia atmosférica.
*
*	@param [in] x Tiempo terrestre.  
*	@param [in] Y Vector de estado del satélite en el sistema ICRF/EME2000.   
*	@return Matriz con la aceleración pertubacional. 
*/
//----------------------------------------------------------------------
Matrix& Accel (double x, Matrix& Y);	
#endif