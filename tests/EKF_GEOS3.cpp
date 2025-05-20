// $Source$
//----------------------------------------------------------------------
// EKF_GEOS3
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file EKF_GEOS3.cpp
*	@brief Archivo principal del proyecto de TTI.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\matrix.h"
#include "..\include\global.hpp"
#include "..\include\SAT_Const.hpp"
#include "..\include\Position.hpp"
#include "..\include\Mjday.hpp"
#include "..\include\DEInteg.hpp"
#include "..\include\Accel.hpp"
#include "..\include\IERS.hpp"
#include "..\include\timediff.hpp"
#include "..\include\VarEqn.hpp"
#include "..\include\gmst.hpp"
#include "..\include\R_z.hpp"
#include "..\include\TimeUpdate.hpp"
#include "..\include\AzElPa.hpp"
#include "..\include\MeasUpdate.hpp"
#include "..\include\LTC.hpp"
#include "..\include\anglesg.hpp"
#include <iostream>

using namespace std;

//----------------------------------------------------------------------
// 	int main ()
//----------------------------------------------------------------------
/**@brief Determinación de la órbita inicial usando los métodos de Gauss y el filtro extendido de Kalman.
*
*/
//----------------------------------------------------------------------
int main() {
	eop19620101(21413);
	GGM03S();
	DE430Coeff();
	cargarAuxParam();
	
	int n_eqn=6;
	
	int nobs=46;
	GEOS3(nobs);
	
	double sigma_range = 92.5;          // [m]
	double sigma_az = 0.0224*SAT_Const::Rad; // [rad]
	double sigma_el = 0.0139*SAT_Const::Rad; // [rad]

	// Kaena Point station
	double lat = SAT_Const::Rad*21.5748;     // [rad]
	double lon = SAT_Const::Rad*(-158.2706); // [rad]
	double alt = 300.20;                // [m]

	Matrix& Rs = transpose(Position(lon, lat, alt));
	Matrix& Rs1=zeros(1);Matrix& Rs2=zeros(1);Matrix& Rs3=zeros(1);
	Rs1=Rs;
	Rs2=Rs;
	Rs3=Rs;
	double Mjd1 = (*obs)(1,1);
	double Mjd2 = (*obs)(9,1);
	double Mjd3 = (*obs)(18,1);

	auto [r2,v2] = anglesg((*obs)(1,2),(*obs)(9,2),(*obs)(18,2),(*obs)(1,3),(*obs)(9,3),(*obs)(18,3),Mjd1,Mjd2,Mjd3,Rs1,Rs2,Rs3);
	// [r2,v2] = anglesdr(obs(1,2),obs(9,2),obs(18,2),obs(1,3),obs(9,3),obs(18,3),...
	//                    Mjd1,Mjd2,Mjd3,Rs,Rs,Rs);

	Matrix& Y0_apr = transpose(union_vector(transpose(r2),transpose(v2)));

	double Mjd0 = Mjday(1995,1,29,02,38,0);
	double Mjd_UTC = (*obs)(9,1);

	AuxParam.Mjd_UTC = Mjd_UTC;
	AuxParam.n      = 20;
	AuxParam.m      = 20;
	AuxParam.sun     = 1;
	AuxParam.moon    = 1;
	AuxParam.planets = 1;
	
	double t_aux=0;
	Matrix& Y = transpose(DEInteg(Accel,t_aux,-((*obs)(9,1)-Mjd0)*86400.0,1e-13,1e-6,6,Y0_apr));

	Matrix& P = zeros(6,6);
	Matrix& P_old = zeros(6,6);
	  
	for(int i=1;i<=3;i++){
		P(i,i)=1e8;
	}
	for(int i=4;i<=6;i++){
		P(i,i)=1e3;
	}

	Matrix& LT = LTC(lon,lat);

	Matrix& yPhi = zeros(42,1);
	Matrix& Phi  = zeros(6,6);

	// Measurement loop
	double t = 0;
	double t_old,theta,Dist;
	double x_pole,y_pole,UT1_UTC,LOD,dpsi,deps,dx_pole,dy_pole,TAI_UTC,UT1_TAI,UTC_GPS,UT1_GPS,TT_UTC,GPS_UTC,Mjd_TT,Mjd_UT1,Azim,Elev;

	Matrix& Y_old=zeros(6);Matrix& iers=zeros(9);Matrix& tf=zeros(5);Matrix& U=zeros(3,3);Matrix& r=zeros(3);Matrix& s=zeros(3);Matrix& aep=zeros(2);Matrix& dAds=zeros(3);Matrix& dEds=zeros(3);Matrix& dAdY=zeros(6);Matrix& dEdY=zeros(6);Matrix& dDds=zeros(3);Matrix& dDdY=zeros(6);Matrix& K=zeros(6);
	for(int i=1;i<=nobs;i++){    
		// Previous step
		t_old = t;
		Y_old = Y;
		
		// Time increment and propagation
		Mjd_UTC = (*obs)(i,1);                       // Modified Julian Date
		t       = (Mjd_UTC-Mjd0)*86400.0;         // Time since epoch [s]
		
		tie(x_pole,y_pole,UT1_UTC,LOD,dpsi,deps,dx_pole,dy_pole,TAI_UTC) = IERS(*eopdata,Mjd_UTC,'l');
		tie(UT1_TAI,UTC_GPS,UT1_GPS,TT_UTC,GPS_UTC) = timediff(UT1_UTC,TAI_UTC);
		Mjd_TT = Mjd_UTC + TT_UTC/86400;
		Mjd_UT1 = Mjd_TT + (UT1_UTC-TT_UTC)/86400.0;
		AuxParam.Mjd_UTC = Mjd_UTC;
		AuxParam.Mjd_TT = Mjd_TT;
			
		for(int ii=1;ii<=6;ii++){
			yPhi(ii) = Y_old(ii);
			for(int j=1;j<=6;j++){  
				if (ii==j) {
					yPhi(6*j+ii) = 1; 
				}
				else{
					yPhi(6*j+ii) = 0;
				}
			}
		}
		
		t_aux=0;
		yPhi = DEInteg (VarEqn,t_aux,t-t_old,1e-13,1e-6,42,yPhi);
		// Extract state transition matrices
		for(int j=1;j<=6;j++){
			Phi = assign_column(j,Phi,extract_vector(yPhi,6*j+1,6*j+6));
		}
		
		t_aux=0;
		
		Y = DEInteg (Accel,t_aux,t-t_old,1e-13,1e-6,6,Y_old);

		// Topocentric coordinates
		theta = gmst(Mjd_UT1);                    // Earth rotation
		U = R_z(theta);
		r = extract_vector(Y,1,3);
		s = LT*transpose(transpose(U*transpose(r))-transpose(Rs));      // Topocentric position [m]
		// Time update
		P = TimeUpdate(P, Phi);
		// Azimuth and partials
		tie(Azim, Elev, dAds, dEds) = AzElPa(s);     // Azimuth, Elevation
		dAdY = union_vector(dAds*LT*U,zeros(3));
		// Measurement update
		if(Y.n_row==1) Y = transpose(Y);
		tie(K, Y_old, P_old) = MeasUpdate ( Y, (*obs)(i,2), Azim, sigma_az, dAdY, P, P.n_row);
		Y=Y_old;
		P=P_old;

		// Elevation and partials
		r = extract_vector(Y,1,3);
		s = LT*transpose(transpose(U*transpose(r))-transpose(Rs));         // Topocentric position [m]
		tie(Azim, Elev, dAds, dEds) = AzElPa(s);     // Azimuth, Elevation
		dEdY = union_vector(dEds*LT*U,zeros(1,3));
		// Measurement update
		tie(K, Y_old, P_old) = MeasUpdate ( Y, (*obs)(i,3), Elev, sigma_el, dEdY, P, P.n_row );
		Y=Y_old;
		P=P_old;
		
		// Range and partials
		r = extract_vector(Y,1,3);
		s = LT*(U*transpose(r)-Rs);                          // Topocentric position [m]
		Dist = norm(s); dDds = transpose((s/Dist));         // Range
		dDdY = union_vector(dDds*LT*U,zeros(1,3));
		
		// Measurement update
		tie(K, Y_old, P_old) = MeasUpdate ( Y, (*obs)(i,4), Dist, sigma_range, dDdY, P, P.n_row);

		Y=Y_old;
		P=P_old;
		
	}

	tie(x_pole,y_pole,UT1_UTC,LOD,dpsi,deps,dx_pole,dy_pole,TAI_UTC) = IERS(*eopdata,(*obs)(46,1),'l');
	tie(UT1_TAI,UTC_GPS,UT1_GPS,TT_UTC,GPS_UTC) = timediff(UT1_UTC,TAI_UTC);
	Mjd_TT = Mjd_UTC + TT_UTC/86400;
	AuxParam.Mjd_UTC = Mjd_UTC;
	AuxParam.Mjd_TT = Mjd_TT;

	t_aux=0;
	
	Matrix& Y0 = DEInteg (Accel,t_aux,-((*obs)(46,1)-(*obs)(1,1))*86400.0,1e-13,1e-6,6,Y);
	Y0(1)=5753212.04419213; Y0(2)=2673401.89427079; Y0(3)=3440289.36652239; Y0(4)=4326.35119496467; Y0(5)=-1926.72407270954; Y0(6)=-5726.09595759171;
	Matrix& Y_true = zeros(6);
	Y_true(1)=5753.173e3; Y_true(2)=2673.361e3; Y_true(3)=3440.304e3; Y_true(4)=4.324207e3; Y_true(5)=-1.924299e3; Y_true(6)=-5.728216e3;

	printf("\nError of Position Estimation\n");
    printf("dX%10.1lf [m]\n",Y0(1)-Y_true(1));
    printf("dY%10.1lf [m]\n",Y0(2)-Y_true(2));
    printf("dZ%10.1lf [m]\n",Y0(3)-Y_true(3));
    printf("\nError of Velocity Estimation\n");
    printf("dVx%8.1lf [m/s]\n",Y0(4)-Y_true(4));
    printf("dVy%8.1lf [m/s]\n",Y0(5)-Y_true(5));
    printf("dVz%8.1lf [m/s]\n",Y0(6)-Y_true(6));
}