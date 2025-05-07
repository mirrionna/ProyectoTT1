// $Header$
//----------------------------------------------------------------------
// unit
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file unit.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función unit.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _unit_
#define _unit_

#include <cmath>
#include "..\include\matrix.h"
//----------------------------------------------------------------------
//  Matrix& unit (Matrix &vec)
//----------------------------------------------------------------------
/**@brief Calcula vector unitario de un vector dado.
*
*	@param [in] vec1 Vector que se quiere normalizar.   
*	@return vec normalizado como vector unitario, o vector con ceros si el vector original era lleno de ceros. 
*/
//----------------------------------------------------------------------
Matrix& unit (Matrix &vec);
#endif