// $Source$
//----------------------------------------------------------------------
// gast
//----------------------------------------------------------------------
// Proyecto TT1
//
/**@file gast.cpp
*	@brief Cálculo del tiempo sidéreo aparente Greenwich.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\gast.hpp"

//----------------------------------------------------------------------
//  double modgast(double a,double b)
//----------------------------------------------------------------------
/**@brief Función auxiliar para adaptar la funcion fmod a la correspondiente en Matlab.
*
*	@param [in] a Dividendo.
*	@param [in] b Divisor.
*	@return Devuelve el resto de dividir a/b, entre 0 y b.
*/
//----------------------------------------------------------------------
double modgast(double a,double b){
	double r=fmod(a,b);
	if(r<0){
		r+=b;
	}
	return r;
}

double gast (double Mjd_UT1){
	double gstime = modgast( gmst(Mjd_UT1) + EqnEquinox(Mjd_UT1), SAT_Const::pi2 );
	
	return gstime;
}