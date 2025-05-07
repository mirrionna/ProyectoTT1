// $Header$
//----------------------------------------------------------------------
// hgibbs
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file hgibbs.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función hgibbs.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _hgibbs_
#define _hgibbs_

#include <cmath>
#include <tuple>
#include <string>
#include "..\include\matrix.h"
#include "..\include\SAT_Const.hpp"
#include "..\include\angl.hpp"
#include "..\include\unit.hpp"
//----------------------------------------------------------------------
//  tuple<Matrix&,double,double,double,string> hgibbs (Matrix &r1,Matrix &r2,Matrix &r3,double Mjd1,double Mjd2,double Mjd3)
//----------------------------------------------------------------------
/**@brief Implementa la aproximación de herrick-gibs para la determinación orbital, y encuentra el vector de velocidad media para 3 vectores de posición.
*
*	@param [in] r1 Vector de posición 1.  
*	@param [in] r2 Vector de posición 2.  
*	@param [in] r3 Vector de posición 3.  
*	@param [in] Mjd1 Fecha juliana del primer avistamiento. 
*	@param [in] Mjd2 Fecha juliana del segundo avistamiento. 
*	@param [in] Mjd3 Fecha juliana del tercer avistamiento. 
*	@return Tupla con el vector de velocidad ijk en m/s, los ángulos entre vectores en radianes y una flag indicando el éxito. 
*/
//----------------------------------------------------------------------
tuple<Matrix&,double,double,double,string> hgibbs (Matrix &r1,Matrix &r2,Matrix &r3,double Mjd1,double Mjd2,double Mjd3);	
#endif