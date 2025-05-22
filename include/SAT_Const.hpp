// $Header$
//----------------------------------------------------------------------
// SAT_Const
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file SAT_Const.hpp
*	@brief Este archivo de cabecera contiene una implementación de una clase que contiene diferentes constantes.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _SAT_Const_
#define _SAT_Const_
#include <cmath>
#include <numbers>

//----------------------------------------------------------------------
/** @class SAT_Const
 *  @brief Clase que contiene constantes astronómicas y físicas utilizadas en cálculos satelitales.
 */
//----------------------------------------------------------------------
class SAT_Const {
public:

	//--------------
	// static constexpr double pi2
	//--------------
	/** @brief Constante matemática 2π. */
	static constexpr double pi2 = std::numbers::pi*2.0;                // 2pi

	//--------------
	// static constexpr double Rad
	//--------------
	/** @brief Radianes por grado. Factor de conversión de grados a radianes. */
	static constexpr double Rad = std::numbers::pi/180;              // Radians per degree

	//--------------
	// static constexpr double Deg
	//--------------
	/** @brief Grados por radian. Factor de conversión de radianes a grados. */
	static constexpr double Deg = 180.0/std::numbers::pi;              // Degrees per radian

	//--------------
	// static constexpr double Arcs
	//--------------
	/** @brief Segundos de arco por radian. */
	static constexpr double Arcs = 3600.0*180.0/std::numbers::pi;         // Arcseconds per radian

	//--------------
	// static constexpr double MJD_J2000
	//--------------
	/** @brief Fecha Juliana modificada para la época J2000.0. */
	static constexpr double MJD_J2000 = 51544.5;             // Modified Julian Date of J2000

	//--------------
	// static constexpr double T_B1950
	//--------------
	/** @brief Diferencia en siglos julianos desde J2000.0 hasta la época B1950. */
	static constexpr double T_B1950 = -0.500002108;        // Epoch B1950

	//--------------
	// static constexpr double c_light
	//--------------
	/** @brief Velocidad de la luz en el vacío [m/s]; DE430. */
	static constexpr double c_light = 299792458.000000000; // Speed of light  [m/s]; DE430

	//--------------
	// static constexpr double AU
	//--------------
	/** @brief Unidad astronómica [m]; DE430. */
	static constexpr double AU = 149597870700.000000; // Astronomical unit [m]; DE430

	//--------------
	// static constexpr double R_Earth
	//--------------
	/** @brief Radio ecuatorial medio de la Tierra [m]; DE430. */
	static constexpr double R_Earth = 6378.1363e3;      // Earth's radius [m]; DE430

	//--------------
	// static constexpr double f_Earth
	//--------------
	/** @brief Aplanamiento de la Tierra; WGS-84. */
	static constexpr double f_Earth = 1.0/298.257223563;  // Flattening; WGS-84

	//--------------
	// static constexpr double R_Sun
	//--------------
	/** @brief Radio del Sol [m]; DE430. */
	static constexpr double R_Sun = 696000e3;         // Sun's radius [m]; DE430

	//--------------
	// static constexpr double R_Moon
	//--------------
	/** @brief Radio de la Luna [m]; DE430. */
	static constexpr double R_Moon = 1738e3;           // Moon's radius [m]; DE430

	//--------------
	// static constexpr double omega_Earth
	//--------------
	/** @brief Velocidad angular de rotación de la Tierra [rad/s]; WGS-84. */
	static constexpr double omega_Earth = 15.04106717866910/3600.0*Rad;   // [rad/s]; WGS-84

	//--------------
	// static constexpr double GM_Earth
	//--------------
	/** @brief Parámetro gravitacional de la Tierra (GM) [m³/s²]; DE430. */
	static constexpr double GM_Earth = 398600.435436e9;                  // [m^3/s^2]; DE430

	//--------------
	// static constexpr double GM_Sun
	//--------------
	/** @brief Parámetro gravitacional del Sol (GM) [m³/s²]; DE430. */
	static constexpr double GM_Sun =132712440041.939400e9;            // [m^3/s^2]; DE430

	//--------------
	// static constexpr double GM_Moon
	//--------------
	/** @brief Parámetro gravitacional de la Luna (GM) [m³/s²]; DE430. */
	static constexpr double GM_Moon = GM_Earth/81.30056907419062; // [m^3/s^2]; DE430

	//--------------
	// static constexpr double GM_Mercury
	//--------------
	/** @brief Parámetro gravitacional de Mercurio (GM) [m³/s²]; DE430. */
	static constexpr double GM_Mercury = 22031.780000e9;                   // [m^3/s^2]; DE430

	//--------------
	// static constexpr double GM_Venus
	//--------------
	/** @brief Parámetro gravitacional de Venus (GM) [m³/s²]; DE430. */
	static constexpr double GM_Venus = 324858.592000e9;                  // [m^3/s^2]; DE430

	//--------------
	// static constexpr double GM_Mars
	//--------------
	/** @brief Parámetro gravitacional de Marte (GM) [m³/s²]; DE430. */
	static constexpr double GM_Mars =42828.375214e9;                   // [m^3/s^2]; DE430

	//--------------
	// static constexpr double GM_Jupiter
	//--------------
	/** @brief Parámetro gravitacional de Júpiter (GM) [m³/s²]; DE430. */
	static constexpr double GM_Jupiter= 126712764.800000e9;               // [m^3/s^2]; DE430

	//--------------
	// static constexpr double GM_Saturn
	//--------------
	/** @brief Parámetro gravitacional de Saturno (GM) [m³/s²]; DE430. */
	static constexpr double GM_Saturn = 37940585.200000e9;                // [m^3/s^2]; DE430

	//--------------
	// static constexpr double GM_Uranus
	//--------------
	/** @brief Parámetro gravitacional de Urano (GM) [m³/s²]; DE430. */
	static constexpr double GM_Uranus =5794548.600000e9;                 // [m^3/s^2]; DE430

	//--------------
	// static constexpr double GM_Neptune
	//--------------
	/** @brief Parámetro gravitacional de Neptuno (GM) [m³/s²]; DE430. */
	static constexpr double GM_Neptune =6836527.100580e9;                 // [m^3/s^2]; DE430

	//--------------
	// static constexpr double GM_Pluto
	//--------------
	/** @brief Parámetro gravitacional de Plutón (GM) [m³/s²]; DE430. */
	static constexpr double GM_Pluto = 977.0000000000009e9;              // [m^3/s^2]; DE430

	//--------------
	// static constexpr double P_Sol
	//--------------
	/** @brief Presión de radiación solar a 1 UA [N/m²]; IERS 96. */
	static constexpr double P_Sol =1367.0/c_light; // [N/m^2] (~1367 W/m^2); IERS 96
	
	//--------------
	// static constexpr double eps
	//--------------
	/** @brief Valor de eps de Matlab */
	static constexpr double eps =2.22044604925031e-16;

};
#endif