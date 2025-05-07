// $Header$
//----------------------------------------------------------------------
// gibbs
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file gibbs.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función gibbs.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _gibbs_
#define _gibbs_

#include <cmath>
#include <tuple>
#include <string>
#include "..\include\matrix.h"
#include "..\include\SAT_Const.hpp"
#include "..\include\angl.hpp"
#include "..\include\unit.hpp"
//----------------------------------------------------------------------
//  tuple<Matrix&,double,double,double,string> gibbs (Matrix &r1,Matrix &r2,Matrix &r3)
//----------------------------------------------------------------------
/**@brief Calcula el vector de velocidad ijk, los ángulos entre vectores y una flag que indica el éxito a partir de 3 vectores de posición.
*
*	@param [in] r1 Vector de posición 1.  
*	@param [in] r2 Vector de posición 2.  
*	@param [in] r3 Vector de posición 3.  
*	@return Tupla con el vector de velocidad ijk en m/s, los ángulos entre vectores en radianes y una flag indicando el éxito. 
*/
//----------------------------------------------------------------------
tuple<Matrix&,double,double,double,string> gibbs (Matrix &r1,Matrix &r2,Matrix &r3);	
#endif