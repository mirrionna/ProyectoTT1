// $Header$
//----------------------------------------------------------------------
// R_y
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file R_y.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función R_y.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _R_Y_
#define _R_Y_

#include <cmath>
#include "..\include\matrix.h"
//----------------------------------------------------------------------
//  Matrix& R_y (double angle)
//----------------------------------------------------------------------
/**@brief Calcula la matriz de rotación en el eje y de un ángulo
*
*	@param [in] angle Double con el ángulo, en radianes.  
*	@return Matriz de rotación en el eje y de angle. 
*/
//----------------------------------------------------------------------
Matrix& R_y (double angle);	
#endif