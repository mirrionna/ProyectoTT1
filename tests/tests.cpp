// $Source$
//----------------------------------------------------------------------
// tests
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file tests.cpp
*	@brief Tests unitarios para los métodos del proyecto de TTI.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\matrix.h"
#include "..\include\R_x.hpp"
#include "..\include\R_y.hpp"
#include "..\include\R_z.hpp"
#include "..\include\AccelPointMass.hpp"
#include "..\include\Cheb3D.hpp"
#include "..\include\EccAnom.hpp"
#include "..\include\Frac.hpp"
#include "..\include\MeanObliquity.hpp"
#include "..\include\Mjday.hpp"
#include "..\include\Mjday_TDB.hpp"
#include "..\include\Position.hpp"
#include "..\include\sign_.hpp"
#include "..\include\timediff.hpp"
#include "..\include\AzElPa.hpp"
#include "..\include\Legendre.hpp"
#include "..\include\TimeUpdate.hpp"
#include "..\include\NutAngles.hpp"
#include "..\include\IERS.hpp"
#include "..\include\NutMatrix.hpp"
#include "..\include\PoleMatrix.hpp"
#include "..\include\PrecMatrix.hpp"
#include "..\include\AccelHarmonic.hpp"
#include "..\include\EqnEquinox.hpp"
#include "..\include\LTC.hpp"
#include "..\include\gmst.hpp"
#include "..\include\JPL_Eph_DE430.hpp"
#include "..\include\gast.hpp"
#include "..\include\MeasUpdate.hpp"
#include "..\include\G_AccelHarmonic.hpp"
#include "..\include\GHAMatrix.hpp"
#include "..\include\Accel.hpp"
#include "..\include\VarEqn.hpp"
#include "..\include\DEInteg.hpp"

#include "..\include\Geodetic.hpp"
#include "..\include\angl.hpp"
#include "..\include\elements.hpp"
#include "..\include\unit.hpp"
#include "..\include\gibbs.hpp"
#include "..\include\hgibbs.hpp"
#include "..\include\anglesg.hpp"
#include "..\include\rpoly.h"

#include "..\include\global.hpp"

#include <cstdio>
#include <cmath>
#include <tuple>
#include <string>
int tests_run = 0;

using namespace std;

#define FAIL() printf("\nfailure in %s() line %d\n", __func__, __LINE__)
#define _assert(test) do { if (!(test)) { FAIL(); return 1; } } while(0)
#define _verify(test) do { int r=test(); tests_run++; if(r) return r; } while(0)


int m_equals(Matrix A, Matrix B, double p) {
	if (A.n_row != B.n_row || A.n_column != B.n_column){
		cout<<A;
		cout<<B;
		return 0;
	}
	else
		for(int i = 1; i <= A.n_row; i++)
			for(int j = 1; j <= A.n_column; j++)
				if(fabs(A(i,j)-B(i,j)) > p) {
					printf("%2.20lf %2.20lf\n",A(i,j),B(i,j));
					return 0;
				}
	
	return 1;
}

int m_sum_01() {
    int f = 3;
    int c = 4;
	
	Matrix A(f, c);
	A(1,1) = 0; A(1,2) =  2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) =  1; A(3,3) = 0; A(3,4) = 5;
	
	Matrix B(f, c);
	B(1,1) = 2; B(1,2) =  0; B(1,3) = 0; B(1,4) = 0;
	B(2,1) = 7; B(2,2) = -2; B(2,3) = 1; B(2,4) = 0;
	B(3,1) = 0; B(3,2) = -3; B(3,3) = 0; B(3,4) = 2;
	
	Matrix C(f, c);
	C(1,1) = 2; C(1,2) =  2; C(1,3) = 8; C(1,4) = 0;
	C(2,1) = 8; C(2,2) = -3; C(2,3) = 1; C(2,4) = 0;
	C(3,1) = 0; C(3,2) = -2; C(3,3) = 0; C(3,4) = 7;
	
	Matrix R = A + B;
    
    _assert(m_equals(C, R, 1e-10));
    
    return 0;
}

int m_sub_01() {
    int f = 3;
    int c = 4;
	
	Matrix A(f, c);
	A(1,1) = 0; A(1,2) = 2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) = 1; A(3,3) = 0; A(3,4) = 5;
	
	Matrix B(f, c);
	B(1,1) = 2; B(1,2) = 0; B(1,3) = 0; B(1,4) = 0;
	B(2,1) = 7; B(2,2) = -2; B(2,3) = 1; B(2,4) = 0;
	B(3,1) = 0; B(3,2) = -3; B(3,3) = 0; B(3,4) = 2;
	
	Matrix C(f, c);
	C(1,1) = -2; C(1,2) = 2; C(1,3) = 8; C(1,4) = 0;
	C(2,1) = -6; C(2,2) = 1; C(2,3) = -1; C(2,4) = 0;
	C(3,1) = 0; C(3,2) = 4; C(3,3) = 0; C(3,4) = 3;
	
	Matrix R = A - B;
    
    _assert(m_equals(C, R, 1e-10));
    
    return 0;
}

int m_mul_01() {
    int f = 3;
    int c = 4;
	
	Matrix A(f, c);
	A(1,1) = 1; A(1,2) = 2; A(1,3) = 3; A(1,4) = 4;
	A(2,1) = 5; A(2,2) = 6; A(2,3) = 7; A(2,4) = 8;
	A(3,1) = -1; A(3,2) = -2; A(3,3) = -3; A(3,4) = -4;
	Matrix B(c, f);
	B(1,1) = 1; B(1,2) = 2; B(1,3) = 3;
	B(2,1) = 3; B(2,2) = 2; B(2,3) = 1;
	B(3,1) = -1; B(3,2) = -2; B(3,3) = -3;
	B(4,1) = -3; B(4,2) = -2; B(4,3) = -1;

	Matrix C(f, f);
	C(1,1) = -8; C(1,2) = -8; C(1,3) = -8;
	C(2,1) = -8; C(2,2) = -8; C(2,3) = -8;
	C(3,1) = 8; C(3,2) = 8; C(3,3) = 8;

	Matrix R = A * B;
    _assert(m_equals(C, R, 1e-10));
    
    return 0;
}

int m_div_01() {
    int f = 3;
    int c = 3;
	
	Matrix A(f, c);
	A(1,1) = 1; A(1,2) = 2; A(1,3) = 3;
	A(2,1) = 4; A(2,2) = 5; A(2,3) = 6;
	A(3,1) = -1; A(3,2) = -2; A(3,3) = -3;
	
	Matrix B(f, c);
	B(1,1) = 1; B(1,2) = 2; B(1,3) = 3;
	B(2,1) = 1; B(2,2) = 2; B(2,3) = 4;
	B(3,1) = -1; B(3,2) = -5; B(3,3) = -3;
	
	Matrix C(f, c);
	C(1,1) = 1; C(1,2) = 0; C(1,3) = 0;
	C(2,1) = 11; C(2,2) = -6; C(2,3) = 1;
	C(3,1) = -1; C(3,2) = 0; C(3,3) = 0;
	
	Matrix R = A / B;
    
    _assert(m_equals(C, R, 1e-10));
    
    return 0;
}

