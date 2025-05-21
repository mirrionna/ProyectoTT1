// $Header$
//----------------------------------------------------------------------
// DEInteg
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file DEInteg.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función DEInteg.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _DEInteg_
#define _DEInteg_

#include <cmath>
#include "..\include\matrix.h"
#include "..\include\sign_.hpp"
#include "..\include\SAT_Const.hpp"
//----------------------------------------------------------------------
//  Matrix& DEInteg (Matrix & func(double t, Matrix& y), double t, double tout, double relerr, double abserr, int n_eqn, Matrix& y)
//----------------------------------------------------------------------
/**@brief Método de integración numérica para EDOs.
*
*	@param [in] func Función sobre la que se va a integrar
*	@param [in] t Double. 
*	@param [in] tout Double. 
*	@param [in] relerr Double. 
*	@param [in] abserr Double. 
*	@param [in] n_eqn Número de ecuaciones.
*	@param [in] y Matriz. 
*	@return Matriz. 
*/
//----------------------------------------------------------------------
Matrix& DEInteg (Matrix & func(double t, Matrix& y), double t, double tout, double relerr, double abserr, int n_eqn, Matrix& y);	
#endif