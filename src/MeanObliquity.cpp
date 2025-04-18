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
#include "..\include\SAT_Const.hpp"


double MeanObliquity(double Mjd_TT){
	SAT_Const *s_const = new SAT_Const();
	
	double T = (Mjd_TT-s_const->MJD_J2000)/36525;

	double MOblq = s_const->Rad *( 84381.448/3600-(46.8150+(0.00059-0.001813*T)*T)*T/3600 );
	
	return MOblq;
}
