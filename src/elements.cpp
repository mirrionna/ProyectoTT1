// $Source$
//----------------------------------------------------------------------
// elements
//----------------------------------------------------------------------
// Proyecto TT1
//
/**@file elements.cpp
*	@brief Cálculo del semilatus rectum, el semieje mayor, la excentricidad, la inclinación, la longitud del nodo ascendente, el argumento del periastro y la anomalía media a partir del vector estado.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\elements.hpp"

double modelements(double a,double b){
	double r=fmod(a,b);
	if(r<0){
		r+=b;
	}
	return r;
}

tuple<double,double,double,double,double,double,double> elements (Matrix& y){
	double pi2 = SAT_Const::pi2;
 
	Matrix& r = extract_vector(y,1,3);                                        // Position
	Matrix& v = extract_vector(y,4,6);                                       // Velocity
 
	Matrix& h = cross(r,v);                                    // Areal velocity
	double magh = norm(h);
	double p = magh*magh/SAT_Const::GM_Earth;
	double H = norm(h);
	
	double Omega = atan2 ( h(1), -h(2) );                     // Long. ascend. node 
	Omega = modelements(Omega,pi2);
	double i     = atan2 ( sqrt(h(1)*h(1)+h(2)*h(2)), h(3) ); // Inclination        
	double u     = atan2 ( r(3)*H, -r(1)*h(2)+r(2)*h(1) );    // Arg. of latitude   
	
	double R  = norm(r);                                      // Distance           
	
	double a = 1/(2/R-dot(v,v)/SAT_Const::GM_Earth);               // Semi-major axis    
	
	double eCosE = 1-R/a;                                     // e*cos(E)           
	double eSinE = dot(r,v)/sqrt(SAT_Const::GM_Earth*a);           // e*sin(E)           
	
	double e2 = eCosE*eCosE +eSinE*eSinE;
	double e  = sqrt(e2);                                     // Eccentricity 
	double E  = atan2(eSinE,eCosE);                           // Eccentric anomaly  
	
	double M  = modelements(E-eSinE,pi2);                             // Mean anomaly
	
	double nu = atan2(sqrt(1.0-e2)*eSinE, eCosE-e2);          // True anomaly
	
	double omega = modelements(u-nu,pi2);                             // Arg. of perihelion 
	
	return std::tie(p, a, e, i, Omega, omega, M);
}