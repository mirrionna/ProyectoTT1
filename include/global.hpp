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

typedef struct{
	double Mjd_UTC,Mjd_TT;
	int n,m,sun,moon,planets;
} Param;

extern Param AuxParam;
extern Matrix *eopdata;
extern Matrix *Cnm;
extern Matrix *Snm;
extern Matrix *PC;

//----------------------------------------------------------------------
//  void eop19620101(int c);
//----------------------------------------------------------------------
/**@brief Carga el fichero de datos eop19620101.txt en la matriz eopdata.
*
*	@param [in] c Número de datos a cargar
*/
//----------------------------------------------------------------------
void eop19620101(int c);

//----------------------------------------------------------------------
//  void GGM03S();
//----------------------------------------------------------------------
/**@brief Carga el fichero de datos GGM03S.txt en las matrices Cnm y Snm.
*
*/
//----------------------------------------------------------------------
void GGM03S();
//----------------------------------------------------------------------
//  void GGM03S();
//----------------------------------------------------------------------
/**@brief Carga el fichero de datos DE430Coeff.txt en la matriz PC.
*
*/
//----------------------------------------------------------------------
void DE430Coeff();
#endif