// $Source$
//----------------------------------------------------------------------
// Position
//----------------------------------------------------------------------
// Proyecto TT1
//
/**@file Position.cpp
*	@brief Cálculo del vector posición a partir de las coordenadas geodésicas.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\matrix.h"
#include "..\include\Position.hpp"
#include "..\include\SAT_Const.hpp"

Matrix& Position (double lon, double lat, double h){
	
	SAT_Const *s_const = new SAT_Const();
	
	double R_equ = s_const->R_Earth;
	double f     = s_const->f_Earth;

	double e2     = f*(2.0-f);   // Square of eccentricity
	double CosLat = cos(lat);    // (Co)sine of geodetic latitude
	double SinLat = sin(lat);

	// Position vector 
	double N = R_equ / sqrt(1.0-e2*SinLat*SinLat);
	Matrix& r = zeros(3);
	r(1) =  (N+h)*CosLat*cos(lon);
	r(2) =  (N+h)*CosLat*sin(lon);
	r(3) =  ((1.0-e2)*N+h)*SinLat;
	
	return r;
}