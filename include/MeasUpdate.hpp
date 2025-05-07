// $Header$
//----------------------------------------------------------------------
// MeasUpdate
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file MeasUpdate.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función MeasUpdate.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _MeasUpdate_
#define _MeasUpdate_

#include <cmath>
#include <tuple>
#include "..\include\matrix.h"
//----------------------------------------------------------------------
//  tuple<Matrix&,Matrix&,Matrix&> MeasUpdate (Matrix &x, double z, double g, double s, Matrix &G, Matrix &P, int n)
//----------------------------------------------------------------------
/**@brief Calcula aceleración debido al campo gravitatorio del centro de masas.
*
*	@param [in] x Matriz.  
*	@param [in] z Double.  
*	@param [in] g Double.  
*	@param [in] s Double.  
*	@param [in] G Matriz.  
*	@param [in] P Matriz.  
*	@param [in] n Entero.  
*	@return Tupla con tres matrices. 
*/
//----------------------------------------------------------------------
tuple<Matrix&,Matrix&,Matrix&> MeasUpdate (Matrix &x, double z, double g, double s, Matrix &G, Matrix &P, int n);	
#endif