int m_asig_01() {
	
	int f = 3;
    int c = 4;
	
	Matrix A(f, c);
	A(1,1) = 0; A(1,2) = 2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) = 1; A(3,3) = 0; A(3,4) = 5;
	
	Matrix R = A;
    
	_assert(m_equals(A, R, 1e-10));
	
    return 0;
}

int m_zeros_01() {
    int f = 3;
    int c = 4;
	
	Matrix A(f, c);
	A(1,1) = 0; A(1,2) = 0; A(1,3) = 0; A(1,4) = 0;
	A(2,1) = 0; A(2,2) = 0; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) = 0; A(3,3) = 0; A(3,4) = 0;
	
	Matrix B = zeros(3, 4);
    
    _assert(m_equals(A, B, 1e-10));
    
    return 0;
}

int v_zeros_01() {
    int c = 4;
	
	Matrix A(c);
	A(1,1) = 0; A(1,2) = 0; A(1,3) = 0; A(1,4) = 0;
	
	Matrix B = zeros(4);
    
    _assert(m_equals(A, B, 1e-10));
    
    return 0;
}

int m_eye_01() {
    int f = 3;
	
	Matrix A(f,f);
	A(1,1) = 1; A(1,2) = 0; A(1,3) = 0;
	A(2,1) = 0; A(2,2) = 1; A(2,3) = 0;
	A(3,1) = 0; A(3,2) = 0; A(3,3) = 1;
	
	Matrix B = eye(3);
    
    _assert(m_equals(A, B, 1e-10));
    
    return 0;
}

int m_transpose_01() {
    int f = 3;
	int c = 4;
	Matrix A(f,c);
	A(1,1) = 1; A(1,2) = 2; A(1,3) = 3;A(1,4) = 4;
	A(2,1) = 5; A(2,2) = 6; A(2,3) = 7;A(2,4) = 8;
	A(3,1) = 9; A(3,2) = 10; A(3,3) = 11;A(3,4) = 12;
	Matrix B(c,f);
	B(1,1) = 1; B(1,2) = 5; B(1,3) = 9;
	B(2,1) = 2; B(2,2) = 6; B(2,3) = 10;
	B(3,1) = 3; B(3,2) = 7; B(3,3) = 11;
	B(4,1) = 4; B(4,2) = 8; B(4,3) = 12;
	Matrix C = transpose(A);
    
    _assert(m_equals(B, C, 1e-10));
    
    return 0;
}

int m_inv_01() {
    int f = 3;
	Matrix A(f,f);
	A(1,1) = 1; A(1,2) = -1; A(1,3) = 0;
	A(2,1) = -1; A(2,2) = 2; A(2,3) = 0;
	A(3,1) = 0; A(3,2) = 0; A(3,3) = 1;
	Matrix B(f,f);
	B(1,1) = 2; B(1,2) = 1; B(1,3) = 0;
	B(2,1) = 1; B(2,2) = 1; B(2,3) = 0;
	B(3,1) = 0; B(3,2) = 0; B(3,3) = 1;
	Matrix C = inv(A);
    _assert(m_equals(B, C, 1e-10));
    
    return 0;
}

int m_determinante_01() {
    int f = 3;
	Matrix A(f,f);
	A(1,1) = 1; A(1,2) = -1; A(1,3) = 0;
	A(2,1) = -1; A(2,2) = 2; A(2,3) = 0;
	A(3,1) = 0; A(3,2) = 0; A(3,3) = 1;
	double det=1;
    
	_assert(abs(det - determinante(A)) < 1e-10);
    
    return 0;
}

int m_submatriz_01() {
    int f = 3;
	Matrix A(f,f);
	A(1,1) = 1; A(1,2) = -1; A(1,3) = 0;
	A(2,1) = -1; A(2,2) = 2; A(2,3) = 0;
	A(3,1) = 0; A(3,2) = 0; A(3,3) = 1;
	
	Matrix B(f-1,f-1);
	B(1,1) = 1; B(1,2) = 0;
	B(2,1) = 0; B(2,2) = 1;
	
	Matrix C = submatriz(A,2,2);
    _assert(m_equals(B, C, 1e-10));
    
    return 0;
}

int m_sumdouble_01() {
    int f = 3;
    int c = 4;
	
	Matrix A(f, c);
	A(1,1) = 0; A(1,2) =  2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) =  1; A(3,3) = 0; A(3,4) = 5;
	
	Matrix B(f, c);
	B(1,1) = 2; B(1,2) =  4; B(1,3) = 10; B(1,4) = 2;
	B(2,1) = 3; B(2,2) = 1; B(2,3) = 2; B(2,4) = 2;
	B(3,1) = 2; B(3,2) = 3; B(3,3) = 2; B(3,4) = 7;
	
	
	Matrix R = A + 2;
    
    _assert(m_equals(B, R, 1e-10));
    
    return 0;
}

int m_subdouble_01() {
    int f = 3;
    int c = 4;
	
	Matrix A(f, c);
	A(1,1) = 0; A(1,2) =  2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) =  1; A(3,3) = 0; A(3,4) = 5;
	
	Matrix B(f, c);
	B(1,1) = -2; B(1,2) =  0; B(1,3) = 6; B(1,4) = -2;
	B(2,1) = -1; B(2,2) = -3; B(2,3) = -2; B(2,4) = -2;
	B(3,1) = -2; B(3,2) = -1; B(3,3) = -2; B(3,4) = 3;
	
	
	Matrix R = A - 2;
    
    _assert(m_equals(B, R, 1e-10));
    
    return 0;
}

int m_muldouble_01() {
    int f = 3;
    int c = 4;
	
	Matrix A(f, c);
	A(1,1) = 0; A(1,2) =  2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) =  1; A(3,3) = 0; A(3,4) = 5;
	
	Matrix B(f, c);
	B(1,1) = 0; B(1,2) =  4; B(1,3) = 16; B(1,4) = 0;
	B(2,1) = 2; B(2,2) = -2; B(2,3) = 0; B(2,4) = 0;
	B(3,1) = 0; B(3,2) = 2; B(3,3) = 0; B(3,4) = 10;
	
	
	Matrix R = A * 2;
    
    _assert(m_equals(B, R, 1e-10));
    
    return 0;
}

int m_divdouble_01() {
    int f = 3;
    int c = 4;
	
	Matrix A(f, c);
	A(1,1) = 0; A(1,2) =  2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) =  1; A(3,3) = 0; A(3,4) = 5;
	
	Matrix B(f, c);
	B(1,1) = 0; B(1,2) =  1; B(1,3) = 4; B(1,4) = 0;
	B(2,1) = 0.5; B(2,2) = -0.5; B(2,3) = 0; B(2,4) = 0;
	B(3,1) = 0; B(3,2) = 0.5; B(3,3) = 0; B(3,4) = 2.5;
	
	
	Matrix R = A / 2;
    
    _assert(m_equals(B, R, 1e-10));
    
    return 0;
}

