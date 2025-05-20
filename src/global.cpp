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

Matrix *obs;

void GEOS3(int nobs){
	obs = new Matrix(zeros(nobs,4));
	//read observations
	FILE *fid = fopen("../data/GEOS3.txt","r");

	if(fid== NULL) {
		printf("Fail open GEOS3.txt file\n");
		exit(EXIT_FAILURE);
	}
	int y,mo,d,h,m,s;
	double az,el,dist;
	char line[55],ly[5],lmo[3],ld[3],lh[3],lm[3],ls[7],laz[9],lel[9],ldist[10];
	for(int i=1;i<=nobs;i++){
		fgets(line,sizeof(line)+2,fid);
		strncpy(ly,&(line[0]),4);
		ly[4]='\0';
		y=atoi(ly);
		strncpy(lmo,&(line[5]),2);
		lmo[2]='\0';
		mo=atoi(lmo);
		strncpy(ld,&(line[8]),2);
		ld[2]='\0';
		d=atoi(ld);
		strncpy(lh,&(line[12]),2);
		lh[2]='\0';
		h=atoi(lh);
		strncpy(lm,&(line[15]),2);
		lm[2]='\0';
		m=atoi(lm);
		strncpy(ls,&(line[18]),6);
		ls[6]='\0';
		s=atoi(ls);
		strncpy(laz,&(line[25]),8);
		laz[8]='\0';
		az=atof(laz);
		strncpy(lel,&(line[35]),8);
		lel[8]='\0';
		el=atof(lel);
		strncpy(ldist,&(line[44]),9);
		ldist[9]='\0';
		dist=atof(ldist);
		
		(*obs)(i,1)=Mjday(y,mo,d,h,m,s);
		(*obs)(i,2)=SAT_Const::Rad*az;
		(*obs)(i,3)=SAT_Const::Rad*el;
		(*obs)(i,4)=1e3*dist;
	}
	fclose(fid);
}