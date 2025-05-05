// $Source$
//----------------------------------------------------------------------
// NutMatrix
//----------------------------------------------------------------------
// Proyecto TT1
//
/**@file NutMatrix.cpp
*	@brief Cálculo de la transformación de la media al ecuador verdadero y equinoccio.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\NutMatrix.hpp"

Matrix& NutMatrix (double Mjd_TT){
	
	// Mean obliquity of the ecliptic
	double eps = MeanObliquity (Mjd_TT);

	// Nutation in longitude and obliquity
	tuple<double, double> A= NutAngles (Mjd_TT);
	double dpsi=get<0>(A);
	double deps=get<1>(A);

	// Transformation from mean to true equator and equinox
	Matrix& NutMat = R_x(-eps-deps)*R_z(-dpsi)*R_x(+eps);
	
	return NutMat;
}
