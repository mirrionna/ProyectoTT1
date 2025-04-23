// $Header$
//----------------------------------------------------------------------
// R_z
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file R_z.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función R_z.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _R_Z_
#define _R_Z_

#include <cmath>
#include "..\include\matrix.h"
//----------------------------------------------------------------------
//  Matrix& R_z (double angle)
//----------------------------------------------------------------------
/**@brief Calcula la matriz de rotación en el eje Z de un ángulo
*
*	@param [in] angle Double con el ángulo, en radianes.  
*	@return Matriz de rotación en el eje z de angle. 
*/
//----------------------------------------------------------------------
Matrix& R_z (double angle);	
#endif