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

//----------------------------------------------------------------------
/** @class SAT_Const
 *  @brief Clase que contiene constantes astronómicas y físicas utilizadas en cálculos satelitales.
 */
//----------------------------------------------------------------------
class SAT_Const {
public:

	//--------------
	// double pi2
	//--------------
	/** @brief Constante matemática 2π. */
	double pi2;

	//--------------
	// double Rad
	//--------------
	/** @brief Radianes por grado. Factor de conversión de grados a radianes. */
	double Rad;

	//--------------
	// double Deg
	//--------------
	/** @brief Grados por radian. Factor de conversión de radianes a grados. */
	double Deg;

	//--------------
	// double Arcs
	//--------------
	/** @brief Segundos de arco por radian. */
	double Arcs;

	//--------------
	// double MJD_J2000
	//--------------
	/** @brief Fecha Juliana modificada para la época J2000.0. */
	double MJD_J2000;

	//--------------
	// double T_B1950
	//--------------
	/** @brief Diferencia en siglos julianos desde J2000.0 hasta la época B1950. */
	double T_B1950;

	//--------------
	// double c_light
	//--------------
	/** @brief Velocidad de la luz en el vacío [m/s]; DE430. */
	double c_light;

	//--------------
	// double AU
	//--------------
	/** @brief Unidad astronómica [m]; DE430. */
	double AU;

	//--------------
	// double R_Earth
	//--------------
	/** @brief Radio ecuatorial medio de la Tierra [m]; DE430. */
	double R_Earth;

	//--------------
	// double f_Earth
	//--------------
	/** @brief Aplanamiento de la Tierra; WGS-84. */
	double f_Earth;

	//--------------
	// double R_Sun
	//--------------
	/** @brief Radio del Sol [m]; DE430. */
	double R_Sun;

	//--------------
	// double R_Moon
	//--------------
	/** @brief Radio de la Luna [m]; DE430. */
	double R_Moon;

	//--------------
	// double omega_Earth
	//--------------
	/** @brief Velocidad angular de rotación de la Tierra [rad/s]; WGS-84. */
	double omega_Earth;

	//--------------
	// double GM_Earth
	//--------------
	/** @brief Parámetro gravitacional de la Tierra (GM) [m³/s²]; DE430. */
	double GM_Earth;

	//--------------
	// double GM_Sun
	//--------------
	/** @brief Parámetro gravitacional del Sol (GM) [m³/s²]; DE430. */
	double GM_Sun;

	//--------------
	// double GM_Moon
	//--------------
	/** @brief Parámetro gravitacional de la Luna (GM) [m³/s²]; DE430. */
	double GM_Moon;

	//--------------
	// double GM_Mercury
	//--------------
	/** @brief Parámetro gravitacional de Mercurio (GM) [m³/s²]; DE430. */
	double GM_Mercury;

	//--------------
	// double GM_Venus
	//--------------
	/** @brief Parámetro gravitacional de Venus (GM) [m³/s²]; DE430. */
	double GM_Venus;

	//--------------
	// double GM_Mars
	//--------------
	/** @brief Parámetro gravitacional de Marte (GM) [m³/s²]; DE430. */
	double GM_Mars;

	//--------------
	// double GM_Jupiter
	//--------------
	/** @brief Parámetro gravitacional de Júpiter (GM) [m³/s²]; DE430. */
	double GM_Jupiter;

	//--------------
	// double GM_Saturn
	//--------------
	/** @brief Parámetro gravitacional de Saturno (GM) [m³/s²]; DE430. */
	double GM_Saturn;

	//--------------
	// double GM_Uranus
	//--------------
	/** @brief Parámetro gravitacional de Urano (GM) [m³/s²]; DE430. */
	double GM_Uranus;

	//--------------
	// double GM_Neptune
	//--------------
	/** @brief Parámetro gravitacional de Neptuno (GM) [m³/s²]; DE430. */
	double GM_Neptune;

	//--------------
	// double GM_Pluto
	//--------------
	/** @brief Parámetro gravitacional de Plutón (GM) [m³/s²]; DE430. */
	double GM_Pluto;

	//--------------
	// double P_Sol
	//--------------
	/** @brief Presión de radiación solar a 1 UA [N/m²]; IERS 96. */
	double P_Sol;

    // Parameterized constructor
	//----------------------------------------------------------------------
	// SAT_Const()
	//----------------------------------------------------------------------
	/**@brief Constructor de la clase SAT_Const.
	*	@return SAT_Const con todas las constantes dentro como atributos.
	*/
	//----------------------------------------------------------------------
    SAT_Const();
};
#endif