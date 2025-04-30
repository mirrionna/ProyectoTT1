// $Header$
//----------------------------------------------------------------------
// +PrecMatrix
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file PrecMatrix.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función PrecMatrix.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _PrecMatrix_
#define _PrecMatrix_

#include <cmath>
#include "..\include\matrix.h"
#include "..\include\SAT_Const.hpp"
#include "..\include\R_y.hpp"
#include "..\include\R_z.hpp"

//----------------------------------------------------------------------
//  Matrix& PrecMatrix (double Mjd_1, double Mjd_2)
//----------------------------------------------------------------------
/**@brief Transformación de precesión de coordenadas ecuatoriales.
*
*	@param [in] Mjd_1 Época dada (fecha juliana modificada).  
*	@param [in] Mjd_2 Época a la que precesar (fecha juliana modificada).   
*	@return Matriz con la transformación de precesión de coordenadas ecuatoriales. 
*/
//----------------------------------------------------------------------
Matrix& PrecMatrix (double Mjd_1, double Mjd_2);	
#endif