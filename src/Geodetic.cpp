// $Source$
//----------------------------------------------------------------------
// Geodetic
//----------------------------------------------------------------------
// Proyecto TT1
//
/**@file Geodetic.cpp
*	@brief Cálculo de las coordenadas geodésicas a partir de un vector de posición.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\Geodetic.hpp"

tuple<double,double,double> Geodetic (Matrix &r){
	double R_equ = SAT_Const::R_Earth;
	double f     = SAT_Const::f_Earth;

	double eps = 1e-10;
	double epsRequ = eps*R_equ;        // Convergence criterion
	double e2      = f*(2.0-f);        // Square of eccentricity

	double X = r(1);                   // Cartesian coordinates
	double Y = r(2);
	double Z = r(3);
	double rho2 = X*X + Y*Y;           // Square of distance from z-axis

	// Check validity of input data
	if (abs(norm(r))<eps){
		cout<<" invalid input in Geodetic constructor\n";
		exit(EXIT_FAILURE);
	}

	// Iteration 
	double dZ = e2*Z;
	double ZdZ,Nh,SinPhi,N,dZ_new;
	while(1){
		ZdZ    =  Z + dZ;
		Nh     =  sqrt ( rho2 + ZdZ*ZdZ ); 
		SinPhi =  ZdZ / Nh;                    // Sine of geodetic latitude
		N      =  R_equ / sqrt(1.0-e2*SinPhi*SinPhi);
		dZ_new =  N*e2*SinPhi;
		if ( abs(dZ-dZ_new) < epsRequ ){
			break;
		}
		dZ = dZ_new;
	}

	// Longitude, latitude, altitude
	double lon = atan2 ( Y, X );
	double lat = atan2 ( ZdZ, sqrt(rho2) );
	double h   = Nh - N;
	
	return std::tie(lon, lat, h);

}