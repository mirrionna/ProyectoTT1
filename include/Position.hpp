// $Header$
//----------------------------------------------------------------------
// Position
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file Position.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función Position.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _Position_
#define _Position_

#include <cmath>
//----------------------------------------------------------------------
//  Matrix& Position (Matrix& r, Matrix& s, double GM)
//----------------------------------------------------------------------
/**@brief Calcula el vector posición a partir de las coordenadas geodésicas.
*
*	@param [in] lon Longitud en radianes.  
*	@param [in] lat Latitud en radianes.  
*	@param [in] h Altura en metros.  
*	@return Vector posición en metros. 
*/
//----------------------------------------------------------------------
Matrix& Position (double lon, double lat, double h);	
#endif