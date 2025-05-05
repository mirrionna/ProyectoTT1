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

#include "..\include\global.hpp"

#include <cstdio>
#include <cmath>
#include <tuple>
int tests_run = 0;

using namespace std;

#define FAIL() printf("\nfailure in %s() line %d\n", __func__, __LINE__)
#define _assert(test) do { if (!(test)) { FAIL(); return 1; } } while(0)
#define _verify(test) do { int r=test(); tests_run++; if(r) return r; } while(0)


int m_equals(Matrix A, Matrix B, double p) {
	if (A.n_row != B.n_row || A.n_column != B.n_column)
		return 0;
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

int all_tests()
{
	eop19620101(21413);
	GGM03S();
	DE430Coeff();
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
