// $Source$
//----------------------------------------------------------------------
// G_AccelHarmonic
//----------------------------------------------------------------------
// Proyecto TT1
//
/**@file G_AccelHarmonic.cpp
*	@brief Cálculo del gradiente del campo gravitacional armónico de la Tierra.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\G_AccelHarmonic.hpp"

Matrix& G_AccelHarmonic (Matrix &r, Matrix &U, int n_max, int m_max){
	double d = 1.0;   // Position increment [m]

	Matrix& G = zeros(3,3);
	Matrix& dr = zeros(3,1);

	// Gradient
	for(int i=1;i<=3;i++){
		// Set offset in i-th component of the position vector
		dr = zeros(3,1);
		dr(i) = d;
		// Acceleration difference
		Matrix& da = AccelHarmonic ( r+dr/2,U, n_max, m_max ) - AccelHarmonic ( r-dr/2,U, n_max, m_max );
		// Derivative with respect to i-th axis
		Matrix& aux = da/d;
		for(int j=1;j<=3;j++){
			G(j,i) = aux(j,i);
		}    
	}
	
	return G;

}