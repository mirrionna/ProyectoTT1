// $Header$
//----------------------------------------------------------------------
// NutMatrix
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file NutMatrix.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función NutMatrix.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _NutMatrix_
#define _NutMatrix_

#include <cmath>
#include "..\include\matrix.h"
#include "..\include\MeanObliquity.hpp"
#include "..\include\NutAngles.hpp"
#include "..\include\R_x.hpp"
#include "..\include\R_z.hpp"

//----------------------------------------------------------------------
//  Matrix& NutMatrix (Matrix& r, Matrix& s, double GM)
//----------------------------------------------------------------------
/**@brief Transforma de la media al ecuador verdadero y equinoccio.
*
*	@param [in] Mjd_TT Tiempo juliano modificado (en tiempo terrestre).  
*	@return Matriz con la transformación de la media al ecuador verdadero y equinoccio. 
*/
//----------------------------------------------------------------------
Matrix& NutMatrix (double Mjd_TT);	
#endif