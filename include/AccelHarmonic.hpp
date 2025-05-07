// $Header$
//----------------------------------------------------------------------
// AccelHarmonic
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file AccelHarmonic.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función AccelHarmonic.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _AccelHarmonic_
#define _AccelHarmonic_

#include <cmath>
#include <tuple>
#include "..\include\matrix.h"
#include "..\include\global.hpp"
#include "..\include\Legendre.hpp"
//----------------------------------------------------------------------
//  Matrix& AccelHarmonic (Matrix &r, Matrix &E, int n_max, int m_max)
//----------------------------------------------------------------------
/**@brief Calcula aceleración debido al campo gravitatorio del centro de masas.
*
*	@param [in] r Vector de posición del satélite en un sistema inerte.  
*	@param [in] E Vector de posición del punto de masas.  
*	@param [in] n_max Grado máximo.  
*	@param [in] m_max Máximo orden (n_max<=m_max, n_max=0 para zonales).
*	@return Double con la aceleración debido al campo gravitatorio del centro de masas. 
*/
//----------------------------------------------------------------------
Matrix& AccelHarmonic (Matrix &r, Matrix &E, int n_max, int m_max);	
#endif