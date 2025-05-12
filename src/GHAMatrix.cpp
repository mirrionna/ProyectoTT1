// $Source$
//----------------------------------------------------------------------
// GHAMatrix
//----------------------------------------------------------------------
// Proyecto TT1
//
/**@file GHAMatrix.cpp
*	@brief Cálculo de la matriz de transofmración del ecuador y equinoccio real al ecuador de la Tierra y el sistema del meridiano de Greenwich.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\GHAMatrix.hpp"

Matrix& GHAMatrix (double Mjd_UT1){
	Matrix& GHAmat = R_z( gast(Mjd_UT1) );
	return GHAmat;
}
