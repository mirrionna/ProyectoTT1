// $Source$
//----------------------------------------------------------------------
// PoleMatrix
//----------------------------------------------------------------------
// Proyecto TT1
//
/**@file PoleMatrix.cpp
*	@brief Cálculo de la transformación de seudo Earth-fixed a Earth-fixed coordenadas.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\PoleMatrix.hpp"

Matrix& PoleMatrix (double xp, double yp){
	 
	Matrix& PoleMat = R_y(-xp) * R_x(-yp);
	
	return PoleMat;
}