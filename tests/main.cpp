// $Source$
//----------------------------------------------------------------------
// main
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file main.cpp
*	@brief Archivo principal del proyecto de TTI.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\Cheb3D.hpp"
#include "..\include\matrix.h"
#include <iostream>

using namespace std;

int main() {
    Matrix Cx(13);
	Matrix Cy(13);
	Matrix Cz(13);
	Cx(1)=1;Cx(2)=2;Cx(3)=3;Cx(4)=4;Cx(5)=5;Cx(6)=6;Cx(7)=7;Cx(8)=8;Cx(9)=9;Cx(10)=10;Cx(11)=11;Cx(12)=12;Cx(13)=13;
	Cy(1)=1;Cy(2)=2;Cy(3)=3;Cy(4)=4;Cy(5)=5;Cy(6)=6;Cy(7)=7;Cy(8)=8;Cy(9)=-1;Cy(10)=-2;Cy(11)=-3;Cy(12)=-4;Cy(13)=-5;
	Cz(1)=1;Cz(2)=2;Cz(3)=3;Cz(4)=4;Cz(5)=5;Cz(6)=6;Cz(7)=7;Cz(8)=8;Cz(9)=0;Cz(10)=1;Cz(11)=2;Cz(12)=3;Cz(13)=4;
	cout<<Cheb3D(49746.1,13,49744,49760,Cx,Cy,Cz);
    return 0;
}