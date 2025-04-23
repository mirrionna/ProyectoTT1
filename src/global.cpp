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