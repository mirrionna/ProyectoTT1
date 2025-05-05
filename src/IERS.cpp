// $Source$
//----------------------------------------------------------------------
// IERS
//----------------------------------------------------------------------
// Proyecto TT1
//
/**@file IERS.cpp
*	@brief Cálculo de los tiempos IERS y los datos de movimiento polar.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\IERS.hpp"
int find(Matrix a, double b){
	for(int i=1;i<=a.n_column;i++){
		if(abs(a(i)-b)<1e-10) return i;
	}
	return -1;
}
tuple<double,double,double,double,double,double,double,double,double> IERS(Matrix &eop,double Mjd_UTC,char interp){
	double x_pole,y_pole,UT1_UTC,LOD,dpsi,deps,dx_pole,dy_pole,TAI_UTC;
	if (interp =='l'){
    // linear interpolation
    double mjd = (floor(Mjd_UTC));
    int i = find(extract_row(eop,4),mjd);
    Matrix preeop = extract_column(eop,i);
    Matrix nexteop = extract_column(eop,i+1);
    double mfme = 1440*(Mjd_UTC-floor(Mjd_UTC));
    double fixf = mfme/1440;
    // Setting of IERS Earth rotation parameters
    // (UT1-UTC [s], TAI-UTC [s], x ["], y ["])
    x_pole  = preeop(5)+(nexteop(5)-preeop(5))*fixf;
    y_pole  = preeop(6)+(nexteop(6)-preeop(6))*fixf;
	UT1_UTC = preeop(7)+(nexteop(7)-preeop(7))*fixf;
    LOD     = preeop(8)+(nexteop(8)-preeop(8))*fixf;
    dpsi    = preeop(9)+(nexteop(9)-preeop(9))*fixf;
    deps    = preeop(10)+(nexteop(10)-preeop(10))*fixf;
    dx_pole = preeop(11)+(nexteop(11)-preeop(11))*fixf;
    dy_pole = preeop(12)+(nexteop(12)-preeop(12))*fixf;
    TAI_UTC = preeop(13);
	
    x_pole  = x_pole/SAT_Const::Arcs;  // Pole coordinate [rad]
    y_pole  = y_pole/SAT_Const::Arcs;  // Pole coordinate [rad]
    dpsi    = dpsi/SAT_Const::Arcs;
    deps    = deps/SAT_Const::Arcs;
    dx_pole = dx_pole/SAT_Const::Arcs; // Pole coordinate [rad]
    dy_pole = dy_pole/SAT_Const::Arcs; // Pole coordinate [rad]
	}
	else if (interp =='n')    {
		double mjd = (floor(Mjd_UTC));
		int i = find(extract_row(eop,4),mjd);
		Matrix eop = extract_column(eop,i);
		// Setting of IERS Earth rotation parameters
		// (UT1-UTC [s], TAI-UTC [s], x ["], y ["])
		x_pole  = eop(5)/SAT_Const::Arcs;  // Pole coordinate [rad]
		y_pole  = eop(6)/SAT_Const::Arcs;  // Pole coordinate [rad]
		UT1_UTC = eop(7);             // UT1-UTC time difference [s]
		LOD     = eop(8);             // Length of day [s]
		dpsi    = eop(9)/SAT_Const::Arcs;
		deps    = eop(10)/SAT_Const::Arcs;
		dx_pole = eop(11)/SAT_Const::Arcs; // Pole coordinate [rad]
		dy_pole = eop(12)/SAT_Const::Arcs; // Pole coordinate [rad]
		TAI_UTC = eop(13);            // TAI-UTC time difference [s]
	}
	return std::tie(x_pole,y_pole,UT1_UTC,LOD,dpsi,deps,dx_pole,dy_pole,TAI_UTC);
}
tuple<double,double,double,double,double,double,double,double,double> IERS(Matrix &eop,double Mjd_UTC){
	return IERS(eop,Mjd_UTC,'n');
}
