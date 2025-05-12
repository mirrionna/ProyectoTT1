// $Source$
//----------------------------------------------------------------------
// MeasUpdate
//----------------------------------------------------------------------
// Proyecto TT1
//
/**@file MeasUpdate.cpp
*	@brief Cálculo de tres matrices.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\MeasUpdate.hpp"

tuple<Matrix&,Matrix&,Matrix&> MeasUpdate (Matrix &x, double z, double g, double s, Matrix &G, Matrix &P, int n){
	Matrix& Inv_W = zeros(1,1);
	Inv_W(1,1) = s*s;    // Inverse weight (measurement covariance)
	// Kalman gain
	Matrix& K = P*transpose(G)*inv(Inv_W+G*P*transpose(G));
	// State update
	x = x + K*(z-g);
	// Covariance update
	P = (eye(n)-K*G)*P;
	return std::tie(K, x, P);
}