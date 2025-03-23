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
	if (m.n_row!=3 || m.n_column!=3) {
		cout << "Matrix sub: error in n_row/n_column\n";
        exit(EXIT_FAILURE);
	}
	double A = m(2,2)*m(3,3)-m(2,3)*m(3,2);
	double B = -m(2,1)*m(3,3)+m(2,3)*m(3,1);
	double C = m(2,1)*m(3,2)-m(2,2)*m(3,1);
	double D = -m(1,2)*m(3,3)+m(1,3)*m(3,2);
	double E = m(1,1)*m(3,3)-m(1,3)*m(3,1);
	double F = -m(1,1)*m(3,2)+m(1,2)*m(3,1);
	double G = m(1,2)*m(2,3)-m(1,3)*m(2,2);
	double H = -m(1,1)*m(2,3)+m(1,3)*m(2,1);
	double I = m(1,1)*m(2,2)-m(1,2)*m(2,1);
	double det = m(1,1)*A+m(1,2)*B+m(1,3)*C;
	if(abs(det)<1e-5){
		cout << "Matrix sub: error in determinant\n";
        exit(EXIT_FAILURE);
	}
	double invdet=1.0/det;
	Matrix *m_aux = new Matrix(m.n_column, m.n_row);
	
	(*m_aux)(1,1)=invdet*A;(*m_aux)(1,2)=invdet*D;(*m_aux)(1,3)=invdet*G;
	(*m_aux)(2,1)=invdet*B;(*m_aux)(2,2)=invdet*E;(*m_aux)(2,3)=invdet*H;
	(*m_aux)(3,1)=invdet*C;(*m_aux)(3,2)=invdet*F;(*m_aux)(3,3)=invdet*I;
	
	return (*m_aux);
}
