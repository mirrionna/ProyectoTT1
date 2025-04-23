// $Header$
//----------------------------------------------------------------------
// Cheb3D
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file Cheb3D.hpp
*	@brief Este archivo de cabecera contiene una implementación de la función Cheb3D.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _Cheb3D_
#define _Cheb3D_
#include "..\include\matrix.h"
//----------------------------------------------------------------------
//  Matrix& Cheb3D (int N, double Ta, double Tb, double Cx, double Cy, double Cz)
//----------------------------------------------------------------------
/**@brief Calcula una aproximación de chebyshev de un vector tridimensional.
*
*	@param [in] t Tiempo.  
*	@param [in] N Entero con el número de coeficientes.  
*	@param [in] Ta Double con el inicio del intervalo.  
*	@param [in] Tb Double con el fin del intervalo.  
*	@param [in] Cx Vector con el coeficiente del polinomio de Chebyshev en la coordenada x.  
*	@param [in] Cy Vector con el coeficiente del polinomio de Chebyshev en la coordenada y.  
*	@param [in] Cz Vector con el coeficiente del polinomio de Chebyshev en la coordenada z.  
*	@return Vector tridimensional con la aproximación de chebyshev. 
*/
//----------------------------------------------------------------------
Matrix& Cheb3D (double t,int N, double Ta, double Tb, Matrix &Cx, Matrix &Cy, Matrix &Cz);	
#endif