int m_extractvec_01(){
    int c = 4;
	
	Matrix A(c);
	A(1) = 0; A(2) =  2; A(3) = 8; A(4) = 0;
	
	Matrix B(2);
	B(1) =  2; B(2) = 8;
	
	Matrix R = extract_vector(A,2,3);
    
    _assert(m_equals(B, R, 1e-10));
    
    return 0;
}

int m_unionvec_01(){
    int c = 4;
	
	Matrix A(c);
	A(1) = 0; A(2) =  2; A(3) = 8; A(4) = 0;
	
	Matrix B(c+1);
	B(1) = 1; B(2) =  2; B(3) = 3; B(4) = 4;B(5)=5;
	
	Matrix C(2*c+1);
	C(1) = 0; C(2) =  2; C(3) = 8; C(4) = 0;
	C(5) = 1; C(6) =  2; C(7) = 3; C(8) = 4;C(9)=5;

	Matrix R = union_vector(A,B);
    
    _assert(m_equals(C, R, 1e-10));
    
    return 0;
}

int m_extractrow_01(){
	int f = 3;
    int c = 4;
	
	Matrix A(f, c);
	A(1,1) = 0; A(1,2) =  2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) =  1; A(3,3) = 0; A(3,4) = 5;
	
	Matrix B(c);
	B(1) = 0; B(2) =  2; B(3) = 8; B(4) = 0;
	
	Matrix R = extract_row(A,1);
    
    _assert(m_equals(B, R, 1e-10));
    
    return 0;
}

int m_extractcol_01(){
	int f = 3;
    int c = 4;
	
	Matrix A(f, c);
	A(1,1) = 0; A(1,2) =  2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) =  1; A(3,3) = 0; A(3,4) = 5;
	
	Matrix B(f);
	B(1) = 0;B(2) = 1;B(3) = 0;
	
	Matrix R = extract_column(A,1);
    
    _assert(m_equals(B, R, 1e-10));
    
    return 0;
}

int m_assignrow_01(){
	int f = 3;
    int c = 4;
	
	Matrix A(f, c);
	A(1,1) = 0; A(1,2) =  2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) =  1; A(3,3) = 0; A(3,4) = 5;
	
	Matrix B(c);
	B(1) = 1; B(2) =  2; B(3) = 3; B(4) = 4;
	
	Matrix R = assign_row(1,A,B);
	
	Matrix C(f, c);
	C(1,1) = 1; C(1,2) =  2; C(1,3) = 3; C(1,4) = 4;
	C(2,1) = 1; C(2,2) = -1; C(2,3) = 0; C(2,4) = 0;
	C(3,1) = 0; C(3,2) =  1; C(3,3) = 0; C(3,4) = 5;
    
    _assert(m_equals(C, R, 1e-10));
    
    return 0;
}

int m_assigncol_01(){
	int f = 3;
    int c = 4;
	
	Matrix A(f, c);
	A(1,1) = 0; A(1,2) =  2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) =  1; A(3,3) = 0; A(3,4) = 5;
	
	Matrix B(f);
	B(1) = 1;B(2) = 2;B(3) = 3;
	
	Matrix R = assign_column(1,A,B);
    
	Matrix C(f, c);
	C(1,1) = 1; C(1,2) =  2; C(1,3) = 8; C(1,4) = 0;
	C(2,1) = 2; C(2,2) = -1; C(2,3) = 0; C(2,4) = 0;
	C(3,1) = 3; C(3,2) =  1; C(3,3) = 0; C(3,4) = 5;
	
    _assert(m_equals(C, R, 1e-10));
    
    return 0;
}

int v_norm_01(){
	
	Matrix v(3);
	v(1)=0;v(2)=3;v(3)=4;
	
	_assert(abs(5 - norm(v)) < 1e-10);
	
	return 0;
}

int v_dot_01(){
	
	Matrix u(3);
	Matrix v(3);
	u(1)=0;u(2)=1;u(3)=2;
	v(1)=1;v(2)=2;v(3)=3;
	
	_assert(abs(8 - dot(u,v)) < 1e-10);
	
	return 0;
}

int v_cross_01(){
	
	Matrix u(3);
	Matrix v(3);
	u(1)=0;u(2)=1;u(3)=2;
	v(1)=1;v(2)=2;v(3)=3;
	
	Matrix R(3);
	R(1)=-1;R(2)=2;R(3)=-1;
	
    _assert(m_equals(cross(u,v), R, 1e-10));
	
	return 0;
}

int r_x_01(){
	
	double angle=5;
	Matrix A (3,3);
	A(1,1)=1;A(1,2)=0;A(1,3)=0;
	A(2,1)=0;A(2,2)=0.283662185463226;A(2,3)=-0.958924274663138;
	A(3,1)=0;A(3,2)=0.958924274663138;A(3,3)=0.283662185463226;
	
	_assert(m_equals(A, R_x(angle), 1e-10));
	
	return 0;
}

int r_y_01(){
	
	double angle=5;
	Matrix A (3,3);
	A(1,1)=0.283662185463226;A(1,2)=0;A(1,3)=0.958924274663138;
	A(2,1)=0;A(2,2)=1;A(2,3)=0;
	A(3,1)=-0.958924274663138;A(3,2)=0;A(3,3)=0.283662185463226;
	
	_assert(m_equals(A, R_y(angle), 1e-10));

	return 0;
}

int r_z_01(){
	
	double angle=5;
	Matrix A (3,3);
	A(1,1)=0.283662185463226;A(1,2)=-0.958924274663138;A(1,3)=0;
	A(2,1)=0.958924274663138;A(2,2)=0.283662185463226;A(2,3)=0;
	A(3,1)=0;A(3,2)=0;A(3,3)=1;
	
	_assert(m_equals(A, R_z(angle), 1e-10));

	return 0;
}

int accelpointmass_01(){
	
	Matrix u(3);
	Matrix v(3);
	u(1)=0;u(2)=1;u(3)=2;
	v(1)=4;v(2)=3;v(3)=2;
	double GM = 2;
	
	Matrix R(3);
	R(1)=0.0382164189132187;
	R(2)=0.00630163440991609;
	R(3)=-0.0256131500933865;
	
	Matrix B = AccelPointMass(u,v,GM);
	_assert(m_equals(R,B, 1e-10));
	
	return 0;
}

