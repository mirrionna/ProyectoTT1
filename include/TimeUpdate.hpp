// $Header$
//----------------------------------------------------------------------
// TimeUpdate
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file TimeUpdate.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función TimeUpdate.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _TimeUpdate_
#define _TimeUpdate_

#include <cmath>
#include "..\include\matrix.h"
//----------------------------------------------------------------------
//  Matrix& TimeUpdate (Matrix& r, Matrix& s, double GM)
//----------------------------------------------------------------------
/**@brief Actualiza el tiempo.
*
*	@param [in] P Matriz.
*	@param [in] Phi Matriz.  
*	@param [in] Qdt Double.  
*	@return Matriz. 
*/
//----------------------------------------------------------------------
Matrix& TimeUpdate (Matrix &P, Matrix &Phi, double Qdt);	
//----------------------------------------------------------------------
//  Matrix& TimeUpdate (Matrix& r, Matrix& s)
//----------------------------------------------------------------------
/**@brief Actualiza el tiempo.
*
*	@param [in] P Matriz.
*	@param [in] Phi Matriz.  
*	@return Matriz. 
*/
//----------------------------------------------------------------------
Matrix& TimeUpdate (Matrix &P, Matrix &Phi);	
#endif