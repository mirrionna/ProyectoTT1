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
#include <cstring>
#include "..\include\matrix.h"
#include "..\include\SAT_Const.hpp"
#include "..\include\Mjday.hpp"

typedef struct{
	double Mjd_UTC,Mjd_TT;
	int n,m,sun,moon,planets;
} Param;

/** @brief Struct de tipo Param para contener ciertos valores globales a todo el proyecto. */
extern Param AuxParam;
/** @brief Matriz global para contener el contenido del archivo eop19620101. */
extern Matrix *eopdata;
/** @brief Matriz global para contener el contenido del archivo GGM03S. */
extern Matrix *Cnm;
/** @brief Matriz global para contener el contenido del archivo GGM03S. */
extern Matrix *Snm;
/** @brief Matriz global para contener el contenido del archivo DE430Coeff. */
extern Matrix *PC;
/** @brief Matriz global para contener el contenido del archivo GEOS3. */
extern Matrix *obs;

//----------------------------------------------------------------------
//  void eop19620101(int c);
//----------------------------------------------------------------------
/**@brief Carga el fichero de datos eop19620101.txt en la matriz eopdata.
*
*	@param [in] c Número de datos a cargar.
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
/**@brief Carga los datos del struct AuxParam de tipo Param.
*
*/
//----------------------------------------------------------------------
void cargarAuxParam();
/**@brief Carga el fichero de datos GEOS3.txt en la matriz obs.
*
*	@param [in] nobs Número de filas a cargar.
*/
//----------------------------------------------------------------------
void GEOS3(int nobs);
#endif