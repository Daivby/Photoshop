#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include "filters.h"
#include <thread>
#include <unistd.h>
#include <fstream>      // std::ofstream
#define ONE_OVER_BILLION 1E-9

// En la terminal de cygwig poner make, para compilar la carpeta, estando parado en la carpeta "cd /cygdrive/c/Users/54911/Downloads/entregable-20220524T000308Z-001/entregable/src"
// e introducir los parametros segun sean necesarios

using namespace std;

// El siguiente es un template basico que pueden usar como base

int main(int argc , char* argv[]){
	
	// Asumimos que los filtros sin p1 se escriben primero (por lo tanto, el primer p1 es no nulo)
	// Asumimos que Zoom no se puede encadenar

	if(string(argv[1]) == "-help"){
		cout << "Uso: ./main <filtro> <nthreads> <[p1]> <img1> <custom_output> <[p2]> <img2>" << endl;
		return 0; 
	}
	
	string filter = string(argv[1]);
	unsigned int n = atoi(argv[2]);
	float p1 = atof(argv[3]);
	string img1(argv[4]);
	string out = string(argv[5]);

	
	ppm img(img1);
	
	cout << "Aplicando filtros"<< endl;
	struct timespec start, stop;    	
	clock_gettime(CLOCK_REALTIME, &start);

	if (filter == "frame")
	{
		float p2 = atof(argv[6]);
		frame(img,p1, p2);
	}
	if (filter == "BlackAndWhite")
	{
		blackWhite(img);
	}
	if (filter == "contrast")
	{
		
		contrast(img,p1);
	}
	if (filter == "merge")
	{
		string img2(argv[7]);
		ppm img3(img2);
		merge(img,img3, p1);
	}
	if (filter == "sharpen")
	{
		sharpen(img);
	}	
	
   	clock_gettime(CLOCK_REALTIME, &stop);

	double accum;
	accum = ( stop.tv_sec - start.tv_sec ) + ( stop.tv_nsec - start.tv_nsec ) * ONE_OVER_BILLION;
	printf("%lf s\n", accum);

	cout << "Escribiendo imagen" << endl;
	img.write(out);	
	    
	cout << "Listo" << endl;
	return 0;
}