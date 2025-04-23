// $Source$
//----------------------------------------------------------------------
// TimeUpdate
//----------------------------------------------------------------------
// Proyecto TT1
//
/**@file TimeUpdate.cpp
*	@brief Cálculo de la actualización del tiempo.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\TimeUpdate.hpp"

Matrix& TimeUpdate (Matrix &P, Matrix &Phi, double Qdt){
	return Phi*P*transpose(Phi) + Qdt;
	
}
Matrix& TimeUpdate (Matrix &P, Matrix &Phi){
	return TimeUpdate(P,Phi,0.0);
}
