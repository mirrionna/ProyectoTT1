// $Header$
//----------------------------------------------------------------------
// G_AccelHarmonic
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file G_AccelHarmonic.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función G_AccelHarmonic.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _G_AccelHarmonic_
#define _G_AccelHarmonic_

#include <cmath>
#include <tuple>
#include "..\include\matrix.h"
#include "..\include\AccelHarmonic.hpp"
//----------------------------------------------------------------------
//  Matrix& G_AccelHarmonic (Matrix &r, Matrix &U, int n_max, int m_max)
//----------------------------------------------------------------------
/**@brief Calcula el gradiente del campo gravitacional armónico de la Tierra.
*
*	@param [in] r Vector de posición del satélite en un sistema inerte.  
*	@param [in] U Matriz de transformación a un sistema fijo.  
*	@param [in] n_max Grado máximo.  
*	@param [in] m_max Máximo orden.
*	@return Vector gradiente. 
*/
//----------------------------------------------------------------------
Matrix& G_AccelHarmonic (Matrix &r, Matrix &U, int n_max, int m_max);	
#endif