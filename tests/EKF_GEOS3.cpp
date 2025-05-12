// $Source$
//------------------------------------------------------------------------------
// Main
//------------------------------------------------------------------------------
// Initial orbit determination (Extended Kalman Filter)
//
// Under License © 2020.
//
// Created: 2025/03/28
//
/** @file main.cpp
 *  @brief Main program operations.
 *
 *  @author Miguel Alonso Angulo.
 *  @bug No known bugs.
 */
//------------------------------------------------------------------------------

#include "..\include\global.hpp"
#include "..\include\matrix.h"
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
#include "..\include\SAT_Const.hpp"
#include <iostream>

using namespace std;

int main() {
	// Files
    eop19620101(21413);
    GGM03S();
	DE430Coeff();
    GEOS3(46);
cout << (*obs);
    double sigma_range = 92.5;      // [m]
    double sigma_az = 0.0224*(SAT_Const::Rad); // [rad]
    double sigma_el = 0.0139*(SAT_Const::Rad); // [rad]

    // Kaena Point station
    double lat = (SAT_Const::Rad)*21.5748;     // [rad]
    double lon = (SAT_Const::Rad)*(-158.2706); // [rad]
    double alt = 300.20;            // [m]

    Matrix &Rs = Position(lon, lat, alt), &Rs1 = zeros(3), &Rs2 = zeros(3), &Rs3 = zeros(3);
    Rs1 = Rs; Rs2 = Rs; Rs3 = Rs;

    double Mjd1 = (*obs)(1,1);
    double Mjd2 = (*obs)(9,1);
    double Mjd3 = (*obs)(18,1);
cout << "1" << endl;
	Matrix &r2 = zeros(1,3), &v2 = zeros(1,3);
	r2(1,1) = 6221397.62857869; r2(1,2) =  2867713.77965738; r2(1,3) =  3006155.98509949;
	v2(1,1) = 4645.04725161806; v2(1,2) = -2752.21591588204; v2(1,3) = -7507.99940987031;
    // auto [r2,v2] = anglesdr((*obs)(1,2),(*obs)(9,2),(*obs)(18,2),(*obs)(1,3),(*obs)(9,3),(*obs)(18,3),Mjd1,Mjd2,Mjd3,Rs,Rs,Rs);

    Matrix& Y0_apr = union_vector(r2,v2);
    double Mjd0 = Mjday(1995,1,29,02,38,0);

    double Mjd_UTC = (*obs)(9,1);
cout << "2" << endl;
    AuxParam.Mjd_UTC = Mjd_UTC;
    AuxParam.n = 20;
    AuxParam.m = 20;
    AuxParam.sun = 1;
    AuxParam.moon = 1;
    AuxParam.planets = 1;
cout << "3" << endl;
    int iflag1 = 1, *iwork1 = new int[5], iflag2 = 1, *iwork2 = new int[5], iflag3 = 1, *iwork3 = new int[5], iflag4 = 1, *iwork4 = new int[5];
	double t_aux = 0.0, *work1 = new double[100+21*6], *work2 = new double[100+21*42], *work3 = new double[100+21*6], *work4 = new double[100+21*6];
// cout << t_aux << -((*obs)(9,1)-Mjd0)*86400.0 << 1e-13 << 1e-6 << 6 << Y0_apr << iflag;
    DEInteg(Accel,t_aux,-((*obs)(9,1)-Mjd0)*86400.0,1e-13,1e-6,6,Y0_apr, iflag1, work1, iwork1);
    Matrix &Y = Y0_apr;
	cout << Y;
    Matrix &P = zeros(6,6), &P_old = zeros(6,6);
    
    for (int i=1; i<=3; i++) {
        P(i,i)=1e8;
    }
    for (int i=4; i<=6; i++) {
        P(i,i)=1e3;
    }
cout << "4" << endl;
    Matrix &LT = LTC(lon,lat);

    Matrix &yPhi = zeros(1, 42);
    Matrix &Phi  = zeros(6, 6);

    // Measurement loop
    double t = 0.0, t_old, theta, Dist;
    double x_pole, y_pole, UT1_UTC, LOD, dpsi, deps, dx_pole, dy_pole, TAI_UTC;
    double UT1_TAI, UTC_GPS, UT1_GPS, TT_UTC, GPS_UTC, Mjd_TT, Mjd_UT1, Azim, Elev;

    Matrix &Y_old = zeros(6), &iers = zeros(9), &tf = zeros(5), &U = zeros(3, 3), &r = zeros(3), &s = zeros(3);
    Matrix &aep = zeros(2), &dAds = zeros(3), &dEds = zeros(3), &dAdY = zeros(6);
    Matrix &dEdY = zeros(6), &dDds = zeros(3), &dDdY = zeros(6), &K = zeros(6);
	cout << "1" << endl;
    for (int i=1; i<=(*obs).n_row; i++) {    
        // Previous step
        t_old = t;
        Y_old = Y;
        
        // Time increment and propagation
        Mjd_UTC = (*obs)(i,1);                       // Modified Julian Date
        t       = (Mjd_UTC-Mjd0)*86400.0;         // Time since epoch [s]
        
        tie(x_pole,y_pole,UT1_UTC,LOD,dpsi,deps,dx_pole,dy_pole,TAI_UTC) = IERS(*eopdata,Mjd_UTC,'l');
        tie(UT1_TAI,UTC_GPS,UT1_GPS,TT_UTC,GPS_UTC) = timediff(3,TAI_UTC);
        cout << "2" << endl;
        Mjd_TT = Mjd_UTC + TT_UTC/86400. ;
        Mjd_UT1 = Mjd_TT + (UT1_UTC-TT_UTC)/86400.0;
        AuxParam.Mjd_UTC = Mjd_UTC;
        AuxParam.Mjd_TT = Mjd_TT;
            
        for (int ii=1; ii<=6; ii++) {
            yPhi(1, ii) = Y_old(1, ii);
            for (int j=1; j<=6; j++) {
                if (ii==j) {
                    yPhi(1, 6*j+ii) = 1; 
                }
                else {
                    yPhi(1, 6*j+ii) = 0;
                }
            }
        }
        cout << "3" << endl;
		// cout << t_aux << " " << t << " " << t_old << " " << yPhi << " " << iflag;
		t_aux = 0.0;
        DEInteg (VarEqn,t_aux,t-t_old,1e-13,1e-6,42,yPhi, iflag2, work2, iwork2);
		cout << "4" << endl;
        // cout << yPhi;
        // Extract state transition matrices
        for (int j=1; j<=6; j++) {
            Phi = assign_column(j, Phi, transpose(extract_vector(yPhi,6*j+1,6*j+6)));
        }
		t_aux = 0.0;
        DEInteg (Accel,t_aux,t-t_old,1e-13,1e-6,6,Y_old, iflag3, work3, iwork3);
        Y = Y_old;
        // cout << Y;
        // Topocentric coordinates
        theta = gmst(Mjd_UT1);                    // Earth rotation
        U = R_z(theta);
        r = extract_vector(Y,1,3);
        s = LT*transpose(transpose(U*transpose(r))-Rs);                          // Topocentric position [m]
        cout << "5" << endl;
        // Time update
        P = TimeUpdate(P, Phi, 0.0);
        // cout << s << P;
        // Azimuth and partials
        tie(Azim, Elev, dAds, dEds) = AzElPa(transpose(s));     // Azimuth, Elevation
        dAdY = union_vector(dAds*LT*U,zeros(3));
        // cout << Azim << " " << Elev << dAds << dEds;
        // Measurement update
        tie(K, Y_old, P_old) = MeasUpdate ( Y, (*obs)(i,2), Azim, sigma_az, dAdY, P, P.n_row);
		Y = Y_old; P = P_old;
		// cout << K;
        cout << "6" << endl;
        // Elevation and partials
        r = extract_vector(Y,1,3);
		// cout << r;
        s = LT*transpose(transpose(U*transpose(r))-Rs);                          // Topocentric position [m]
		// cout << s;
        tie(Azim, Elev, dAds, dEds) = AzElPa(transpose(s));     // Azimuth, Elevation
        dEdY = union_vector(dEds*LT*U,zeros(3));
        // cout << Azim << " " << Elev << dAds << dEds;
        // Measurement update
        tie(K, Y_old, P_old) = MeasUpdate ( Y, (*obs)(i,3), Elev, sigma_el, dEdY, P, P.n_row);
		Y = Y_old; P = P_old;
		// cout << K;
        cout << "7" << endl;
        // Range and partials
        r = extract_vector(Y,1,3);
        s = LT*transpose(transpose(U*transpose(r))-Rs);                          // Topocentric position [m]
        Dist = norm(transpose(s)); dDds = (transpose(s)/Dist);         // Range
        dDdY = union_vector(dDds*LT*U,zeros(3));
        // cout << dDdY;
        // Measurement update
        tie(K, Y_old, P_old) = MeasUpdate ( Y, (*obs)(i,4), Dist, sigma_range, dDdY, P, P.n_row);
		Y = Y_old; P = P_old;
		// cout << K;
		cout << "8" << endl;
    }

    tie(x_pole,y_pole,UT1_UTC,LOD,dpsi,deps,dx_pole,dy_pole,TAI_UTC) = IERS(*eopdata,(*obs)(46,1),'l');
    tie(UT1_TAI,UTC_GPS,UT1_GPS,TT_UTC,GPS_UTC) = timediff(UT1_UTC,TAI_UTC);
    Mjd_TT = Mjd_UTC + TT_UTC/86400.0;
    AuxParam.Mjd_UTC = Mjd_UTC;
    AuxParam.Mjd_TT = Mjd_TT;

	t_aux = 0.0;
    DEInteg (Accel,t_aux,-((*obs)(46,1)-(*obs)(1,1))*86400.0,1e-13,1e-6,6,Y,iflag4,work4,iwork4);
    Matrix& Y0 = Y;

    Matrix& Y_true = zeros(6);
    Y_true(1) = 5753.173e3; Y_true(2) = 2673.361e3; Y_true(3) = 3440.304e3;
    Y_true(4) = 4.324207e3; Y_true(5) = -1.924299e3; Y_true(6) = -5.728216e3;

    printf("\nError of Position Estimation\n");
    printf("dX%10.1lf [m]\n",Y0(1)-Y_true(1));
    printf("dY%10.1lf [m]\n",Y0(2)-Y_true(2));
    printf("dZ%10.1lf [m]\n",Y0(3)-Y_true(3));
    printf("\nError of Velocity Estimation\n");
    printf("dVx%8.1lf [m/s]\n",Y0(4)-Y_true(4));
    printf("dVy%8.1lf [m/s]\n",Y0(5)-Y_true(5));
    printf("dVz%8.1lf [m/s]\n",Y0(6)-Y_true(6));

    return 0;
}