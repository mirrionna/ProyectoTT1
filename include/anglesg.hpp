// $Header$
//----------------------------------------------------------------------
// anglesg
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file anglesg.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función anglesg.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _anglesg_
#define _anglesg_

#include <cmath>
#include <tuple>
#include "..\include\matrix.h"
#include "..\include\global.hpp"
#include "..\include\Geodetic.hpp"
#include "..\include\LTC.hpp"
#include "..\include\IERS.hpp"
#include "..\include\timediff.hpp"
#include "..\include\PrecMatrix.hpp"
#include "..\include\NutMatrix.hpp"
#include "..\include\PoleMatrix.hpp"
//#include "..\include\GHAMatrix.hpp"
#include "..\include\gibbs.hpp"
#include "..\include\hgibbs.hpp"
#include "..\include\elements.hpp"
#include "..\include\angl.hpp"
//----------------------------------------------------------------------
//  tuple<Matrix&,Matrix&> anglesg (double az1,double az2,double az3,double el1,double el2,double el3,double Mjd1,double Mjd2,double Mjd3,Matrix& Rs1,Matrix& Rs2,Matrix& Rs3)
//----------------------------------------------------------------------
/**@brief Soluciona el problema de la determinación orbital usando tres avistamientos ópticos.
*
*	@param [in] az1 Acimut en el primer tiempo en radianes.  
*	@param [in] az2 Acimut en el segundo tiempo en radianes.  
*	@param [in] az3 Acimut en el tercer tiempo en radianes.  
*	@param [in] el1 Elevación en el primer tiempo en radianes.  
*	@param [in] el2 Elevación en el segundo tiempo en radianes.  
*	@param [in] el3 Elevación en el tercer tiempo en radianes. 
*	@param [in] Mjd1 Fecha juliana del primer tiempo.  
*	@param [in] Mjd2 Fecha juliana del segundo tiempo.  
*	@param [in] Mjd3 Fecha juliana del tercer tiempo. 
*	@param [in] Rs1 Posición en metros del primer tiempo.  
*	@param [in] Rs2 Posición en metros del segundo tiempo.  
*	@param [in] Rs3 Posición en metros del tercer tiempo.
*	@return Tupla con el vector de posición en t2 en metros y el vector velocidad en t2 en metros por segundo. 
*/
//----------------------------------------------------------------------
tuple<Matrix&,Matrix&> anglesg (double az1,double az2,double az3,double el1,double el2,double el3,double Mjd1,double Mjd2,double Mjd3,Matrix& Rs1,Matrix& Rs2,Matrix& Rs3);	
#endif