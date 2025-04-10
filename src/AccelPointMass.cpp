// $Source$
//----------------------------------------------------------------------
// AccelPointMass
//----------------------------------------------------------------------
// Proyecto TT1
//
/**@file AccelPointMass.cpp
*	@brief Cálculo de la aceleración pertubacional de un satélite debido a un punto de masas.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\matrix.h"
#include "..\include\AccelPointMass.hpp"

Matrix& AccelPointMass (Matrix &r, Matrix &s, double GM){
	// Relative position vector of satellite w.r.t. point mass 
	Matrix& d = r - s;

	// Acceleration 
	Matrix& a = ( d/(pow(norm(d),3)) + s/(pow(norm(s),3)) ) * -GM;
	
	return a;
}
