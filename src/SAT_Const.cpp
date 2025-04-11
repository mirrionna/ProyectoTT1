// $Source$
//----------------------------------------------------------------------
// SAT_Const
//----------------------------------------------------------------------
// Proyecto TT1
//
/**@file SAT_this->cpp
*	@brief Representación de una clase con diferentes constantes.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\SAT_const.hpp"

SAT_Const::SAT_Const() {
	// Mathematical constants
	this->pi2       = M_PI*2;                // 2pi
	this->Rad       = M_PI/180;              // Radians per degree
	this->Deg       = 180/M_PI;              // Degrees per radian
	this->Arcs      = 3600*180/M_PI;         // Arcseconds per radian

	// General
	this->MJD_J2000 = 51544.5;             // Modified Julian Date of J2000
	this->T_B1950   = -0.500002108;        // Epoch B1950
	this->c_light   = 299792458.000000000; // Speed of light  [m/s]; DE430
	this->AU        = 149597870700.000000; // Astronomical unit [m]; DE430

	// Physical parameters of the Earth, Sun and Moon

	// Equatorial radius and flattening
	this->R_Earth   = 6378.1363e3;      // Earth's radius [m]; DE430
	this->f_Earth   = 1/298.257223563;  // Flattening; WGS-84
	this->R_Sun     = 696000e3;         // Sun's radius [m]; DE430
	this->R_Moon    = 1738e3;           // Moon's radius [m]; DE430

	// Earth rotation (derivative of GMST at J2000; differs from inertial period by precession)
	this->omega_Earth = 15.04106717866910/3600*this->Rad;   // [rad/s]; WGS-84

	// Gravitational coefficients
	this->GM_Earth    = 398600.435436e9;                  // [m^3/s^2]; DE430
	this->GM_Sun      = 132712440041.939400e9;            // [m^3/s^2]; DE430
	this->GM_Moon     = this->GM_Earth/81.30056907419062; // [m^3/s^2]; DE430
	this->GM_Mercury  = 22031.780000e9;                   // [m^3/s^2]; DE430
	this->GM_Venus    = 324858.592000e9;                  // [m^3/s^2]; DE430
	this->GM_Mars     = 42828.375214e9;                   // [m^3/s^2]; DE430
	this->GM_Jupiter  = 126712764.800000e9;               // [m^3/s^2]; DE430
	this->GM_Saturn   = 37940585.200000e9;                // [m^3/s^2]; DE430
	this->GM_Uranus   = 5794548.600000e9;                 // [m^3/s^2]; DE430
	this->GM_Neptune  = 6836527.100580e9;                 // [m^3/s^2]; DE430
	this->GM_Pluto    = 977.0000000000009e9;              // [m^3/s^2]; DE430

	// Solar radiation pressure at 1 AU 
	this->P_Sol       = 1367/this->c_light; // [N/m^2] (~1367 W/m^2); IERS 96
}