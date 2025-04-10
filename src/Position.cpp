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

Matrix& Position (double lon, double lat, double h){
	double R_equ = 6.378136300000000e+06;
	double f     = 0.003352810664747;

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