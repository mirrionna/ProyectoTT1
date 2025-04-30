// $Source$
//----------------------------------------------------------------------
// PoleMatrix
//----------------------------------------------------------------------
// Proyecto TT1
//
/**@file PoleMatrix.cpp
*	@brief Cálculo de la aceleración pertubacional de un satélite debido a un punto de masas.
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