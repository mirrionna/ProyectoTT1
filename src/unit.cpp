// $Source$
//----------------------------------------------------------------------
// unit
//----------------------------------------------------------------------
// Proyecto TT1
//
/**@file unit.cpp
*	@brief Cálculo del vector unitario de un vector dado.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\unit.hpp"

Matrix& unit (Matrix &vec){
	double small = 0.000001;
	double magv = norm(vec);
	Matrix& outvec = zeros(3);
	if ( magv > small ){
		for (int i=1;i<=3;i++){
			outvec(i)= vec(i)/magv;
		}
	}
	return outvec;
}