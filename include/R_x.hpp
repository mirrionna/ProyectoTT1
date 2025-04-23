// $Header$
//----------------------------------------------------------------------
// R_x
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file R_x.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función R_x.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _R_X_
#define _R_X_

#include <cmath>
#include "..\include\matrix.h"
//----------------------------------------------------------------------
//  Matrix& R_x (double angle)
//----------------------------------------------------------------------
/**@brief Calcula la matriz de rotación en el eje X de un ángulo
*
*	@param [in] angle Double con el ángulo, en radianes.  
*	@return Matriz de rotación en el eje x de angle. 
*/
//----------------------------------------------------------------------
Matrix& R_x (double angle);	
#endif