int cheb3d_01(){
	Matrix Cx(5);
	Matrix Cy(5);
	Matrix Cz(5);
	Cx(1)=1;Cx(2)=2;Cx(3)=3;Cx(4)=4;Cx(5)=5;
	Cy(1)=-1;Cy(2)=-2;Cy(3)=-3;Cy(4)=-4;Cy(5)=-5;
	Cz(1)=0;Cz(2)=1;Cz(3)=2;Cz(4)=3;Cz(5)=4;
	double t = 2;
	double N = 5;
	double Ta = 1;
	double Tb = 3;
	
	Matrix R(3);
	R(1)=3;R(2)=-3;R(3)=2;
	Matrix A = Cheb3D(t,N,Ta,Tb,Cx,Cy,Cz);
	_assert(m_equals(R,A, 1e-10));
	
	return 0;
}

int eccanom_01(){
	
	double M=2;
	double e=0.16;
	
	_assert(abs(2.13518640114338 - EccAnom(M,e)) < 1e-10);
	
	return 0;
}

int frac_01(){
	
	double x=1.123456;
	
	_assert(abs(0.123456 - Frac(x)) < 1e-10);
	
	return 0;
}

int meanobliquity_01(){
	
	double Mjd_TT=13;
		
	_assert(abs(0.409412989421167 - MeanObliquity(Mjd_TT)) < 1e-10);
	
	return 0;
}

int mjday_01(){
	
	_assert(abs(52890.2291666665 - Mjday(2003,9,8,5,30,0)) < 1e-10);
	
	return 0;
}

int mjday_02(){
	
	_assert(abs(52890 - Mjday(2003,9,8)) < 1e-10);
	
	return 0;
}

int mjday_tdb_01(){
	
	_assert(abs(58340.4456185067 - Mjday_TDB(58340.445618518)) < 1e-10);
	
	return 0;
}

int position_01(){
	double lat = 42.232583;
	double lon = -2.473639;
	double h = 841;
	
	Matrix R(3);
	R(1)=892407.685713797;
	R(2)=4934471.15708111;
	R(3)=-3929617.98430755;
	
	Matrix B = Position(lat,lon,h);
	
	_assert(m_equals(R,B, 1e-8));
	
	return 0;
}

int sign_01(){
	_assert(abs(-3-sign_(3,-1))<1e-10);
	return 0;
}

int timediff_01(){
	double t1 = 4.5;
	double t2 = 4.0;
	auto [UT1_TAI, UTC_GPS, UT1_GPS, TT_UTC, GPS_UTC] = timediff(t1,t2);
	
	
	double p = 1e-10;
	
	_assert(fabs(UT1_TAI-0.5) < p);
	_assert(fabs(UTC_GPS-15) < p);
	_assert(fabs(UT1_GPS-19.5) < p);
	_assert(fabs(TT_UTC-36.184) < p);
	_assert(fabs(GPS_UTC+15) < p);
	
	return 0;
}

int azelpa_01(){
	Matrix s(3);
	s(1)=1;s(2)=2;s(3)=3;
	
	auto [A1,A2,A3,A4] = AzElPa(s);
	Matrix B1(3);
	Matrix B2(3);
	B1(1)=0.4;B1(2)=-0.2;B1(3)=0;
	B2(1)=-0.095831484749991;B2(2)=-0.191662969499982;B2(3)=0.159719141249985;

	double p = 1e-10;
	_assert(fabs(A1-0.463647609000806) < p);
	_assert(fabs(A2-0.930274014115472) < p);
	_assert(m_equals(A3,B1, 1e-8));
	_assert(m_equals(A4,B2, 1e-8));

	
	return 0;
	
}

int legendre_01(){
	
	auto [A1,A2] = Legendre(2,2,1);
	Matrix B1(3,3);
	Matrix B2(3,3);
	B1(1,1)=1;B1(1,2)=0;B1(1,3)=0;
	B1(2,1)=1.4574704987823;B1(2,2)=0.935831045210238;B1(2,3)=0;
	B1(3,1)=1.25691645573063;B1(3,2)=1.76084689542256;B1(3,3)=0.565313394670859;
	
	B2(1,1)=0;B2(1,2)=0;B2(1,3)=0;
	B2(2,1)=0.935831045210238;B2(2,2)=-1.4574704987823;B2(2,3)=0;
	B2(3,1)=3.0498762872218;B2(3,2)=-1.61172976752398;B2(3,3)=-1.76084689542256;
	double p = 1e-10;
	_assert(m_equals(A1,B1, 1e-10));
	_assert(m_equals(A2,B2, 1e-10));

	
	return 0;
	
}

int timeupdate_01(){
	Matrix B(2,2);
	B(1,1)=13;B(1,2)=13;
	B(2,1)=13;B(2,2)=13;
	Matrix P(2,2);Matrix Phi(2,2);
	P(1,1)=1;P(1,2)=2;
	P(2,1)=1;P(2,2)=2;
	Phi(1,1)=2;Phi(1,2)=1;
	Phi(2,1)=2;Phi(2,2)=1;
	
	Matrix A = TimeUpdate(P,Phi,1);
	
	_assert(m_equals(A,B, 1e-10));

	return 0;
	
}

int timeupdate_02(){
	Matrix B(2,2);
	B(1,1)=12;B(1,2)=12;
	B(2,1)=12;B(2,2)=12;
	Matrix P(2,2);Matrix Phi(2,2);
	P(1,1)=1;P(1,2)=2;
	P(2,1)=1;P(2,2)=2;
	Phi(1,1)=2;Phi(1,2)=1;
	Phi(2,1)=2;Phi(2,2)=1;
	
	Matrix A = TimeUpdate(P,Phi);
	
	_assert(m_equals(A,B, 1e-10));

	return 0;
	
}

int nutangles_01(){
	
	auto [A1,A2] = NutAngles(2003);
	tuple<double,double> B = make_tuple(5.86599460508007e-05,-3.02393562601737e-05);
	
	double p = 1e-10;
	_assert(fabs(A1-5.86599460508007e-05) < p);
	_assert(fabs(A2+3.02393562601737e-05) < p);

	
	return 0;
	
}

int iers_01(){
	
	double Mjd_UTC=49746.1163541665;
	
	auto [A1,A2,A3,A4,A5,A6,A7,A8,A9] = IERS(*eopdata,Mjd_UTC,'l');
	
	double p = 1e-10;
	_assert(fabs(A1+5.5937872420407e-07) < p);
	_assert(fabs(A2-2.33559834147197e-06) < p);
	_assert(fabs(A3-0.325747632958709) < p);
	_assert(fabs(A4-0.00272698971874332) < p);
	_assert(fabs(A5+1.16882953161744e-07) < p);
	_assert(fabs(A6+2.4783506198648e-08) < p);
	_assert(fabs(A7+8.43027359626024e-10) < p);
	_assert(fabs(A8+1.56811369105037e-09) < p);
	_assert(fabs(A9-29) < p);
	return 0;
	
}

int nutmatrix_01(){
	
	Matrix A(3,3);
	A(1,1)=0.999999998279505;A(1,2)=-5.38122630785173e-05;A(1,3)=-2.3350152228722e-05;
	A(2,1)=5.38129691474857e-05;A(2,2)=0.999999998094892;A(2,3)=3.02387279850214e-05;
	A(3,1)=2.33485249698519e-05;A(3,2)=-3.02399844739898e-05;A(3,3)=0.999999999270195;
	
	Matrix B = NutMatrix(2003);
	
    _assert(m_equals(A, B, 1e-10));
	
	return 0;
}

