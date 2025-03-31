// $Source$
//----------------------------------------------------------------------
// Matrix
//----------------------------------------------------------------------
// Proyecto TT1
//
/**@file matrix.cpp
*	@brief Representación de una matriz.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\matrix.h"

Matrix::Matrix(const int n_row, const int n_column) {
    if (n_row <= 0 || n_column <= 0) {
		cout << "Matrix create: error in n_row/n_column\n";
        exit(EXIT_FAILURE);
	}
	
	this->n_row = n_row;
	this->n_column = n_column;
	this->data = (double **) malloc(n_row*sizeof(double *));
	
    if (this->data == NULL) {
		cout << "Matrix create: error in data\n";
        exit(EXIT_FAILURE);
	}
	
	for(int i = 0; i < n_row; i++) {
		this->data[i] = (double *) malloc(n_column*sizeof(double));
	}
}

double& Matrix::operator () (const int row, const int column) {
	if (row <= 0 || row > this->n_row || column <= 0 || column > this->n_column) {
		cout << "Matrix get: error in row/column\n";
        exit(EXIT_FAILURE);
	}
	
	return this->data[row - 1][column - 1];
}

Matrix& Matrix::operator + (Matrix &m) {
	if (this->n_row != m.n_row || this->n_column != m.n_column) {
		cout << "Matrix sum: error in n_row/n_column\n";
        exit(EXIT_FAILURE);
	}
	
	Matrix *m_aux = new Matrix(this->n_row, this->n_column);
	
    for(int i = 1; i <= this->n_row; i++) {
        for(int j = 1; j <= this->n_column; j++) {
			(*m_aux)(i,j) = (*this)(i,j) + m(i,j);
		}
	}
	
	return *m_aux;
}

Matrix& Matrix::operator - (Matrix &m) {
	if (this->n_row != m.n_row || this->n_column != m.n_column) {
		cout << "Matrix sub: error in n_row/n_column\n";
        exit(EXIT_FAILURE);
	}
	
	Matrix *m_aux = new Matrix(this->n_row, this->n_column);
	
    for(int i = 1; i <= this->n_row; i++) {
        for(int j = 1; j <= this->n_column; j++) {
			(*m_aux)(i,j) = (*this)(i,j) - m(i,j);
		}
	}
	
	return *m_aux;
}

Matrix& Matrix::operator * (Matrix &m){
	if (this->n_column != m.n_row) {
		cout << "Matrix sub: error in n_row/n_column\n";
        exit(EXIT_FAILURE);
	}
	Matrix *m_aux = new Matrix(this->n_row, m.n_column);
		for(int i = 1; i <= this->n_row; i++) {
        for(int j = 1; j <= m.n_column; j++) {
			double mij=0;
			for(int k=1; k<=this->n_column; k++){
				mij+=(*this) (i,k) * m(k,j);
			}
			(*m_aux)(i,j) = mij;
		}
	}
	
	return *m_aux;
}

Matrix& Matrix::operator / (Matrix &m){
	if (this->n_row != m.n_row) {
		cout << "Matrix sub: error in n_row/n_column\n";
        exit(EXIT_FAILURE);
	}
	return (*this)*inv(m);
}

Matrix& Matrix::operator = (Matrix &m){
	Matrix *m_aux = new Matrix(m.n_row, m.n_column);
		for(int i = 1; i <= this->n_row; i++) {
        for(int j = 1; j <= m.n_column; j++) {
			(*m_aux)(i,j) = m(i,j);
		}
	}
	
	return *m_aux;
}

Matrix& Matrix::operator + (double n) {

	Matrix *m_aux = new Matrix(this->n_row, this->n_column);
	
    for(int i = 1; i <= this->n_row; i++) {
        for(int j = 1; j <= this->n_column; j++) {
			(*m_aux)(i,j) = (*this)(i,j) + n;
		}
	}
	
	return *m_aux;
}

Matrix& Matrix::operator - (double n) {

	Matrix *m_aux = new Matrix(this->n_row, this->n_column);
	
    for(int i = 1; i <= this->n_row; i++) {
        for(int j = 1; j <= this->n_column; j++) {
			(*m_aux)(i,j) = (*this)(i,j) - n;
		}
	}
	
	return *m_aux;
}

Matrix& Matrix::operator * (double n) {

	Matrix *m_aux = new Matrix(this->n_row, this->n_column);
	
    for(int i = 1; i <= this->n_row; i++) {
        for(int j = 1; j <= this->n_column; j++) {
			(*m_aux)(i,j) = (*this)(i,j) * n;
		}
	}
	
	return *m_aux;
}

Matrix& Matrix::operator / (double n) {
	
	if(abs(n)<1e-10){
		cout << "Double error, cannot divide by zero\n";
        exit(EXIT_FAILURE);
	}
	Matrix *m_aux = new Matrix(this->n_row, this->n_column);
	
    for(int i = 1; i <= this->n_row; i++) {
        for(int j = 1; j <= this->n_column; j++) {
			(*m_aux)(i,j) = (*this)(i,j) / n;
		}
	}
	
	return *m_aux;
}

ostream& operator << (ostream &o, Matrix &m) {
	for (int i = 1; i <= m.n_row; i++) {
        for (int j = 1; j <= m.n_column; j++)
			printf("%5.20lf ", m(i,j));
        o << "\n";
    }
	
    return o;
}

Matrix& zeros(const int n_row, const int n_column) {
	Matrix *m_aux = new Matrix(n_row, n_column);
	
	for(int i = 1; i <= n_row; i++) {
		for(int j = 1; j <= n_column; j++) {
			(*m_aux)(i,j) = 0;
		}
	}
	
	return (*m_aux);
}

Matrix& eye(const int n_row){
	Matrix *m_aux = new Matrix(n_row, n_row);
	
	for(int i = 1; i <= n_row; i++) {
		for(int j = 1; j <= n_row; j++) {
			if(i==j){
				(*m_aux)(i,j) = 1;
			}
			else{
				(*m_aux)(i,j) = 0;
			}
		}
	}
	
	return (*m_aux);
}

Matrix& transpose(Matrix &m){
	Matrix *m_aux = new Matrix(m.n_column, m.n_row);
	
	for(int i = 1; i <= m.n_row; i++) {
		for(int j = 1; j <= m.n_column; j++) {
			(*m_aux)(j,i) = m(i,j);
		}
	}
	
	return (*m_aux);
}

Matrix& inv(Matrix &m){
	if(m.n_row!=m.n_column){
		cout << "Matrix sub: error in n_row/n_column\n";
        exit(EXIT_FAILURE);
	}
	double det=determinante(m);

	if(abs(det)<1e-10){
		cout << "Matrix sub: error in determinant\n";
        exit(EXIT_FAILURE);
	}
	Matrix m_cofactor(m.n_row, m.n_column);
	
	for(int i = 1; i <= m_cofactor.n_row; i++) {
		for(int j = 1; j <= m_cofactor.n_column; j++) {
			double cij=determinante(submatriz(m,i,j));
			double signo = ((i+j)%2 ==0)? 1:-1;
			m_cofactor(i,j) = signo*cij;
		}
	}
	Matrix conjugada = transpose(m_cofactor);

	for(int i = 1; i <= conjugada.n_row; i++) {
		for(int j = 1; j <= conjugada.n_column; j++) {
			conjugada(i,j)/=det;
		}
	}
	Matrix *m_aux=new Matrix(conjugada.n_row,conjugada.n_column);
	
	for(int i = 1; i <= conjugada.n_row; i++) {
		for(int j = 1; j <= conjugada.n_column; j++) {
			(*m_aux)(i,j)=conjugada(i,j);
		}
	}
	
	return (*m_aux);
}

double determinante(Matrix &m){
	if (m.n_row!=m.n_column) {
		cout << "Matrix sub: error in n_row/n_column\n";
        exit(EXIT_FAILURE);cout << "Matrix sub: error in n_row/n_column\n";
        exit(EXIT_FAILURE);
	}
	if(m.n_row==2){
		return m(1,1)*m(2,2)-m(1,2)*m(2,1);
	}
	else{
		double det=0;
		int i=1;
		for(int j=1;j<=m.n_row;j++){
			double signo = ((i+j)%2 ==0)? 1:-1;
			det+=signo*m(i,j)*determinante(submatriz(m,i,j));
		}
		return det;
	}
}

Matrix& submatriz(Matrix &m, int i, int j){
	if(i>m.n_row||j>m.n_column){
		cout<<"Matrix sub: error in n_row/n_column\n";
		exit(EXIT_FAILURE);
	}
	Matrix *m_aux = new Matrix(m.n_row-1, m.n_column-1);
	for(int a=1;a<=m.n_row;a++){
		if(a!=i){
			for(int b=1;b<=m.n_column;b++){
				if(b!=j){
					double r=a;double c=b;
					if(r>i) r--;if(c>j) c--;
					(*m_aux)(r,c) = m(a,b);
				}
			}
		}
	}

	return (*m_aux);
}