// $Header$
//----------------------------------------------------------------------
// Matrix
//----------------------------------------------------------------------
// Proyecto TTI
//
/**@file matrix.h
*	@brief Este archivo de cabecera contiene una implementación de una clase que representa una matriz.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#ifndef _MATRIX_
#define _MATRIX_

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace std;

class Matrix {
public:
    int n_row, n_column;
	double **data;

    // Parameterized constructor
	//----------------------------------------------------------------------
	// Matrix(const int n_row, const int n_column)
	//----------------------------------------------------------------------
	/**@brief Constructor de una matriz.
	*
	*	@param [in] n_row Número de filas de la matriz.  
	*	@param [in] n_column Número de columnas de la matriz.
	*	@return Matriz creada con las filas y columnas requeridas.
	*/
	//----------------------------------------------------------------------
    Matrix(const int n_row, const int n_column);
	
	// Member operators
	//----------------------------------------------------------------------
	// double& operator () (const int row, const int column)
	//----------------------------------------------------------------------
	/**@brief Sobreescritura del operador () para acceder a los componentes de la matriz.
	*
	*	@param [in] row Entero que representa el número de la fila que se quiere acceder, entre 1 y n_row.  
	*	@param [in] column Entero que representa el número de la columna que se quiere acceder, entre 1 y n_column.
	*	@return Double que ocupa la fila y columna buscadas.
	*/
	//----------------------------------------------------------------------
	double& operator () (const int row, const int column);
	//----------------------------------------------------------------------
	// Matrix& operator + (Matrix &m)
	//----------------------------------------------------------------------
	/**@brief Sobreescritura del operador suma para dos matrices.
	*
	*	@param [in] m Matriz que se quiere sumar.  
	*	@return Puntero a matriz resultado de sumar a la matriz this la matriz m.
	*/
	//----------------------------------------------------------------------
	Matrix& operator + (Matrix &m);
	//----------------------------------------------------------------------
	// Matrix& operator - (Matrix &m)
	//----------------------------------------------------------------------
	/**@brief Sobreescritura del operador resta para dos matrices.
	*
	*	@param [in] m Matriz que se quiere restar.  
	*	@return Puntero a matriz resultado de restar a la matriz this la matriz m.
	*/
	//----------------------------------------------------------------------
	Matrix& operator - (Matrix &m);
	//----------------------------------------------------------------------
	// Matrix& operator * (Matrix &m)
	//----------------------------------------------------------------------
	/**@brief Sobreescritura del operador multiplicación para dos matrices.
	*
	*	@param [in] m Matriz que se quiere multiplicar.  
	*	@return Puntero a matriz resultado de multiplicar la matriz this por la matriz m.
	*/
	//----------------------------------------------------------------------
	Matrix& operator * (Matrix &m);
	//----------------------------------------------------------------------
	// Matrix& operator / (Matrix &m)
	//----------------------------------------------------------------------
	/**@brief Sobreescritura del operador cociente para dos matrices.
	*
	*	@param [in] m Matriz por la que se quiere dividir.  
	*	@return Puntero a matriz resultado de dividir la matriz this entre la matriz m.
	*/
	//----------------------------------------------------------------------
	Matrix& operator / (Matrix &m); 
	//----------------------------------------------------------------------
	// Matrix& operator = (Matrix &m)
	//----------------------------------------------------------------------
	/**@brief Sobreescritura del operador asignación para dos matrices.
	*
	*	@param [in] m Matriz que se quiere asignar.  
	*	@return Puntero a matriz resultado de asignar la matriz m a this.
	*/
	//----------------------------------------------------------------------
	Matrix& operator = (Matrix &m);
	//----------------------------------------------------------------------
	// Matrix& operator + (double m)
	//----------------------------------------------------------------------
	/**@brief Sobreescritura del operador suma para una matriz y un double.
	*
	*	@param [in] n Double que se quiere sumar.  
	*	@return Puntero a matriz resultado de sumar m a todos los elementos de la matriz this.
	*/
	//----------------------------------------------------------------------
	Matrix& operator + (double n);
	//----------------------------------------------------------------------
	// Matrix& operator - (double m)
	//----------------------------------------------------------------------
	/**@brief Sobreescritura del operador resta para una matriz y un double.
	*
	*	@param [in] n Double que se quiere restar.  
	*	@return Puntero a matriz resultado de restar m a todos los elementos de la matriz this.
	*/
	//----------------------------------------------------------------------
	Matrix& operator - (double n);
	//----------------------------------------------------------------------
	// Matrix& operator * (double m)
	//----------------------------------------------------------------------
	/**@brief Sobreescritura del operador multiplicación para una matriz y un double.
	*
	*	@param [in] n Double por el que se quiere multiplicar.  
	*	@return Puntero a matriz resultado de multiplicar m por todos los elementos de la matriz this.
	*/
	//----------------------------------------------------------------------
	Matrix& operator *	(double n);
	//----------------------------------------------------------------------
	// Matrix& operator / (double m)
	//----------------------------------------------------------------------
	/**@brief Sobreescritura del operador cociente para una matriz y un double.
	*
	*	@param [in] n Double por el que se quiere dividir.  
	*	@return Puntero a matriz resultado de dividir todos los elementos de la matriz this por m.
	*/
	//----------------------------------------------------------------------
	Matrix& operator / (double );
	
	// Non-member operators
	//----------------------------------------------------------------------
	// friend ostream& operator << (ostream &o, Matrix &m)
	//----------------------------------------------------------------------
	/**@brief Sobreescritura del operador << para una matriz.
	*
	*	@param [in] o Método de muestreo por pantalla
		@param [in] m Matriz que se quiere mostrar por pantalla.
	*	@return Muestra por pantalla la matriz m, elemento a elemento.
	*/
	//----------------------------------------------------------------------
	friend ostream& operator << (ostream &o, Matrix &m);
};

