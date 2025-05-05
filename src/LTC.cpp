// $Source$
//----------------------------------------------------------------------
// LTC
//----------------------------------------------------------------------
// Proyecto TT1
//
/**@file LTC.cpp
*	@brief Cálculo de la matriz de rotación desde el ecuador norte y el meridiano de Greenwich hasta el sistema de coordenadas de la tangente local.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\LTC.hpp"

Matrix& LTC (double lon, double lat){
	
	Matrix& M = R_y(-1.0*lat)*R_z(lon);
	
	for(int j=1;j<=3;j++){
		double Aux=M(1,j); M(1,j)=M(2,j); M(2,j)=M(3,j); M(3,j)= Aux;
	}

	return M;
	
}