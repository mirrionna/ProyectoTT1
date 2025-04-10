// $Source$
//----------------------------------------------------------------------
// R_y
//----------------------------------------------------------------------
// Proyecto TT1
//
/**@file R_y.cpp
*	@brief Cálculo de la matriz de rotación en el eje y de un ángulo.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\matrix.h"
#include "..\include\R_y.hpp"

Matrix& R_y (double angle){
	double C = cos(angle);
	double S = sin(angle);
	Matrix& rotmat = zeros(3,3);

	rotmat(1,1) =   C;  rotmat(1,2) = 0.0;  rotmat(1,3) = -1.0*S;
	rotmat(2,1) = 0.0;  rotmat(2,2) = 1.0;  rotmat(2,3) =    0.0;
	rotmat(3,1) =   S;  rotmat(3,2) = 0.0;  rotmat(3,3) =      C;
	
	return rotmat;
}
