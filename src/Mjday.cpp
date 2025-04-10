// $Source$
//----------------------------------------------------------------------
// Mjday
//----------------------------------------------------------------------
// Proyecto TT1
//
/**@file Mjday.cpp
*	@brief Cálculo de la fecha juliana modificada.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\Mjday.hpp"

double Mjday (int yr, int mon, int day, int hr, int min, int sec){
	double jd = 367.0 * yr- floor( (7 * (yr + floor( (mon + 9) / 12.0) ) ) * 0.25 )+ floor( 275 * mon / 9.0 )+ day + 1721013.5+ ( (sec/60.0 + min ) / 60.0 + hr ) / 24.0;

	double Mjd = jd-2400000.5;
	
	return Mjd;
}

double Mjday (int yr, int mon, int day){
	return Mjday(yr,mon,day,0,0,0);
}