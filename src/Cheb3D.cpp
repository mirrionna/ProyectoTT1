// $Source$
//----------------------------------------------------------------------
// Cheb3D
//----------------------------------------------------------------------
// Proyecto TT1
//
/**@file Cheb3D.cpp
*	@brief Cálculo de una aproximación de chebyshev de un vector tridimensional.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\Cheb3D.hpp"

Matrix& Cheb3D (double t,int N, double Ta, double Tb, Matrix &Cx, Matrix &Cy, Matrix &Cz){
	//Check validity
	if ( (t<Ta) || (Tb<t) ) {
		cout<<"ERROR: Time out of range in Cheb3D::Value\n";
		exit(EXIT_FAILURE);
	}
		
	// Clenshaw algorithm
	double tau = (2*t-Ta-Tb)/(Tb-Ta);  
	
	Matrix f1 = zeros(3);
	Matrix f2 = zeros(3);
	Matrix old_f1 = zeros(3);
	for(int i=N;i>=2;i--){
		old_f1 = f1;
		Matrix aux(3);
		aux(1)=Cx(i);aux(2)=Cy(i);aux(3)=Cz(i);
		f1 = f1*2*tau-f2+aux;
		f2 = old_f1;
	}
	Matrix aux2(3);
	aux2(1)=Cx(1);aux2(2)=Cy(1);aux2(3)=Cz(1);
	Matrix& ChebApp = zeros(3);
	ChebApp = f1*tau-f2+aux2;
	return ChebApp;
	}