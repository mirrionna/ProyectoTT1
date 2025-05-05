// $Header$
//----------------------------------------------------------------------
// JPL_Eph_DE430
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file JPL_Eph_DE430.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función JPL_Eph_DE430.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _JPL_Eph_DE430_
#define _JPL_Eph_DE430_

#include <cmath>
#include <tuple>
#include "..\include\matrix.h"
#include "..\include\global.hpp"
#include "..\include\Cheb3D.hpp"
//----------------------------------------------------------------------
//  tuple<Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&> JPL_Eph_DE430 (double Mjd_TDB)
//----------------------------------------------------------------------
/**@brief Calcula la posición ecuatorial del sol, la luna y los nueve planetas mayores usando JPL Ephemerides.
*
*	@param [in] Mjd_TDB Fecha juliana modificada.  
*	@return Tupla con las matrices con posición ecuatorial del sol, la luna y los nueve planetas mayores. 
*/
//----------------------------------------------------------------------
tuple<Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&> JPL_Eph_DE430 (double Mjd_TDB);	
#endif