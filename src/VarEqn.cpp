// $Source$
//----------------------------------------------------------------------
// VarEqn
//----------------------------------------------------------------------
// Proyecto TT1
//
/**@file VarEqn.cpp
*	@brief Cálculo de las ecuaciones variacionales.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\VarEqn.hpp"

Matrix& VarEqn (double x, Matrix& yPhi){
	cout << "Entro";
	auto [x_pole,y_pole,UT1_UTC,LOD,dpsi,deps,dx_pole,dy_pole,TAI_UTC] = IERS(*eopdata,AuxParam.Mjd_UTC,'l');
	auto [UT1_TAI,UTC_GPS,UT1_GPS,TT_UTC,GPS_UTC] = timediff(UT1_UTC,TAI_UTC);
	double Mjd_UT1 = AuxParam.Mjd_TT + (UT1_UTC-TT_UTC)/86400;

	// Transformation matrix
	Matrix& P = PrecMatrix(SAT_Const::MJD_J2000,AuxParam.Mjd_TT + x/86400);
	Matrix& N = NutMatrix(AuxParam.Mjd_TT + x/86400);
	Matrix& T = N * P;
	Matrix& E = PoleMatrix(x_pole,y_pole) * GHAMatrix(Mjd_UT1) * T;
	// State vector components
	Matrix& r = transpose(extract_vector(yPhi,1,3));
	Matrix& v = transpose(extract_vector(yPhi,4,6));
	Matrix& Phi = zeros(6,6);
	// State transition matrix
	for(int j=1;j<=6;j++){
		assign_column(j,Phi,extract_vector(yPhi,6*j+1,6*j+6));
	}
	// Acceleration and gradient
	Matrix& a = AccelHarmonic ( r, E, AuxParam.n, AuxParam.m );
	Matrix& G = G_AccelHarmonic ( r, E, AuxParam.n, AuxParam.m );
	// Time derivative of state transition matrix
	Matrix& yPhip = zeros(42,1);
	Matrix& dfdy = zeros(6,6);

	for(int i=1;i<=3;i++){
		for(int j=1;j<=3;j++){
			dfdy(i,j) = 0.0;                 // dv/dr(i,j)
			dfdy(i+3,j) = G(i,j);            // da/dr(i,j)
			if ( i==j ){
				dfdy(i,j+3) = 1;
			}
			else{
				dfdy(i,j+3) = 0;             // dv/dv(i,j)
			}
			dfdy(i+3,j+3) = 0.0;             // da/dv(i,j)
		}
	}
	Matrix& Phip = dfdy*Phi;
	// Derivative of combined state vector and state transition matrix
	for(int i=1;i<=3;i++){
		yPhip(i,1)   = v(i,1);                 // dr/dt(i)
		yPhip(i+3,1) = a(i,1);                 // dv/dt(i)
	}

	for(int i=1;i<=6;i++){
		for(int j=1;j<=6;j++){
			yPhip(6*j+i,1) = Phip(i,j);     // dPhi/dt(i,j)
		}
	}
	cout << "Salgo";
	return yPhip;
  
}
