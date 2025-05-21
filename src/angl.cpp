// $Source$
//----------------------------------------------------------------------
// angl
//----------------------------------------------------------------------
// Proyecto TT1
//
/**@file angl.cpp
*	@brief Cálculo del ángulo en el intervalo [-π,π] entre dos vectores.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\angl.hpp"

//----------------------------------------------------------------------
//  int sign(double a)
//----------------------------------------------------------------------
/**@brief Función auxiliar que devuelve el signo de un double.
*
*	@param [in] a Double del que se quiere calcular el signo.   
*	@return Devuelve 1 en caso de que a sea positivo, -1 si a es negativo.
*/
//----------------------------------------------------------------------
int sign(double a){
	return (0.0<a) - (a<0.0);
}

double angl (Matrix &vec1, Matrix &vec2){
	double small     = 0.00000001;
	double undefined = 999999.1;
	double theta;
	double magv1 = norm(vec1);
	double magv2 = norm(vec2);

	if (magv1*magv2 > small^2){
		double temp= dot(vec1,vec2) / (magv1*magv2);
		if (abs( temp ) > 1.0){
			temp= sign(temp) * 1.0;
		}
		theta = acos( temp );
	}
	else{
		theta = undefined;
	}
	
	return theta;
}