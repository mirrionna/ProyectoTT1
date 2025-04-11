// $Header$
//----------------------------------------------------------------------
// SAT_Const
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file SAT_Const.hpp
*	@brief Este archivo de cabecera contiene una implementación de una clase que contiene diferentes constantes.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _SAT_Const_
#define _SAT_Const_
#include <cmath>

class SAT_Const {
public:
    double pi2,Rad,Deg,Arcs,MJD_J2000,T_B1950,c_light,AU,R_Earth,f_Earth,R_Sun,R_Moon,omega_Earth,GM_Earth,GM_Sun,GM_Moon,GM_Mercury,GM_Venus,GM_Mars,GM_Jupiter,GM_Saturn,GM_Uranus,GM_Neptune,GM_Pluto,P_Sol;

    // Parameterized constructor
	//----------------------------------------------------------------------
	// SAT_Const()
	//----------------------------------------------------------------------
	/**@brief Constructor de la clase SAT_Const.
	*	@return SAT_Const con todas las constantes dentro como atributos.
	*/
	//----------------------------------------------------------------------
    SAT_Const();
};
#endif