int polematrix_01(){
	
	Matrix A(3,3);
	A(1,1)=0.907446781450196;A(1,2)=-0.0482287950799795;A(1,3)=0.417389892259999;
	A(2,1)=0;A(2,2)=0.993390379722272;A(2,3)=0.114784813783187;
	A(3,1)=-0.420167036826641;A(3,2)=-0.104161109826913;A(3,3)=0.901448902802564;
	
	Matrix B = PoleMatrix(13,69);
	
    _assert(m_equals(A, B, 1e-10));
	
	return 0;
}

int precmatrix_01(){
	
	Matrix A(3,3);
	A(1,1)=0.999999108990078;A(1,2)=0.00122404631636326;A(1,3)=0.000532662807124593;
	A(2,1)=-0.0012240463163649;A(2,2)=0.999999250854974;A(2,3)=-3.25999048523056e-07;
	A(3,1)=-0.000532662807120835;A(3,2)=-3.26005188870774e-07;A(3,3)=0.999999858135104;
	
	Matrix B = PrecMatrix(2003,2);
	
    _assert(m_equals(A, B, 1e-10));
	
	return 0;
}

int accelharmonic_01(){
	Matrix A(3,3);
	A(1,1)=1;A(1,2)=2;A(1,3)=3;
	A(2,1)=4;A(2,2)=5;A(2,3)=6;
	A(3,1)=7;A(3,2)=8;A(3,3)=9;
	
	Matrix B(3,1);
	B(1,1)=10000;B(2,1)=20000;B(3,1)=30000;
	Matrix ah = AccelHarmonic(B,A,1,2);
	Matrix C(3,1);
	C(1,1)=-8643.47675428564;C(2,1)=-10330.0088039024;C(3,1)=-12016.5408535191;
    _assert(m_equals(C, ah, 1e-10));
	
	return 0;
}

int eqnequinox_01(){
		
	double p = 1e-10;
	_assert(fabs(EqnEquinox(2003)-5.38122631093785e-05) < p);

	
	return 0;
	
}

int LTC_01(){
	Matrix A1=LTC(42.232583,-2.473639);
	
	Matrix B1(3,3);
	B1(1,1)=0.984036858261639;B1(1,2)=-0.177964776241149;B1(1,3)=0;
	B1(2,1)=-0.110227950763158;B1(2,2)=-0.609493455124053;B1(2,3)=-0.785090776300103;
	B1(3,1)=0.139718504333238;B1(3,2)=0.772558260960545;B1(3,3)=-0.61938071730439;

	_assert(m_equals(A1,B1, 1e-10));

	
	return 0;
	
}

int gmst_01(){
	
	double p = 1e-10;
	_assert(fabs(gmst(2003)-4.01447257055521) < p);

	
	return 0;
	
}

int jpl_eph_de430_01(){
	
	auto [r_Mercury,r_Venus,r_Earth,r_Mars,r_Jupiter,r_Saturn,r_Uranus,r_Neptune,r_Pluto,r_Moon,r_Sun] = JPL_Eph_DE430(49746.1);
	Matrix B1(3,1);
	B1(1,1)=83810666211.6714;B1(2,1)=-65300253562.273;B1(3,1)=-23400591423.1512;
	
	Matrix B2(3,1);
	B2(1,1)=-15254871090.737;B2(2,1)=-110119619839.499;B2(3,1)=-41014557782.1451;
	
	Matrix B3(3,1);
	B3(1,1)=-92446370466.6615;B3(2,1)=106412761987.887;B3(3,1)=46137876551.2218;
	
	Matrix B4(3,1);
	B4(1,1)=-88286755974.9184;B4(2,1)=46961779170.9088;B4(3,1)=29069662998.0302;
	
	Matrix B5(3,1);
	B5(1,1)=-298422178337.688;B5(2,1)=-754510732235.042;B5(3,1)=-314415669431.536;
	
	Matrix B6(3,1);
	B6(1,1)=1482007182963.1;B6(2,1)=-453899645892.782;B6(3,1)=-249413567763.422;
	
	Matrix B7(3,1);
	B7(1,1)=1412337137361.43;B7(2,1)=-2511375518242.91;B7(3,1)=-1118117451413.37;
	
	Matrix B8(3,1);
	B8(1,1)=1871221039794.16;B8(2,1)=-3928996288702.76;B8(3,1)=-1655028957852.41;
	
	Matrix B9(3,1);
	B9(1,1)=-2171444383702.46;B9(2,1)=-3915447988031.43;B9(3,1)=-552721549757.353;
	
	Matrix B10(3,1);
	B10(1,1)=88301268.8063318;B10(2,1)=-336822619.971717;B10(3,1)=-114792187.645337;
	
	Matrix B11(3,1);
	B11(1,1)=92273673176.1919;B11(2,1)=-105393042175.493;B11(3,1)=-45694105289.8874;
	double p = 1e-2;
	_assert(m_equals(r_Mercury,B1, p));
	_assert(m_equals(r_Venus,B2, p));
	_assert(m_equals(r_Earth,B3, p));
	_assert(m_equals(r_Mars,B4, p));
	_assert(m_equals(r_Jupiter,B5, p));
	_assert(m_equals(r_Saturn,B6, p));
	_assert(m_equals(r_Uranus,B7, p));
	_assert(m_equals(r_Neptune,B8, p));
	_assert(m_equals(r_Pluto,B9, p));
	_assert(m_equals(r_Moon,B10, p));
	_assert(m_equals(r_Sun,B11, p));

	
	return 0;
	
}

int geodetic_01(){
	
	Matrix r(3);
	r(1)=100000;r(2)=10000;r(3)=200000;
	
	auto [A1,A2,A3] = Geodetic(r);
	double p = 1e-5;
	_assert(fabs(A1-0.099668652491162) < p);
	_assert(fabs(A2-1.17346835589897) < p);
	_assert(fabs(A3+6136649.99543401) < 1e-3);
	return 0;
	
}

int angl_01(){
	
	Matrix u(3);
	u(1)=1;u(2)=2;u(3)=3;
	
	Matrix v(3);
	v(1)=3;v(2)=2;v(3)=1;
	
	double theta = angl(u,v);
	double p = 1e-10;
	_assert(fabs(theta-0.775193373310361) < p);
	return 0;
	
}

int elements_01(){
	
	Matrix y(6);
	y(1)=1;y(2)=2;y(3)=3;y(4)=4;y(5)=5;y(6)=6;
	
	auto [A1,A2,A3,A4,A5,A6,A7] = elements(y);
	
	double p = 1e-10;
	_assert(fabs(A1-1.35474011564823e-13) < p);
	_assert(fabs(A2-1.87082869338765) < p);
	_assert(fabs(A3-0.999999999999964) < p);
	_assert(fabs(A4-1.99133066207886) < p);
	_assert(fabs(A5-3.6052402625906) < p);
	_assert(fabs(A6-5.21086941752228) < p);
	_assert(fabs(A7-3.14159030993265) < p);
	return 0;
	
}