// Operator overloading
//----------------------------------------------------------------------
// friend ostream& operator << (ostream &o, Matrix &m)
//----------------------------------------------------------------------
/**@brief Sobreescritura del operador << para una matriz.
*
*	@param [in] o Método de muestreo por pantalla
	@param [in] m Matriz que se quiere mostrar por pantalla.
*	@return Muestra por pantalla la matriz m, elemento a elemento.
*/
//----------------------------------------------------------------------
ostream& operator << (ostream &o, Matrix &m);

// Methods
//----------------------------------------------------------------------
// Matrix& zeros(const int n_row, const int n_column)
//----------------------------------------------------------------------
/**@brief Constructor de una matriz rellena de ceros.
*
*	@param [in] n_row Número de filas de la matriz.
	@param [in] n_column Número de columnas de la matriz.
*	@return Puntero a una matriz con n_row filas, n_column columnas y en todos sus elementos valor cero.
*/
//----------------------------------------------------------------------
Matrix& zeros(const int n_row, const int n_column);
//----------------------------------------------------------------------
// Matrix& eye(const int n_row)
//----------------------------------------------------------------------
/**@brief Constructor de una matriz identidad.
*
*	@param [in] n_row Número de filas de la matriz identidad.
*	@return Puntero a una matriz identidad de tamaño n_row.
*/
//----------------------------------------------------------------------
Matrix& eye(const int n_row);
//----------------------------------------------------------------------
// Matrix& transpose(Matrix &m)
//----------------------------------------------------------------------
/**@brief Transpuesta de una matriz.
*
*	@param [in] m Matriz de la que se quiere obtener la transpuesta.
*	@return Puntero a la matriz transpuesta de m.
*/
//----------------------------------------------------------------------
Matrix& transpose(Matrix &m);
//----------------------------------------------------------------------
// Matrix& inv(Matrix &m)
//----------------------------------------------------------------------
/**@brief Matriz inversa de una matriz, calculando cofactores.
*
*	@param [in] m Matriz de la que se quiere obtener la inversa.
*	@return Puntero a una matriz que es la inversa de m.
*/
//----------------------------------------------------------------------
Matrix& inv(Matrix &m);
//----------------------------------------------------------------------
// Matrix& submatriz(Matrix &m,int i, int j)
//----------------------------------------------------------------------
/**@brief Método auxiliar para obtener una submatriz.
*
*	@param [in] m Matriz de la que se quiere obtener una submatriz.
*	@param [in] i Fila que se quiere eliminar de la matriz.
*	@param [in] j Columna que se quiere eliminar de la matriz.
*	@return Puntero a una matriz idéntica a m, eliminando la i-ésima fila y la j-ésima columna.
*/
//----------------------------------------------------------------------
Matrix& submatriz(Matrix &m, int i, int j);
//----------------------------------------------------------------------
// double determinante(Matrix &m);
//----------------------------------------------------------------------
/**@brief Determinante de una matriz, obtenido recursivamente.
*
*	@param [in] m Matriz de la que se quiere obtener el determinante.
*	@return Double que es el determinante de la matriz m.
*/
//----------------------------------------------------------------------
double determinante(Matrix &m);
#endif