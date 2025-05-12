// $Header$
//----------------------------------------------------------------------
// GHAMatrix
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file GHAMatrix.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función GHAMatrix.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _GHAMatrix_
#define _GHAMatrix_

#include <cmath>
#include "..\include\matrix.h"
#include "..\include\R_z.hpp"
#include "..\include\gast.hpp"
//----------------------------------------------------------------------
//  Matrix& GHAMatrix (double Mjd_UT1)
//----------------------------------------------------------------------
/**@brief Calcula la matriz de transofmración del ecuador y equinoccio real al ecuador de la Tierra y el sistema del meridiano de Greenwich.
*
*	@param [in] Mjd_UT1 Fecha juliana modificada.   
*	@return Matriz Greenwich Hour Angle. 
*/
//----------------------------------------------------------------------
Matrix& GHAMatrix (double Mjd_UT1);	
#endif