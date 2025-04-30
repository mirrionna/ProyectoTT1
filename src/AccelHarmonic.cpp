// $Source$
//----------------------------------------------------------------------
// AccelHarmonic
//----------------------------------------------------------------------
// Proyecto TT1
//
/**@file AccelHarmonic.cpp
*	@brief Cálculo de la aceleración pertubacional de un satélite debido a un punto de masas.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\AccelHarmonic.hpp"

Matrix& AccelHarmonic (Matrix &r, Matrix &E, int n_max, int m_max){
	
	GGM03S();
	Matrix *mCnm = Cnm;
	Matrix *mSnm = Snm;

	double r_ref = 6378.1363e3;   // Earth's radius [m]; GGM03S
	double gm    = 398600.4415e9; // [m^3/s^2]; GGM03S
	cout<<"A\n";
	// Body-fixed position 
	Matrix &r_bf = E * r;
	cout<<"B\n";
	// Auxiliary quantities
	double d = norm(transpose(r_bf));                     // distance
	double latgc = asin(r_bf(3,1)/d);
	double lon = atan2(r_bf(2,1),r_bf(1,1));
	cout<<"C\n";
	auto [pnm, dpnm] = Legendre(n_max,m_max,latgc);
	cout<<pnm;
	cout<<dpnm;
	cout<<"D\n";
	double dUdr = 0;
	double dUdlatgc = 0;
	double dUdlon = 0;
	double q3 = 0; double q2 = q3; double q1 = q2;
	cout<<"E\n";
	for (int n=0;n<=n_max;n++){
		double b1 = (-gm/pow(d,2))*pow((r_ref/d),n)*(n+1);
		double b2 =  (gm/d)*pow((r_ref/d),n);
		double b3 =  (gm/d)*pow((r_ref/d),n);
		for(int m=0;m<=m_max;m++){
			q1 = q1 + pnm(n+1,m+1)*((*mCnm)(n+1,m+1)*cos(m*lon)+(*mSnm)(n+1,m+1)*sin(m*lon));
			q2 = q2 + dpnm(n+1,m+1)*((*mCnm)(n+1,m+1)*cos(m*lon)+(*mSnm)(n+1,m+1)*sin(m*lon));
			q3 = q3 + m*pnm(n+1,m+1)*((*mSnm)(n+1,m+1)*cos(m*lon)-(*mCnm)(n+1,m+1)*sin(m*lon));
		}
		dUdr     = dUdr     + q1*b1;
		dUdlatgc = dUdlatgc + q2*b2;
		dUdlon   = dUdlon   + q3*b3;
		q3 = 0; q2 = q3; q1 = q2;
	}
	cout<<"F\n";
	// Body-fixed acceleration
	double r2xy = pow(r_bf(1,1),2)+pow(r_bf(2,1),2);

	double ax = (1/d*dUdr-r_bf(3,1)/(pow(d,2)*sqrt(r2xy))*dUdlatgc)*r_bf(1,1)-(1/r2xy*dUdlon)*r_bf(2,1);
	double ay = (1/d*dUdr-r_bf(3,1)/(pow(d,2)*sqrt(r2xy))*dUdlatgc)*r_bf(2,1)+(1/r2xy*dUdlon)*r_bf(1,1);
	double az =  1/d*dUdr*r_bf(3,1)+sqrt(r2xy)/pow(d,2)*dUdlatgc;
	cout<<"G\n";
	Matrix a_bf (3,1);
	a_bf(1,1)=ax;a_bf(2,1)=ay;a_bf(3,1)=az;
	cout<<"H\n";
	// Inertial acceleration 
	Matrix& a = transpose(E)*a_bf;
	
	
	return a;
}