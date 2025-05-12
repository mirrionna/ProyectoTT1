// $Source$
//----------------------------------------------------------------------
// global
//----------------------------------------------------------------------
// Proyecto TT1
//
/**@file global.cpp
*	@brief Carga de varios ficheros de texto.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\global.hpp"

Matrix *eopdata; 

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

Matrix *Cnm; 
Matrix *Snm; 

void GGM03S(){
	
	Cnm = new Matrix(zeros(181, 181));
	Snm = new Matrix(zeros(181, 181));
	FILE *fid = fopen("../data/GGM03S.txt","r");

	if(fid== NULL) {
		printf("Fail open GGM03S.txt file\n");
		exit(EXIT_FAILURE);
	}
	double aux;
	for (int n = 0; n <= 180; n++) {
		for(int m=0;m<=n;m++){
				fscanf(fid, "%lf %lf %lf %lf %lf %lf",
				   &aux, &aux, &(Cnm->operator()(n+1,m+1)),
				   &(Snm->operator()(n+1,m+1)), &aux, &aux);
			}
		}
	fclose(fid);
}

Matrix *PC;
void DE430Coeff(){
	
	PC = new Matrix(zeros(2285, 1020));
	FILE *fid = fopen("../data/DE430Coeff.txt","r");

	if(fid== NULL) {
		printf("Fail open DE430Coeff.txt file\n");
		exit(EXIT_FAILURE);
	}
	double aux;
	for (int n = 1; n <= 2285; n++) {
		for(int m=1;m<=1020;m++){
				fscanf(fid, "%lf ",&((*PC)(n, m)));
			}
		}
	fclose(fid);
}

Matrix *obs;
void GEOS3(int f) {
	obs = new Matrix(zeros(f, 4));
	
	FILE *fp = fopen("../data/GEOS3.txt","r");
	if(fp == NULL) {
		printf("Fail open GEOS3.txt file\n");
		exit(EXIT_FAILURE);
	}
	
	int Y, MO, D, H, MI, S;
	double AZ, EL, DIST;
	char line[55], y[5], mo[3], d[3], h[3], mi[3], s[7], az[9], el[9], dist[10];
	for(int i = 1; i <= f; i++) {
		fgets(line, sizeof(line) + 2, fp);
		
		strncpy(y, &(line[0]), 4);
		y[4] = '\0';
		Y = atoi(y);
		
		strncpy(mo, &(line[5]), 2);
		mo[2] = '\0';
		MO = atoi(mo);
		
		strncpy(d, &(line[8]), 2);
		d[2] = '\0';
		D = atoi(d);
		
		strncpy(h, &(line[12]), 2);
		h[2] = '\0';
		H = atoi(h);
		
		strncpy(mi, &(line[15]), 2);
		mi[2] = '\0';
		MI = atoi(mi);
		
		strncpy(s, &(line[18]), 6);
		s[6] = '\0';
		S = atoi(s);
		
		strncpy(az, &(line[25]), 8);
		az[8] = '\0';
		AZ = atof(az);
		
		strncpy(el, &(line[35]), 8);
		el[8] = '\0';
		EL = atof(el);
		
		strncpy(dist, &(line[44]), 9);
		dist[9] = '\0';
		DIST = atof(dist);
		
		(*obs)(i,1) = Mjday(Y, MO, D, H, MI, S);
		(*obs)(i,2) = SAT_Const::Rad*(AZ);
		(*obs)(i,3) = SAT_Const::Rad*(EL);
		(*obs)(i,4) = 1e3*DIST;
	}
    
	fclose(fp);
}

Param AuxParam;
void cargarAuxParam(){
	AuxParam.Mjd_UTC=4.974611635416653e+04;
	AuxParam.n=20;
	AuxParam.m=20;
	AuxParam.sun=1;
	AuxParam.moon=1;
	AuxParam.planets=1;
	AuxParam.Mjd_TT=4.974611706231468e+04;
}
