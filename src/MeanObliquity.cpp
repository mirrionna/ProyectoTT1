// $Source$
//----------------------------------------------------------------------
// MeanObliquity
//----------------------------------------------------------------------
// Proyecto TT1
//
/**@file MeanObliquity.cpp
*	@brief Cálculo de la oblicuidad media de la eclíptica, en radianes.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\MeanObliquity.hpp"

double MeanObliquity(double Mjd_TT){
	double Rad = 0.017453292519943;
	double MJD_J2000 = 5.154450000000000e+04;
	
	double T = (Mjd_TT-MJD_J2000)/36525;

	double MOblq = Rad *( 84381.448/3600-(46.8150+(0.00059-0.001813*T)*T)*T/3600 );
	
	return MOblq;
}