int unit_01(){
	Matrix A(3);
	A(1)=1;A(2)=2;A(3)=3;
	
	Matrix B(3);
	B(1)=0.267261241912424;B(2)=0.534522483824849;B(3)=0.801783725737273;
	Matrix C = unit(A);

    _assert(m_equals(C, B, 1e-10));
	
	return 0;
}

int gibbs_01(){
	
	Matrix r1(3);
	Matrix r2(3);
	Matrix r3(3);
	r1(1)=5720303.71012986;r1(2)=3152426.6965331;r1(3)=3750056.80416402;
	r2(1)=6221397.62857869;r2(2)=2867713.77965738;r2(3)=3006155.98509949;
	r3(1)=6699811.80976796;r3(2)=2569867.80763881;r3(3)=2154940.29542389;
	
	auto [v2, theta,theta1,copa, error] = gibbs(r1,r2,r3);
	Matrix B1(3);
	B1(1)=4645.04725161805;B1(2)=-2752.21591588211;B1(3)=-7507.99940987023;
	
	double p = 1e-10;
	_assert(m_equals(v2,B1, 1e-10));
	_assert(fabs(theta-0.125269502872995) < p);
	_assert(fabs(theta1-0.136454013492469) < p);
	_assert(fabs(copa-0.00509723347775616) < p);
	_assert(error.compare("ok")==0);
	return 0;
	
}

int hgibbs_01(){
	
	Matrix r1(3);
	Matrix r2(3);
	Matrix r3(3);
	r1(1)=5720303.71012986;r1(2)=3152426.6965331;r1(3)=3750056.80416402;
	r2(1)=6221397.62857869;r2(2)=2867713.77965738;r2(3)=3006155.98509949;
	r3(1)=6699811.80976796;r3(2)=2569867.80763881;r3(3)=2154940.29542389;
	
	auto [v2, theta,theta1,copa, error] = hgibbs(r1,r2,r3,41245,41246,41247);
	Matrix B1(3);
	B1(1)=7293.91989172759;B1(2)=-3645.40701546474;B1(3)=-10497.4139772076;
	
	double p = 1e-10;
	_assert(m_equals(v2,B1, 1e-10));
	_assert(fabs(theta-0.125269502872995) < p);
	_assert(fabs(theta1-0.136454013492469) < p);
	_assert(fabs(copa-0.00509723347775616) < p);
	_assert(error.compare("angl > 1ø")==0);
	return 0;
	
}

int anglesg_01(){
	
	Matrix Rs(3,1);
	Rs(1,1)=-5512567.84003607;
	Rs(2,1)=-2196994.44666933;
	Rs(3,1)=2330804.96614689;
	Matrix Rs2(3,1);
	Rs2(1,1)=-5512567.84003607;
	Rs2(2,1)=-2196994.44666933;
	Rs2(3,1)=2330804.96614689;
	Matrix Rs3(3,1);
	Rs3(1,1)=-5512567.84003607;
	Rs3(2,1)=-2196994.44666933;
	Rs3(3,1)=2330804.96614689;
	auto [A1,A2] = anglesg(1.0559084894933,1.36310214580757,1.97615602688759,0.282624656433946,0.453434794338875,0.586427138011591,4.974611015046295e+04,4.974611128472211e+04,4.974611253472231e+04,Rs,Rs2,Rs3);
	Matrix B1(3,1);
	Matrix B2(3,1);
	B1(1,1)=6221397.62857869;
	B1(2,1)=2867713.77965738;
	B1(3,1)=3006155.98509949;
	
	B2(1,1)=4645.04725161806;
	B2(2,1)=-2752.21591588204;
	B2(3,1)=-7507.99940987031;
	double p = 1e-5;
	_assert(m_equals(A1,B1, p));
	_assert(m_equals(A2,B2, p));

	
	return 0;
	
}

int rpoly_01(){
	
	double coef[10], zeror[10], zeroi[10];
    int i, nr, degree;
    
    coef[0] = 1.0;
    coef[1] = 0.0;
    coef[2] = -73120740632072.03125;
    coef[3] = 0.0;
    coef[4] = 0.0;
    coef[5] = -1587936795676375129762729592392515584.0;
    coef[6] = 0.0;
    coef[7] = 0.0;
    coef[8] = -11985384853690913913633237309023581769694874388537465110528.0;
    degree =8;
    
    nr = real_poly_roots(coef, degree, zeror, zeroi);
	
	double p=1e-10;
	
	_assert(fabs(nr-8) < p);
	_assert(fabs(zeror[0]-20488505.59583731740713119507) < p);
	_assert(fabs(zeror[1]+16734286.96763427741825580597) < p);
	_assert(fabs(zeror[2]+14960114.44405406899750232697) < p);
	_assert(fabs(zeror[3]+14960114.44405406899750232697) < p);
	_assert(fabs(zeror[4]-11333954.31939544528722763062) < p);
	_assert(fabs(zeror[5]-11333954.31939544528722763062) < p);
	_assert(fabs(zeror[6]-1749050.81055710464715957642) < p);
	_assert(fabs(zeror[7]-1749050.81055710464715957642) < p);
	_assert(fabs(zeroi[0]-0) < p);
	_assert(fabs(zeroi[1]-0) < p);
	_assert(fabs(zeroi[2]-12499576.43868194520473480225) < p);
	_assert(fabs(zeroi[3]+12499576.43868194520473480225) < p);
	_assert(fabs(zeroi[4]-12628091.67192456685006618500) < p);
	_assert(fabs(zeroi[5]+12628091.67192456685006618500) < p);
	_assert(fabs(zeroi[6]-17787677.85044153779745101929) < p);
	_assert(fabs(zeroi[7]+17787677.85044153779745101929) < p);
	return 0;
}

int gast_01(){
	
	double p = 1e-10;
	_assert(fabs(gast(41254.4)-3.17743554317744) < p);

	
	return 0;
	
}

