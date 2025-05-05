// $Source$
//----------------------------------------------------------------------
// JPL_Eph_DE430
//----------------------------------------------------------------------
// Proyecto TT1
//
/**@file JPL_Eph_DE430.cpp
*	@brief Cálculo de la posición ecuatorial del sol, la luna y los nueve planetas mayores usando JPL Ephemerides.
*	
*	@author Miguel Río Navarro
*	@bug No known bugs.
*/ 
//----------------------------------------------------------------------
#include "..\include\JPL_Eph_DE430.hpp"

int findbetween(double b){
	for (int i = 1; i <= 2285; i++) {
        if (PC->operator()(i, 1) <= b && b <= PC->operator()(i, 2)) {
            return i;
        }
    }
    return -1;
}

tuple<Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&,Matrix&> JPL_Eph_DE430 (double Mjd_TDB){
	double JD = Mjd_TDB + 2400000.5;
	int i = findbetween(JD); 
	Matrix PCtemp = extract_row(*PC,i);
	double t1 = PCtemp(1)-2400000.5; // MJD at start of interval

	double dt = Mjd_TDB - t1;

	Matrix temp = Matrix(4);
	temp(1)=231;temp(2)=244;temp(3)=257;temp(4)=270;
	Matrix& Cx_Earth = extract_vector(PCtemp,temp(1),temp(2)-1);
	Matrix& Cy_Earth = extract_vector(PCtemp,temp(2),temp(3)-1);
	Matrix& Cz_Earth = extract_vector(PCtemp,temp(3),temp(4)-1);
	temp = temp+39;
	Matrix& Cx = extract_vector(PCtemp,temp(1),temp(2)-1);
	Matrix& Cy = extract_vector(PCtemp,temp(2),temp(3)-1);
	Matrix& Cz = extract_vector(PCtemp,temp(3),temp(4)-1);
	Cx_Earth = union_vector(Cx_Earth,Cx);
	Cy_Earth = union_vector(Cy_Earth,Cy);
	Cz_Earth = union_vector(Cz_Earth,Cz);  
	double Mjd0;
	int j;
	if (0<=dt && dt<=16){
		j=0;
		Mjd0 = t1;
	}
	else if(16<dt && dt<=32){
		j=1;
		Mjd0 = t1+16*j;
	}

	Matrix& Cx_Earth_sub = extract_vector(Cx_Earth,13*j+1,13*j+13);
	Matrix& Cy_Earth_sub = extract_vector(Cy_Earth,13*j+1,13*j+13);
	Matrix& Cz_Earth_sub = extract_vector(Cz_Earth,13*j+1,13*j+13);
	Matrix& r_Earth = Cheb3D(Mjd_TDB, 13, Mjd0, Mjd0+16,Cx_Earth_sub,Cy_Earth_sub,Cz_Earth_sub)*1e3;

	temp(1)=441;temp(2)=454;temp(3)=467;temp(4)=480;
	Matrix& Cx_Moon = extract_vector(PCtemp,temp(1),temp(2)-1);
	Matrix& Cy_Moon = extract_vector(PCtemp,temp(2),temp(3)-1);
	Matrix& Cz_Moon = extract_vector(PCtemp,temp(3),temp(4)-1);
	for(int i=1;i<=7;i++){
		temp = temp+39;
		Cx = extract_vector(PCtemp,temp(1),temp(2)-1);
		Cy = extract_vector(PCtemp,temp(2),temp(3)-1);
		Cz = extract_vector(PCtemp,temp(3),temp(4)-1);   
		Cx_Moon = union_vector(Cx_Moon,Cx);
		Cy_Moon = union_vector(Cy_Moon,Cy);
		Cz_Moon = union_vector(Cz_Moon,Cz);    
	}
	if (0<=dt && dt<=4){
		j=0;
		Mjd0 = t1;
	}
	else if(4<dt && dt<=8){
		j=1;
		Mjd0 = t1+4*j;
	}
	else if(8<dt && dt<=12){
		j=2;
		Mjd0 = t1+4*j;
	}
	else if(12<dt && dt<=16){
		j=3;
		Mjd0 = t1+4*j;
	}
	else if(16<dt && dt<=20){
		j=4;
		Mjd0 = t1+4*j;
	}
	else if(20<dt && dt<=24){
		j=5;
		Mjd0 = t1+4*j;
	}
	else if(24<dt && dt<=28){
		j=6;
		Mjd0 = t1+4*j;
	}
	else if(28<dt && dt<=32){
		j=7;
		Mjd0 = t1+4*j;
	}
	Matrix& r_Moon = Cheb3D(Mjd_TDB, 13, Mjd0, Mjd0+4, extract_vector(Cx_Moon,13*j+1,13*j+13),extract_vector(Cy_Moon,13*j+1,13*j+13), extract_vector(Cz_Moon,13*j+1,13*j+13))*1e3;
	temp(1)=753;temp(2)=764;temp(3)=775;temp(4)=786;
	Matrix& Cx_Sun = extract_vector(PCtemp,temp(1),temp(2)-1);
	Matrix& Cy_Sun = extract_vector(PCtemp,temp(2),temp(3)-1);
	Matrix& Cz_Sun = extract_vector(PCtemp,temp(3),temp(4)-1);
	temp = temp+33;
	Cx = extract_vector(PCtemp,temp(1),temp(2)-1);
	Cy = extract_vector(PCtemp,temp(2),temp(3)-1);
	Cz = extract_vector(PCtemp,temp(3),temp(4)-1);   
	Cx_Sun = union_vector(Cx_Sun,Cx);
	Cy_Sun = union_vector(Cy_Sun,Cy);
	Cz_Sun = union_vector(Cz_Sun,Cz);
	if (0<=dt && dt<=16){
		j=0;
		Mjd0 = t1;
	}
	else if(16<dt && dt<=32){
		j=1;
		Mjd0 = t1+16*j;
	}
	Matrix& r_Sun = Cheb3D(Mjd_TDB, 11, Mjd0, Mjd0+16, extract_vector(Cx_Sun,11*j+1,11*j+11),extract_vector(Cy_Sun,11*j+1,11*j+11), extract_vector(Cz_Sun,11*j+1,11*j+11))*1e3;
	temp(1)=3;temp(2)=17;temp(3)=31;temp(4)=45;	
	Matrix& Cx_Mercury = extract_vector(PCtemp,temp(1),temp(2)-1);
	Matrix& Cy_Mercury = extract_vector(PCtemp,temp(2),temp(3)-1);
	Matrix& Cz_Mercury = extract_vector(PCtemp,temp(3),temp(4)-1);
	for(int i=1;i<=3;i++){
		temp = temp+42;
		Cx = extract_vector(PCtemp,temp(1),temp(2)-1);
		Cy = extract_vector(PCtemp,temp(2),temp(3)-1);
		Cz = extract_vector(PCtemp,temp(3),temp(4)-1);
		Cx_Mercury = union_vector(Cx_Mercury,Cx);
		Cy_Mercury = union_vector(Cy_Mercury,Cy);
		Cz_Mercury = union_vector(Cz_Mercury,Cz);    
	}
	if (0<=dt && dt<=8){
		j=0;
		Mjd0 = t1;
	}
	else if(8<dt && dt<=16){
		j=1;
		Mjd0 = t1+8*j;
	}
	else if (16<dt && dt<=24){
		j=2;
		Mjd0 = t1+8*j;
	}
	else if(24<dt && dt<=32){
		j=3;
		Mjd0 = t1+8*j;
	}
	Matrix& r_Mercury = Cheb3D(Mjd_TDB, 14, Mjd0, Mjd0+8, extract_vector(Cx_Mercury,14*j+1,14*j+14),extract_vector(Cy_Mercury,14*j+1,14*j+14), extract_vector(Cz_Mercury,14*j+1,14*j+14))*1e3;
	temp(1)=171;temp(2)=181;temp(3)=191;temp(4)=201;
	Matrix& Cx_Venus = extract_vector(PCtemp,temp(1),temp(2)-1);
	Matrix& Cy_Venus = extract_vector(PCtemp,temp(2),temp(3)-1);
	Matrix& Cz_Venus = extract_vector(PCtemp,temp(3),temp(4)-1);
	temp = temp+30;
	Cx = extract_vector(PCtemp,temp(1),temp(2)-1);
	Cy = extract_vector(PCtemp,temp(2),temp(3)-1);
	Cz = extract_vector(PCtemp,temp(3),temp(4)-1);
	Cx_Venus = union_vector(Cx_Venus,Cx);
	Cy_Venus = union_vector(Cy_Venus,Cy);
	Cz_Venus = union_vector(Cz_Venus,Cz);
	if (0<=dt && dt<=16){
		j=0;
		Mjd0 = t1;
	}
	else if(16<dt && dt<=32){
		j=1;
		Mjd0 = t1+16*j;
	}
	Matrix& r_Venus = Cheb3D(Mjd_TDB, 10, Mjd0, Mjd0+16, extract_vector(Cx_Venus,10*j+1,10*j+10),extract_vector(Cy_Venus,10*j+1,10*j+10), extract_vector(Cz_Venus,10*j+1,10*j+10))*1e3;
	temp(1)=309;temp(2)=320;temp(3)=331;temp(4)=342;	
	Matrix& Cx_Mars = extract_vector(PCtemp,temp(1),temp(2)-1);
	Matrix& Cy_Mars = extract_vector(PCtemp,temp(2),temp(3)-1);
	Matrix& Cz_Mars = extract_vector(PCtemp,temp(3),temp(4)-1);
	j=0;
	Mjd0 = t1;
	Matrix& r_Mars = Cheb3D(Mjd_TDB, 11, Mjd0, Mjd0+32, extract_vector(Cx_Mars,11*j+1,11*j+11),extract_vector(Cy_Mars,11*j+1,11*j+11), extract_vector(Cz_Mars,11*j+1,11*j+11))*1e3;
	temp(1)=342;temp(2)=350;temp(3)=358;temp(4)=366;
	Matrix& Cx_Jupiter = extract_vector(PCtemp,temp(1),temp(2)-1);
	Matrix& Cy_Jupiter = extract_vector(PCtemp,temp(2),temp(3)-1);
	Matrix& Cz_Jupiter = extract_vector(PCtemp,temp(3),temp(4)-1);
	j=0;
	Mjd0 = t1;
	Matrix& r_Jupiter = Cheb3D(Mjd_TDB, 8, Mjd0, Mjd0+32, extract_vector(Cx_Jupiter,8*j+1,8*j+8),extract_vector(Cy_Jupiter,8*j+1,8*j+8), extract_vector(Cz_Jupiter,8*j+1,8*j+8))*1e3;
	temp(1)=366;temp(2)=373;temp(3)=380;temp(4)=387;
	Matrix& Cx_Saturn = extract_vector(PCtemp,temp(1),temp(2)-1);
	Matrix& Cy_Saturn = extract_vector(PCtemp,temp(2),temp(3)-1);
	Matrix& Cz_Saturn = extract_vector(PCtemp,temp(3),temp(4)-1);
	j=0;
	Mjd0 = t1;
	Matrix& r_Saturn = Cheb3D(Mjd_TDB, 7, Mjd0, Mjd0+32, extract_vector(Cx_Saturn,7*j+1,7*j+7),extract_vector(Cy_Saturn,7*j+1,7*j+7), extract_vector(Cz_Saturn,7*j+1,7*j+7))*1e3;
	temp(1)=387;temp(2)=393;temp(3)=399;temp(4)=405;
	Matrix& Cx_Uranus = extract_vector(PCtemp,temp(1),temp(2)-1);
	Matrix& Cy_Uranus = extract_vector(PCtemp,temp(2),temp(3)-1);
	Matrix& Cz_Uranus = extract_vector(PCtemp,temp(3),temp(4)-1);
	j=0;
	Mjd0 = t1;
	Matrix& r_Uranus = Cheb3D(Mjd_TDB, 6, Mjd0, Mjd0+32, extract_vector(Cx_Uranus,6*j+1,6*j+6),extract_vector(Cy_Uranus,6*j+1,6*j+6), extract_vector(Cz_Uranus,6*j+1,6*j+6))*1e3;
	temp(1)=405;temp(2)=411;temp(3)=417;temp(4)=423;
	Matrix& Cx_Neptune = extract_vector(PCtemp,temp(1),temp(2)-1);
	Matrix& Cy_Neptune = extract_vector(PCtemp,temp(2),temp(3)-1);
	Matrix& Cz_Neptune = extract_vector(PCtemp,temp(3),temp(4)-1);
	j=0;
	Mjd0 = t1;
	Matrix& r_Neptune = Cheb3D(Mjd_TDB, 6, Mjd0, Mjd0+32, extract_vector(Cx_Neptune,6*j+1,6*j+6),extract_vector(Cy_Neptune,6*j+1,6*j+6), extract_vector(Cz_Neptune,6*j+1,6*j+6))*1e3;
	temp(1)=423;temp(2)=429;temp(3)=435;temp(4)=441;
	Matrix& Cx_Pluto = extract_vector(PCtemp,temp(1),temp(2)-1);
	Matrix& Cy_Pluto = extract_vector(PCtemp,temp(2),temp(3)-1);
	Matrix& Cz_Pluto = extract_vector(PCtemp,temp(3),temp(4)-1);
	j=0;
	Mjd0 = t1;
	Matrix& r_Pluto = Cheb3D(Mjd_TDB, 6, Mjd0, Mjd0+32, extract_vector(Cx_Pluto,6*j+1,6*j+6),extract_vector(Cy_Pluto,6*j+1,6*j+6), extract_vector(Cz_Pluto,6*j+1,6*j+6))*1e3;
	/*
	temp(1)=819;temp(2)=829;temp(3)=839;
	Matrix& Cx_Nutations = extract_vector(PCtemp,temp(1),temp(2)-1);
	Matrix& Cy_Nutations = extract_vector(PCtemp,temp(2),temp(3)-1);
	cout<<"Antes del bucle\n";
	cout<<temp;
	for(int i=1;i<=3;i++){
		temp = temp+20;
		cout<<"Iteracion: "<<i<<"\n";
		cout<<temp;
		Cx = extract_vector(PCtemp,temp(1),temp(2)-1);
		Cy = extract_vector(PCtemp,temp(2),temp(3)-1);
		cout<<"Cx,Cy sacados \n";
		Cx_Nutations = union_vector(Cx_Nutations,Cx);
		Cy_Nutations = union_vector(Cy_Nutations,Cy);
		cout<<Cx_Nutations;
		cout<<Cy_Nutations;
	}
	cout<<"Dsps del bucle\n";
	if (0<=dt && dt<=8){
		j=0;
		Mjd0 = t1;
	}
	else if(8<dt && dt<=16){
		j=1;
		Mjd0 = t1+8*j;
	}
	else if (16<dt && dt<=24){
		j=2;
		Mjd0 = t1+8*j;
	}
	else if(24<dt && dt<=32){
		j=3;
		Mjd0 = t1+8*j;
	}
	cout<<j<<" "<<Mjd0<<"\n";
	Matrix& zz = zeros(1,10);
	Matrix& Nutations = Cheb3D(Mjd_TDB, 10, Mjd0, Mjd0+8, extract_vector(Cx_Nutations,10*j+1,10*j+10),extract_vector(Cy_Nutations,10*j+1,10*j+10),zz);
	cout<<"NUTACIONES\n";
	temp(1)=899;temp(2)=909;temp(3)=919;temp(4)=929;
	Matrix& Cx_Librations = extract_vector(PCtemp,temp(1),temp(2)-1);
	Matrix& Cy_Librations = extract_vector(PCtemp,temp(2),temp(3)-1);
	Matrix& Cz_Librations = extract_vector(PCtemp,temp(3),temp(4)-1);
	for(int i=1;i<=3;i++){
		temp = temp+30;
		Cx = extract_vector(PCtemp,temp(1),temp(2)-1);
		Cy = extract_vector(PCtemp,temp(2),temp(3)-1);
		Cz = extract_vector(PCtemp,temp(3),temp(4)-1);
		Cx_Librations = union_vector(Cx_Librations,Cx);
		Cy_Librations = union_vector(Cy_Librations,Cy);
		Cz_Librations = union_vector(Cz_Librations,Cz);    
	}
	if (0<=dt && dt<=8){
		j=0;
		Mjd0 = t1;
	}
	else if(8<dt && dt<=16){
		j=1;
		Mjd0 = t1+8*j;
	}
	else if (16<dt && dt<=24){
		j=2;
		Mjd0 = t1+8*j;
	}
	else if(24<dt && dt<=32){
		j=3;
		Mjd0 = t1+8*j;
	}
	Matrix& Librations = Cheb3D(Mjd_TDB, 10, Mjd0, Mjd0+8, extract_vector(Cx_Librations,10*j+1,10*j+10),extract_vector(Cy_Librations,10*j+1,10*j+10), extract_vector(Cz_Librations,10*j+1,10*j+10));
	cout<<"Librations\n";
	*/
	double EMRAT = 81.30056907419062; // DE430
	double EMRAT1 = 1/(1+EMRAT);
	Matrix aux = r_Moon*EMRAT1;
	r_Earth = r_Earth-aux;
	r_Mercury = r_Mercury-r_Earth;
	r_Venus = r_Venus-r_Earth;
	r_Mars = r_Mars-r_Earth;
	r_Jupiter = r_Jupiter-r_Earth;
	r_Saturn = r_Saturn-r_Earth;
	r_Uranus = r_Uranus-r_Earth;
	r_Neptune = r_Neptune-r_Earth;
	r_Pluto = r_Pluto-r_Earth;
	r_Sun = r_Sun-r_Earth;
	return std::tie(transpose(r_Mercury),transpose(r_Venus),transpose(r_Earth),transpose(r_Mars),transpose(r_Jupiter),transpose(r_Saturn),transpose(r_Uranus),transpose(r_Neptune),transpose(r_Pluto),transpose(r_Moon),transpose(r_Sun));
}