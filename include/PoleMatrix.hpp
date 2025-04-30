// $Header$
//----------------------------------------------------------------------
// PoleMatrix
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file PoleMatrix.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función PoleMatrix.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _PoleMatrix_
#define _PoleMatrix_

#include <cmath>
#include "..\include\matrix.h"
#include "..\include\R_x.hpp"
#include "..\include\R_y.hpp"

//----------------------------------------------------------------------
//  Matrix& PoleMatrix (double xp, double yp)
//----------------------------------------------------------------------
/**@brief Transforma de seudo Earth-fixed a Earth-fixed coordenadas.
*
*	@param [in] xp Coordenadas x.  
*	@param [in] yp Coordenadas y.  
*	@return Matriz con la transformación de seudo Earth-fixed a Earth-fixed coordenadas. 
*/
//----------------------------------------------------------------------
Matrix& PoleMatrix (double xp, double yp);	
#endif