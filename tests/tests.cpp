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
	
	cout<<"REVISAR POSITION, fallo de precision\n";

	return 0;
}

int sign_01(){
	_assert(abs(-3-sign_(3,-1))<1e-10);
	return 0;
}

int timediff_01(){
	double t1 = 4.5;
	double t2 = 4.0;
	tuple<double,double,double,double,double> A = timediff(t1,t2);
	
	tuple<double,double,double,double,double> B = make_tuple(0.5,15,19.5,36.184,-15);
	
	double p = 1e-10;
	
	_assert(fabs(get<0>(A)-get<0>(B)) < p);
	_assert(fabs(get<1>(A)-get<1>(B)) < p);
	_assert(fabs(get<2>(A)-get<2>(B)) < p);
	_assert(fabs(get<3>(A)-get<3>(B)) < p);
	_assert(fabs(get<4>(A)-get<4>(B)) < p);
	
	return 0;
}

int all_tests()
{
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