int measupdate_01(){
	
	Matrix x(6,1);
	x(1,1)=5738566.5776918;
	x(2,1)=3123975.34092958;
	x(3,1)=3727114.48156063;
	x(4,1)=5199.63329181124;
	x(5,1)=-2474.43881044665;
	x(6,1)=-7195.16752553892;
	Matrix dAdY(6);
	dAdY(1)=9.59123748602946e-08;
	dAdY(2)=2.16050345227544e-07;
	dAdY(3)=-3.27382770920699e-07;
	dAdY(4)=0;
	dAdY(5)=0;
	dAdY(6)=0;
	Matrix P(6,6);
	P(1,1)=101453348.207942;P(1,2)=120429.109483243;P(1,3)=148186.144985839;P(1,4)=39372.9209837664;P(1,5)=3284.2167520673;P(1,6)=4014.15727991751;
	P(2,1)=120429.109483243;P(2,2)=101309543.076861;P(2,3)=84141.6477884862;P(2,4)=3284.34773339132;P(2,5)=35369.9224490354;P(2,6)=2255.66799464957;
	P(3,1)=148186.144985839;P(3,2)=84141.6477884862;P(3,3)=101344434.103677;P(3,4)=4014.41933388835;P(3,5)=2255.725324827;P(3,6)=36274.7873567435;
	P(4,1)=39372.9209837664;P(4,2)=3284.34773339132;P(4,3)=4014.41933388835;P(4,4)=1001.21615369407;P(4,5)=1.32096249080649;P(4,6)=1.60455481117521;
	P(5,1)=3284.2167520673;P(5,2)=35369.9224490354;P(5,3)=2255.725324827;P(5,4)=1.32096249080649;P(5,5)=999.57682959713;P(5,6)=0.892927375062725;
	P(6,1)=4014.15727991751;P(6,2)=2255.66799464957;P(6,3)=36274.7873567435;P(6,4)=1.60455481117521;P(6,5)=0.892927375062725;P(6,6)=999.924178045879;
	auto [A1,A2,A3] = MeasUpdate(x,1.0559084894933,1.1,0.0,dAdY,P,6);
	Matrix B1(6,1);
	Matrix B2(6,1);
	Matrix B3(6,6);
	B1(1,1)=588086.242773885;
	B1(2,1)=1324930.06616326;
	B1(3,1)=-2007874.91591972;
	B1(4,1)=192.129885123686;
	B1(5,1)=437.253977706858;
	B1(6,1)=-666.548640643429;
	
	B2(1,1)=5712636.96693969;
	B2(2,1)=3065557.1729967;
	B2(3,1)=3815644.71951204;
	B2(4,1)=5191.16199496266;
	B2(5,1)=-2493.71799879881;
	B2(6,1)=-7165.77838914676;

	B3(1,1)=95744126.5575462;B3(1,2)=-12742173.122666;B3(1,3)=19640910.3535729;B3(1,4)=37507.697790205;B3(1,5)=-960.704646656044;B3(1,6)=10485.1026165295;
	B3(2,1)=-12742173.122666;B3(2,2)=72330717.8860365;B3(2,3)=44000313.2854161;B3(2,4)=-917.910557157902;B3(2,5)=25806.3183709328;B3(2,6)=16834.3971152909;
	B3(3,1)=19640910.3535729;B3(3,2)=44000313.2854161;B3(3,3)=34791352.0306252;B3(3,4)=10382.762258012;B3(3,5)=16748.9587600199;B3(3,6)=14181.3461594349;
	B3(4,1)=37507.697790205;B3(4,2)=-917.910557157902;B3(4,3)=10382.762258012;B3(4,4)=1000.60677858572;B3(4,5)=-0.0658685577296619;B3(4,6)=3.71863586551292;
	B3(5,1)=-960.704646656043;B3(5,2)=25806.3183709328;B3(5,3)=16748.9587600199;B3(5,4)=-0.0658685577296616;B3(5,5)=996.420644956779;B3(5,6)=5.70420569133708;
	B3(6,1)=10485.1026165295;B3(6,2)=16834.3971152909;B3(6,3)=14181.3461594349;B3(6,4)=3.71863586551292;B3(6,5)=5.70420569133708;B3(6,6)=992.589879937744;
	
	double p = 1e-5;
	_assert(m_equals(A1,B1, p));
	_assert(m_equals(A2,B2, p));
	_assert(m_equals(A3,B3, p));
	
	return 0;
	
}

int g_accelharmonic_01(){
	
	Matrix r(3,1);
	r(1,1)=7101800.90695315;
	r(2,1)=1293997.58115302;
	r(3,1)=10114.014948955;
	
	Matrix U(3,3);
	U(1,1)=-0.984320311904791;U(1,2)=0.17638970840918;U(1,3)=-0.000440838949610109;
    U(2,1)=-0.176389673507182;U(2,2)=-0.984320409906027;U(2,3)=-0.000117142904888635;
    U(3,1)=-0.000454589578418276;U(3,2)=-3.75467022865179e-05;U(3,3)=0.999999895969275;
	Matrix C = G_AccelHarmonic(r,U,20,20);
	
	Matrix D(3,3);
	D(1,1)=2.02233500257165e-06;D(1,2)=5.61803303433805e-07;D(1,3)=4.39856240319614e-09;
    D(2,1)=5.61803301435404e-07;D(2,2)=-9.58631634517815e-07;D(2,3)=8.05634892131479e-10;
    D(3,1)=4.39855909334375e-09;D(3,2)=8.0563404905587e-10;D(3,3)=-1.06370336962723e-06;

    _assert(m_equals(C,D, 1e-10));
	
	return 0;
}

int ghamatrix_01(){
	
	Matrix A(3,3);
	A(1,1)=-0.893257956965228;A(1,2)=-0.449544460891586;A(1,3)=0;
	A(2,1)=0.449544460891586;A(2,2)=-0.893257956965228;A(2,3)=0;
	A(3,1)=0;A(3,2)=0;A(3,3)=1;
	
	Matrix B = GHAMatrix(42156);
	
    _assert(m_equals(A, B, 1e-10));
	
	return 0;
}

int accel_01(){
	
	Matrix x(6,1);
	x(1,1)=5719063.64288367;
	x(2,1)=2685081.89956799;
	x(3,1)=3463067.36712468;
	x(4,1)=4582.55994448408;
	x(5,1)=-2068.24606125433;
	x(6,1)=-5764.11300483978;
	
	Matrix B1(6,1);
	B1(1,1)=4582.55994448408;
	B1(2,1)=-2068.24606125433;
	B1(3,1)=-5764.11300483978;
	B1(4,1)=-6.09382659543918;
	B1(5,1)=-2.86111011839987;
	B1(6,1)=-3.69945067085889;
	
	Matrix B = Accel(-538.671863984076,x);
	
    _assert(m_equals(B1, B, 1e-6));
	
	return 0;
}

