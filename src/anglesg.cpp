// $Source$
//----------------------------------------------------------------------
// anglesg
//----------------------------------------------------------------------
// Proyecto TT1
//
/**@file anglesg.cpp
*	@brief Solución del problema de la determinación orbital usando tres avistamientos ópticos.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\anglesg.hpp"

//TODO: Raices de un polinomio de grado n
Matrix& roots(Matrix& poly){
	Matrix& A = zeros(1);
	return A;
} 
//TODO Es real una raiz del polinomio
bool isreal(double a){
	return true;
} 

tuple<Matrix&,Matrix&> anglesg (double az1,double az2,double az3,double el1,double el2,double el3,double Mjd1,double Mjd2,double Mjd3,Matrix& Rs1,Matrix& Rs2,Matrix& Rs3){
	//TODO: Necesito GHAMatrix
	return std::tie(zeros(1),zeros(2));
	Matrix L1(3);Matrix L2(3);Matrix L3(3);
	L1(1)=cos(el1)*sin(az1);L1(2)=cos(el1)*cos(az1);L1(3)=sin(el1);
	L2(1)=cos(el2)*sin(az2);L2(2)=cos(el2)*cos(az2);L2(3)=sin(el2);
	L3(1)=cos(el3)*sin(az3);L3(2)=cos(el3)*cos(az3);L2(3)=sin(el3);

	auto [lon1, lat1, h1] = Geodetic(Rs1);
	auto [lon2, lat2, h2] = Geodetic(Rs2);
	auto [lon3, lat3, h3] = Geodetic(Rs3);

	Matrix& M1 = LTC(lon1, lat1);
	Matrix& M2 = LTC(lon2, lat2);
	Matrix& M3 = LTC(lon3, lat3);

	// body-fixed system
	Matrix& Lb1 = transpose(M1)*L1;
	Matrix& Lb2 = transpose(M1)*L2;
	Matrix& Lb3 = transpose(M1)*L3;

	// mean of date system (J2000)
	double Mjd_UTC = Mjd1;
	auto [x_pole,y_pole,UT1_UTC,LOD,dpsi,deps,dx_pole,dy_pole,TAI_UTC] = IERS(*eopdata,Mjd_UTC,'l');
	auto [UT1_TAI,UTC_GPS,UT1_GPS,TT_UTC,GPS_UTC] = timediff(UT1_UTC,TAI_UTC);
	double Mjd_TT = Mjd_UTC + TT_UTC/86400;
	double Mjd_UT1 = Mjd_TT + (UT1_UTC-TT_UTC)/86400;

	Matrix& P = PrecMatrix(SAT_Const::MJD_J2000,Mjd_TT);
	Matrix& N = NutMatrix(Mjd_TT);
	Matrix& T = N * P;
	Matrix& E = PoleMatrix(x_pole,y_pole); //* GHAMatrix(Mjd_UT1) * T;

	Matrix& Lm1 = transpose(E)*Lb1;
	Rs1 = transpose(E)*Rs1;

	Mjd_UTC = Mjd2;
	auto [x_pole2,y_pole2,UT1_UTC2,LOD2,dpsi2,deps2,dx_pole2,dy_pole2,TAI_UTC2] = IERS(*eopdata,Mjd_UTC,'l');
	auto [UT1_TAI2,UTC_GPS2,UT1_GPS2,TT_UTC2,GPS_UTC2] = timediff(UT1_UTC2,TAI_UTC2);
	Mjd_TT = Mjd_UTC + TT_UTC2/86400;
	Mjd_UT1 = Mjd_TT + (UT1_UTC2-TT_UTC2)/86400;

	P = PrecMatrix(SAT_Const::MJD_J2000,Mjd_TT);
	N = NutMatrix(Mjd_TT);
	T = N * P;
	E = PoleMatrix(x_pole2,y_pole2); //* GHAMatrix(Mjd_UT1) * T;

	Matrix& Lm2 = transpose(E)*Lb2;
	Rs2 = transpose(E)*Rs2;

	Mjd_UTC = Mjd3;
	auto [x_pole3,y_pole3,UT1_UTC3,LOD3,dpsi3,deps3,dx_pole3,dy_pole3,TAI_UTC3] = IERS(*eopdata,Mjd_UTC,'l');
	auto [UT1_TAI3,UTC_GPS3,UT1_GPS3,TT_UTC3,GPS_UTC3] = timediff(UT1_UTC3,TAI_UTC3);
	Mjd_TT = Mjd_UTC + TT_UTC3/86400;
	Mjd_UT1 = Mjd_TT + (UT1_UTC3-TT_UTC3)/86400.0;

	P = PrecMatrix(SAT_Const::MJD_J2000,Mjd_TT);
	N = NutMatrix(Mjd_TT);
	T = N * P;
	E = PoleMatrix(x_pole3,y_pole3); //* GHAMatrix(Mjd_UT1) * T;

	Matrix& Lm3 = transpose(E)*Lb3;
	Rs3 = transpose(E)*Rs3;

	// geocentric inertial position
	double tau1 = (Mjd1-Mjd2)*86400;
	double tau3 = (Mjd3-Mjd2)*86400;

	double a1 = tau3/(tau3-tau1);
	double a3 =-tau1/(tau3-tau1);

	double b1 = tau3/(6*(tau3-tau1))*(pow(tau3-tau1,2)-pow(tau3,2));
	double b3 =-tau1/(6*(tau3-tau1))*(pow(tau3-tau1,2)-pow(tau1,2));

	Matrix aux(3,3);Matrix aux2(3,3);
	aux(1,1)=Lm1(1,1);aux(1,2)=Lm2(1,1);aux(1,3)=Lm3(1,1);
	aux(2,1)=Lm1(2,1);aux(2,2)=Lm2(2,1);aux(2,3)=Lm3(2,1);
	aux(3,1)=Lm1(3,1);aux(3,2)=Lm2(3,1);aux(3,3)=Lm3(3,1);
	aux2(1,1)=Rs1(1,1);aux2(1,2)=Rs2(1,1);aux2(1,3)=Rs2(1,1);
	aux2(2,1)=Rs1(2,1);aux2(2,2)=Rs2(2,1);aux2(2,3)=Rs2(2,1);
	aux2(3,1)=Rs1(3,1);aux2(3,2)=Rs2(3,1);aux2(3,3)=Rs2(3,1);
	Matrix& D = inv(aux)*aux2;

	double d1s = D(2,1)*a1-D(2,2)+D(2,3)*a3;
	double d2s = D(2,1)*b1+D(2,3)*b3;

	double Ccye = 2*dot(Lm2,Rs2);

	Matrix poly(9);
	poly(1)=  1.0;  // R2^8... polynomial
	poly(2)=  0.0;
	poly(3)=  -(pow(d1s,2) + d1s*Ccye + pow(norm(Rs2),2));
	poly(4)=  0.0;
	poly(5)=  0.0;
	poly(6)=  -SAT_Const::GM_Earth*(d2s*Ccye + 2*d1s*d2s);
	poly(7)=  0.0;
	poly(8)=  0.0;
	poly(9)=  -pow(SAT_Const::GM_Earth,2)*pow(d2s,2);
	Matrix& rootarr = roots(poly);

	double bigr2= -99999990.0;

	for(int j=1;j<=8;j++){
		if (( rootarr(j) > bigr2 ) && ( isreal(rootarr(j)) )){
			bigr2= rootarr(j);
		}  
	}

	double u = SAT_Const::GM_Earth/(pow(bigr2,3));

	double C1 = a1+b1*u;
	double C2 = -1;
	double C3 = a3+b3*u;

	Matrix auxd(3,1);
	auxd(1,1)=C1;
	auxd(2,1)=C2;
	auxd(3,1)=C3;
	Matrix& menosD = zeros(D.n_row,D.n_column);
	for(int i=1;i<=D.n_row;i++){
		for(int j=1;i<=D.n_column;i++){
			menosD.data[i-1][j-1] = D.data[i-1][j-1];
		}
	}
	Matrix& temp = menosD*auxd;
	double rho1 = temp(1)/(a1+b1*u);
	double rho2 = -temp(2);
	double rho3 = temp(3)/(a3+b3*u);

	double rhoold1 = rho1;
	double rhoold2 = rho2;
	double rhoold3 = rho3;

	rho2 = 99999999.9;
	double ll   = 0;

	Matrix& r1=zeros(1);
	Matrix& r2=zeros(1);
	Matrix& r3=zeros(1);
	Matrix& v2=zeros(3);
	while ((abs(rhoold2-rho2) > 1e-12) && (ll <= 0 )){
		ll = ll + 1;
		rho2 = rhoold2;
		
		r1 = Rs1+Lm1*rho1;
		r2 = Rs2+Lm2*rho2;
		r3 = Rs3+Lm3*rho3;
		
		double magr1 = norm(r1);
		double magr2 = norm(r2);
		double magr3 = norm(r3);

		
		auto [v2, theta,theta1,copa,error] = gibbs(r1,r2,r3);
		
		if ( (error.compare("ok")!=0) && (copa < std::numbers::pi/180) ){ 
			auto [v2,theta,theta1,copa,error] = hgibbs(r1,r2,r3,Mjd1,Mjd2,Mjd3);
		}
		
		auto [p, a, e, i, Omega, omega, M] = elements (union_vector(r2,v2));
		double f1,g1,f3,g3;
		if ( ll <= 8 ){
			u = SAT_Const::GM_Earth/pow(magr2,3);
			double rdot= dot(r2,v2)/magr2;
			double udot= (-3*SAT_Const::GM_Earth*rdot)/pow(magr2,4);
			
			double tausqr= tau1*tau1;
			f1=  1 - 0.5*u*tausqr -(1/6)*udot*tausqr*tau1 - (1/24) * u*u*tausqr*tausqr - (1/30)*u*udot*tausqr*tausqr*tau1;
			g1= tau1 - (1/6)*u*tau1*tausqr - (1/12) * udot*tausqr*tausqr - (1/120)*u*u*tausqr*tausqr*tau1 - (1/120)*u*udot*tausqr*tausqr*tausqr;
			tausqr= tau3*tau3;
			f3=  1 - 0.5*u*tausqr -(1/6)*udot*tausqr*tau3 - (1/24) * u*u*tausqr*tausqr - (1/30)*u*udot*tausqr*tausqr*tau3;
			g3= tau3 - (1/6)*u*tau3*tausqr - (1/12) * udot*tausqr*tausqr - (1/120)*u*u*tausqr*tausqr*tau3 - (1/120)*u*udot*tausqr*tausqr*tausqr;
		}
		else{
			
			theta  = angl( r1,r2 );
			theta1 = angl( r2,r3 );
			
			f1= 1 - ( (magr1*(1 - cos(theta)) / p ) );
			g1= ( magr1*magr2*sin(-theta) ) / sqrt( p );
			f3= 1 - ( (magr3*(1 - cos(theta1)) / p ) );
			g3= ( magr3*magr2*sin(theta1) ) / sqrt( p );
		}
		
		double C1 = g3/(f1*g3-f3*g1);
		double C2 = -1;
		double C3 =-g1/(f1*g3-f3*g1);
		
		double H1 = SAT_Const::GM_Earth*tau3/12;
		double H3 =-SAT_Const::GM_Earth*tau1/12;
		double H2 = H1-H3;
		
		double G1 = -tau3/(tau1*(tau3-tau1));
		double G3 = -tau1/(tau3*(tau3-tau1));
		double G2 = G1-G3;
		
		double D1 = G1+H1/pow(magr1,3);
		double D2 = G2+H2/pow(magr2,3);
		double D3 = G3+H3/pow(magr3,3);
		
		double tempdouble = -D1*C1-D2*C2-D3*C3;
		rhoold1 = tempdouble/(a1+b1*u);
		rhoold2 = -tempdouble;
		rhoold3 = tempdouble/(a3+b3*u);
		
		r1 = Rs1+Lm1*rhoold1;
		r2 = Rs2+Lm2*rhoold2;
		r3 = Rs3+Lm3*rhoold3;
		
	}

	r1 = Rs1+Lm1*rho1;
	r2 = Rs2+Lm2*rho2;
	r3 = Rs3+Lm3*rho3;
	
	return std::tie(r2,v2);
}