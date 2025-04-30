// $Source$
//----------------------------------------------------------------------
// global
//----------------------------------------------------------------------
// Proyecto TT1
//
/**@file global.cpp
*	@brief Carga de un fichero de texto.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\global.hpp"

Matrix* eopdata = nullptr; 

void eop19620101(int c){

	eopdata = new Matrix(zeros(13, c));

	// read Earth orientation parameters
	FILE *fid = fopen("../data/eop19620101.txt","r");

	if(fid== NULL) {
		printf("Fail open eop19620101.txt file\n");
		exit(EXIT_FAILURE);
	}
	for (int j = 1; j <= c; j++) {
        fscanf(fid, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
               &(eopdata->operator()(1, j)), &(eopdata->operator()(2, j)), &(eopdata->operator()(3, j)),
               &(eopdata->operator()(4, j)), &(eopdata->operator()(5, j)), &(eopdata->operator()(6, j)),
               &(eopdata->operator()(7, j)), &(eopdata->operator()(8, j)), &(eopdata->operator()(9, j)),
               &(eopdata->operator()(10, j)), &(eopdata->operator()(11, j)), &(eopdata->operator()(12, j)),
               &(eopdata->operator()(13, j)));
    }
	fclose(fid);
}

Matrix* Cnm = nullptr; 
Matrix* Snm = nullptr; 

void GGM03S(){

	Cnm = new Matrix(zeros(181, 181));
	Snm = new Matrix(zeros(181, 181));
	// read Earth orientation parameters
	FILE *fid = fopen("../data/GGM03S.txt","r");

	if(fid== NULL) {
		printf("Fail open GGM03S.txt file\n");
		exit(EXIT_FAILURE);
	}
	double aux;
	for (int n = 0; n <= 180; n++) {
		for(int m=0;m<=n;m++){
				fscanf(fid, "%lf %lf %lf %lf %lf %lf",
				   &(aux), &(aux), &(Cnm->operator()(n+1,m+1)),
				   &(Snm->operator()(n+1,m+1)), &(aux), &(aux));
			}
		}
	fclose(fid);
}