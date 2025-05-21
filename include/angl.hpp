// $Header$
//----------------------------------------------------------------------
// angl
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file angl.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función angl.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _angl_
#define _angl_

#include <cmath>
#include "..\include\matrix.h"
//----------------------------------------------------------------------
//  double angl (Matrix &vec1, Matrix &vec2)
//----------------------------------------------------------------------
/**@brief Calcula el ángulo entre dos vectores, entre -pi y pi.
*
*	@param [in] vec1 Primer vector.  
*	@param [in] vec2 Segundo vector.  
*	@return Ángulo en el intervalo [-π,π] entre el vec1 y vec2. 
*/
//----------------------------------------------------------------------
double angl (Matrix &vec1, Matrix &vec2);
#endif