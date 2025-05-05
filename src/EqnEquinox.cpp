// $Source$
//----------------------------------------------------------------------
// EqnEquinox
//----------------------------------------------------------------------
// Proyecto TT1
//
/**@file EqnEquinox.cpp
*	@brief Cálculo de la ecuación de los equinoccios.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\EqnEquinox.hpp"

double EqnEquinox (double Mjd_TT){
	// Nutation in longitude and obliquity
	auto [dpsi, deps] = NutAngles (Mjd_TT);

	// Equation of the equinoxes
	double EqE = dpsi * cos ( MeanObliquity(Mjd_TT) );
	
	return EqE;
}
