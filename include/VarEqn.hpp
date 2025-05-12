// $Header$
//----------------------------------------------------------------------
// VarEqn
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file VarEqn.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función VarEqn.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _VarEqn_
#define _VarEqn_

#include <cmath>
#include "..\include\matrix.h"
#include "..\include\SAT_const.hpp"
#include "..\include\global.hpp"
#include "..\include\IERS.hpp"
#include "..\include\timediff.hpp"
#include "..\include\PrecMatrix.hpp"
#include "..\include\NutMatrix.hpp"
#include "..\include\PoleMatrix.hpp"
#include "..\include\GHAMatrix.hpp"
#include "..\include\AccelHarmonic.hpp"
#include "..\include\G_AccelHarmonic.hpp"

//----------------------------------------------------------------------
//  Matrix& VarEqn (Matrix& r, Matrix& s, double GM)
//----------------------------------------------------------------------
/**@brief Calcula las ecuaciones variacionales.
*
*	@param [in] x Tiempo desde epoch en segundos.  
*	@param [in] yPhi Vector de dimensión 42 con el vector estado (y) y el estado de la matriz de transición (Phi) en el orden de almacenamiento.  
*	@return Derivada de yPhi. 
*/
//----------------------------------------------------------------------
Matrix& VarEqn (double x, Matrix& yPhi);	
#endif