int vareqn_01(){
	
	Matrix A(42);
	A(1) = 7055540.55303718;
	A(2) = 1392009.04833565;
	A(3) = 184573.002856935;
	A(4) = 518.721490311643;
	A(5) = -2937.21745577442;
	A(6) = -6728.72802360915;
	A(7) = 1.0002223217216;
	A(8) = 6.86235834619309e-05;
	A(9) = 1.21812212859873e-05;
	A(10) = 2.99701272514737e-05;
	A(11) = 9.19881572688816e-06;
	A(12) = 1.53232965333811e-06;
	A(13) = 6.86236343320243e-05;
	A(14) = 0.999895694596537;
	A(15) = 2.45685044112465e-06;
	A(16) = 9.1988330389348e-06;
	A(17) = -1.40664565971499e-05;
	A(18) = 3.07556007371378e-07;
	A(19) = 1.21813347518041e-05;
	A(20) = 2.45687151803192e-06;
	A(21) = 0.99988199767632;
	A(22) = 1.53236839176295e-06;
	A(23) = 3.07563200573812e-07;
	A(24) = -1.58999009076755e-05;
	A(25) = 14.8543040485214;
	A(26) = 0.000338231852367611;
	A(27) = 5.63459026135203e-05;
	A(28) = 1.00022281252919;
	A(29) = 6.80056651496741e-05;
	A(30) = 1.05785031871047e-05;
	A(31) = 0.000338231973190712;
	A(32) = 14.8526848707458;
	A(33) = 1.1303467405304e-05;
	A(34) = 6.80057155518227e-05;
	A(35) = 0.999895368284792;
	A(36) = 2.11128285949748e-06;
	A(37) = 5.63461718187475e-05;
	A(38) = 1.13035175318208e-05;
	A(39) = 14.852617446191;
	A(40) = 1.05786166037029e-05;
	A(41) = 2.11130393255509e-06;
	A(42) = 0.999881833188252;

	
	Matrix B(42);
	B(1) = 518.721490311643;
	B(2) = -2937.21745577442;
	B(3) = -6728.72802360915;
	B(4) = -7.56359746310245;
	B(5) = -1.49227955822348;
	B(6) = -0.198376820490144;
	B(7) = 2.99701272514737e-05;
	B(8) = 9.19881572688816e-06;
	B(9) = 1.53232965333811e-06;
	B(10) = 2.02464591490892e-06;
	B(11) = 6.10925486559748e-07;
	B(12) = 8.13444920874581e-08;
	B(13) = 9.1988330389348e-06;
	B(14) = -1.40664565971499e-05;
	B(15) = 3.07556007371378e-07;
	B(16) = 6.10930169208707e-07;
	B(17) = -9.51364673492224e-07;
	B(18) = 1.6048947508729e-08;
	B(19) = 1.53236839176295e-06;
	B(20) = 3.07563200573812e-07;
	B(21) = -1.58999009076755e-05;
	B(22) = 8.13549311536726e-08;
	B(23) = 1.60508843805756e-08;
	B(24) = -1.07251950690499e-06;
	B(25) = 1.00022281252919;
	B(26) = 6.80056651496741e-05;
	B(27) = 1.05785031871047e-05;
	B(28) = 3.00675951758311e-05;
	B(29) = 9.07350171420114e-06;
	B(30) = 1.20816992236255e-06;
	B(31) = 6.80057155518227e-05;
	B(32) = 0.999895368284792;
	B(33) = 2.11128285949748e-06;
	B(34) = 9.07351910316192e-06;
	B(35) = -1.41322101843878e-05;
	B(36) = 2.38366445794881e-07;
	B(37) = 1.05786166037029e-05;
	B(38) = 2.11130393255509e-06;
	B(39) = 0.999881833188252;
	B(40) = 1.20820867505632e-06;
	B(41) = 2.38373637847664e-07;
	B(42) = -1.59316124447033e-05;

	
	Matrix C = VarEqn(14.8532021081661,A);
	
    _assert(m_equals(transpose(C), B, 1e-10));
	
	return 0;
}

int deinteg_01(){
	
	AuxParam.Mjd_UTC=4.974611128472211e+04;
	Matrix Y0_apr(6,1);
	Y0_apr(1,1)=6221397.628578685;
	Y0_apr(2,1)=2867713.779657379;
	Y0_apr(3,1)=3006155.985099489;
	Y0_apr(4,1)=4645.047251618060;
	Y0_apr(5,1)=-2752.215915882042;
	Y0_apr(6,1)=-7507.999409870306;
	
	Matrix B1(6,1);
	B1(1,1)=5542555.937228607;
	B1(2,1)=3213514.867349196;
	B1(3,1)=3990892.975876853;
	B1(4,1)=5394.068421663513;
	B1(5,1)=-2365.213378823415;
	B1(6,1)=-7061.845542002954;
	
	double aa = -134.9999919533730;
	
	Matrix B = DEInteg(Accel,0.0,aa,1e-13,1e-6,6,Y0_apr);
    _assert(m_equals(transpose(B1), B, 1e-7));
	
	return 0;
}

int all_tests()
{
	eop19620101(21413);
	GGM03S();
	DE430Coeff();
	cargarAuxParam();
    _verify(m_sum_01);
    _verify(m_sub_01);
	_verify(m_mul_01);
	_verify(m_div_01);
	_verify(m_asig_01);
    _verify(m_zeros_01);
	_verify(v_zeros_01);
	_verify(m_eye_01);
	_verify(m_transpose_01);
	_verify(m_inv_01);
	_verify(m_determinante_01);
	_verify(m_submatriz_01);
	_verify(m_sumdouble_01);
	_verify(m_subdouble_01);
	_verify(m_muldouble_01);
	_verify(m_divdouble_01);
	_verify(m_extractvec_01);
	_verify(m_unionvec_01);
	_verify(m_extractrow_01);
	_verify(m_extractcol_01);
	_verify(m_assignrow_01);
	_verify(m_assigncol_01);
	_verify(v_norm_01);
	_verify(v_dot_01);
	_verify(v_cross_01);
	
	_verify(r_x_01);
	_verify(r_y_01);
	_verify(r_z_01);
	_verify(accelpointmass_01);
	_verify(cheb3d_01);
	_verify(eccanom_01);
	_verify(frac_01);
	_verify(meanobliquity_01);
	_verify(mjday_01);
	_verify(mjday_02);
	_verify(mjday_tdb_01);
	_verify(position_01);
	_verify(sign_01);
	_verify(timediff_01);
	_verify(azelpa_01);
	_verify(legendre_01);
	_verify(timeupdate_01);
	_verify(timeupdate_02);
	_verify(nutangles_01);
	_verify(iers_01);

	_verify(nutmatrix_01);
	_verify(polematrix_01);
	_verify(precmatrix_01);
	_verify(accelharmonic_01);
	_verify(eqnequinox_01);
	_verify(LTC_01);
	_verify(gmst_01);
	_verify(jpl_eph_de430_01);
	
	_verify(gast_01);
	_verify(measupdate_01);
	_verify(g_accelharmonic_01);
	_verify(ghamatrix_01);	
	_verify(accel_01);	
	_verify(vareqn_01);
	
	_verify(deinteg_01);
	
	_verify(geodetic_01);
	_verify(angl_01);
	_verify(elements_01);
	_verify(unit_01);
	_verify(gibbs_01);
	_verify(hgibbs_01);
	_verify(anglesg_01);
	_verify(rpoly_01);

    return 0;
}


int main()
{
    int result = all_tests();

    if (result == 0)
        printf("PASSED\n");

    printf("Tests run: %d\n", tests_run);
    return result != 0;
}
