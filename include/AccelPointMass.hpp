// $Header$
//----------------------------------------------------------------------
// AccelPointMass
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file AccelPointMass.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función AccelPointMass.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _AccelPointMass_
#define _AccelPointMass_

#include <cmath>
//----------------------------------------------------------------------
//  Matrix& AccelPointMass (Matrix& r, Matrix& s, double GM)
//----------------------------------------------------------------------
/**@brief Calcula la aceleración perturbacional debido a un punto de masas.
*
*	@param [in] r Vector de posición del satélite.  
*	@param [in] s Vector de posición del punto de masas.  
*	@param [in] GM Coeficiente gravitacional del punto de masas.  
*	@return Matriz con la aceleración pertubacional. 
*/
//----------------------------------------------------------------------
Matrix& AccelPointMass (Matrix &r, Matrix &s, double GM);	
#endif