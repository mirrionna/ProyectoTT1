// $Header$
//----------------------------------------------------------------------
// global
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file global.hpp
*	@brief Este archivo de cabecera contiene una implementación para leer ficheros.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _global_
#define _global_

#include <cmath>
#include "..\include\matrix.h"

extern Matrix* eopdata;

//----------------------------------------------------------------------
//  void eop19620101(int c);
//----------------------------------------------------------------------
/**@brief Carga un fichero de datos.
*
*	@param [in] c Número de datos a cargar
*/
//----------------------------------------------------------------------
void eop19620101(int c);

extern Matrix* Cnm;
extern Matrix* Snm;

//----------------------------------------------------------------------
//  void GGM03S();
//----------------------------------------------------------------------
/**@brief Carga un fichero de datos.
*
*/
//----------------------------------------------------------------------
void GGM03S();
#endif