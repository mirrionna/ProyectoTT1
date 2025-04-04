// $Source$
//----------------------------------------------------------------------
// tests
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file test.cpp
*	@brief Tests unitarios para los métodos del proyecto de TTI.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\matrix.h"
#include <cstdio>
#include <cmath>

int tests_run = 0;

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

int m_extractrow_01(){
	int f = 3;
    int c = 4;
	
	Matrix A(f, c);
	A(1,1) = 0; A(1,2) =  2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) =  1; A(3,3) = 0; A(3,4) = 5;
	
	Matrix B(1, c);
	B(1,1) = 0; B(1,2) =  2; B(1,3) = 8; B(1,4) = 0;
	
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
	
	Matrix B(f, 1);
	B(1,1) = 0;
	B(2,1) = 1;
	B(3,1) = 0;
	
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
	
	Matrix B(1, c);
	B(1,1) = 1; B(1,2) =  2; B(1,3) = 3; B(1,4) = 4;
	
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
	
	Matrix B(f, 1);
	B(1,1) = 1;
	B(2,1) = 2;
	B(3,1) = 3;
	
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
	_verify(m_extractrow_01);
	_verify(m_extractcol_01);
	_verify(m_assignrow_01);
	_verify(m_assigncol_01);
	_verify(v_norm_01);
	_verify(v_dot_01);
	_verify(v_cross_01);
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
