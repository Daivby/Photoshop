#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>       /* sqrt */
#include <vector>
#include "filters.h"
#include <thread>  
#include <atomic>  

#define BLACK 0

using namespace std;

// COMPLETAR :)

// Filtro plano como ejemplo

void blackWhite(ppm& img, int inicio, int fin)
{
	for(int i = inicio; i < fin; i++)
		for(int j = 0; j < img.width; j++)
		{
			pixel pix = img.getPixel(i,j); // Fijo en p, la posicion del pixel en i y j, la variable pixen le da al pixel los valores r g y b
			int res = (pix.r + pix.g + pix.b) / 3; // aplico la cuenta del filtro B&W, si seguido del ., pongo r, g o b, puedo llamar los valores rgb de la variable pixel
			img.setPixel(i, j, pixel(res,res,res)); // Reemplaza los valores del pixel original, con los del pixel filtrado
		}

}
void merge(ppm& img1, ppm& img2, float p1, int inicio, int fin)
{
	float p2 = 1 - p1;
	cout << inicio << endl;
	cout << fin << endl;
	for(int i = inicio; i < fin; i++)
		for(int j = 0; j < img1.width; j++)
		{
			pixel pix1 = img1.getPixel(i,j);
			pixel pix2 = img2.getPixel(i,j); // Fijo en p, la posicion del pixel en i y j, la variable pixen le da al pixel los valores r g y b
			int R = (pix1.r * p1 + pix2.r * p2);
			int G = (pix1.g * p1 + pix2.g * p2);
			int B = (pix1.b * p1 + pix2.b * p2); // aplico la cuenta del filtro B&W, si seguido del ., pongo r, g o b, puedo llamar los valores rgb de la variable pixel
			img1.setPixel(i, j, pixel(R,G,B)); // Reemplaza los valores del pixel original, con los del pixel filtrado
		}
}
void contrast(ppm& img, int contrast, int inicio, int fin)
{
	float numerador = 259*(contrast + 255);
	float denominador = 255*(259 - contrast);
	float f = numerador / denominador;
	for(int i = inicio; i < fin; i++)
		for(int j = 0; j < img.width; j++){
			pixel pix = img.getPixel(i,j);
			int R = f*(pix.r - 128) + 128;
			int G = f*(pix.g - 128) + 128;
			int B = f*(pix.b - 128) + 128;
			img.setPixel(i, j, pixel(R,G,B).truncate()); // Reemplaza los valores del pixel original, con los del pixel filtrado
		}
	
}
void sharpen(ppm& img, ppm &img2, int inicio, int fin, int idthread, int threads)
{
	if (idthread < threads)
	{
		fin = fin;
	}
	else if (idthread == threads)
	{
		fin -= 2;
	}
	
	for (int i = inicio; i < fin; i++)
	{
		for (int j = 0; j+2 < img.width; j++)
		{
			pixel pix11 = img.getPixel(i,j);
			pixel pix12 = img.getPixel(i,j+1);
			pixel pix13 = img.getPixel(i,j+2);
			pixel pix21 = img.getPixel(i+1,j);
			pixel pix22 = img.getPixel(i+1,j+1);
			pixel pix23 = img.getPixel(i+1,j+2);
			pixel pix31 = img.getPixel(i+2,j);         //(pix11 pix12 pix13)       ( 0 -1  0 )
			pixel pix32 = img.getPixel(i+2,j+1);
			pixel pix33 = img.getPixel(i+2,j+2);       //(pix21 pix22 pix23)    +  (-1  5 -1 )
			
			       									   //(pix31 pix32 pix33)       ( 0 -1  0 )
			int y11= 0;
			int y12= -1;
			int y13= 0;
			int y21= -1;
			int y22= 5;
			int y23= -1;
			int y31= 0;
			int y32= -1;
			int y33= 0;

			int R11 = pix11.r * y11;
			int R12 = pix12.r * y12;
			int R13 = pix13.r * y13;
			int R21 = pix21.r * y21;
			int R22 = pix22.r * y22;
			int R23 = pix23.r * y23;
			int R31 = pix31.r * y31;
			int R32 = pix32.r * y32;
			int R33 = pix33.r * y33;

			int G11 = pix11.g * y11;
			int G12 = pix12.g * y12;
			int G13 = pix13.g * y13;
			int G21 = pix21.g * y21;
			int G22 = pix22.g * y22;
			int G23 = pix23.g * y23;
			int G31 = pix31.g * y31;
			int G32 = pix32.g * y32;
			int G33 = pix33.g * y33;

			int B11 = pix11.b * y11;
			int B12 = pix12.b * y12;
			int B13 = pix13.b * y13;
			int B21 = pix21.b * y21;
			int B22 = pix22.b * y22;
			int B23 = pix23.b * y23;
			int B31 = pix31.b * y31;
			int B32 = pix32.b * y32;
			int B33 = pix33.b * y33;

			int R = R11+R12+R13+R21+R22+R23+R31+R32+R33;
			int G = G11+G12+G13+G21+G22+G23+G31+G32+G33;
			int B = B11+B12+B13+B21+B22+B23+B31+B32+B33;

			img2.setPixel(i, j, pixel(R,G,B).truncate());
		}
	}
	
}
void frame(ppm& img, int color, int x, int inicio, int fin)
{
	for (int i = inicio; i < fin; i++)
	{
		for (int j = 0; j < img.width; j++)
		{
			if(!(j > x) || ! (i > x) ||! (j < img.width - x) || ! (i < img.height - x ))
			{
				img.setPixel(i,j,pixel(color,color,color));
			}
		}
	}
}
void zoom(ppm &img, ppm &img_zoom, int n, int inicio, int fin)
{

	for (int i = inicio; i < fin; i++)
	{
		for (int j = 0; j < img.width; j++)
		{
			for (int i_ = 0; i_ < n; i_++)
			{
				for (int j_ = 0; j_ < n; j_++)
				{
					img_zoom.setPixel((i * n) + i_, (j * n) + j_, img.getPixel(i,j));
				}
			}
		}
	}
}

void blackWhiteMultithread (ppm &img, int threads)
{
	int x = img.height/threads;
	int inicio;
	int fin;
	vector<thread> BlackWhitethreads;
	for(int i = 1; i <= threads; i++) 
	{
		if (i == threads)
		{
			fin = img.height;
		}
		else
		{
			fin = x * i;
		}
		
		BlackWhitethreads.push_back(thread(blackWhite, ref(img), inicio, fin));
		 
		inicio = fin + 1;
	}
	for (int i = 0; i < threads; i++)
	{
		BlackWhitethreads[i].join();
	}
}
void MergeMultithread (ppm &img1, ppm& img2, float p1, int threads)
{
	int x = img1.height/threads;
	int inicio;
	int fin;
	vector<thread> mergethreads;
	for(int i = 1; i <= threads; i++) 
	{
		if (i == threads)
		{
			fin = img1.height;
		}
		else
		{
			fin = x * i;
		}
		
		mergethreads.push_back(thread(merge, ref(img1), ref(img2), p1, inicio, fin));
		 
		inicio = fin;
	}
	for (int i = 0; i < threads; i++)
	{
		mergethreads[i].join();
	}
}
void ContrastMultithread (ppm &img, int contraste, int threads)
{
	int x = img.height/threads;
	int inicio;
	int fin;
	vector<thread> Contrastthreads;
	for(int i = 1; i <= threads; i++) 
	{
		if (i == threads)
		{
			fin = img.height;
		}
		else
		{
			fin = x * i;
		}
		
		Contrastthreads.push_back(thread(contrast, ref(img), contraste, inicio, fin));
		 
		inicio = fin + 1;
	}
	for (int i = 0; i < threads; i++)
	{
		Contrastthreads[i].join();
	}
}
void SharpenMultithread(ppm &img, ppm &img2, int threads)
{
	int idthread = 1;
	int x = img.height/threads;
	int inicio = 0;
	int fin; 
	vector<thread> Sharpenthreads;
	for (int i = 1; i <= threads; i++)
	{
		if (i == threads)
		{
			fin = img.height;
		}
		else
		{
			fin = x * i;
		}
		
		Sharpenthreads.push_back(thread(sharpen, ref(img), ref (img2), inicio, fin, idthread, threads));
		inicio = fin;
		idthread += 1;

	}
	for (int i = 0; i < threads; i ++)
	{
		Sharpenthreads[i].join();
	}
}
void FrameMultithread (ppm &img, int color, int pixels, int threads)
{
	int x = img.height/threads;
	int inicio;
	int fin;
	vector<thread> Framethreads;
	for(int i = 1; i <= threads; i++) 
	{
		if (i == threads)
		{
			fin = img.height;
		}
		else
		{
			fin = x * i;
		}
		
		Framethreads.push_back(thread(frame, ref(img), color, pixels, inicio, fin));
		 
		inicio = fin + 1;
	}
	for (int i = 0; i < threads; i++)
	{
		Framethreads[i].join();
	}
}
void ZoomMultithread (ppm &img, ppm &img2, int n, int threads)
{
	int x = img.height/threads;
	int inicio = 0;
	int fin;
	vector<thread> Zoomthreads;
	for(int i = 1; i <= threads; i++) 
	{
		if (i == threads)
		{
			fin = img.height;
		}
		else
		{
			fin = x * i;
		}
		
		Zoomthreads.push_back(thread(zoom, ref(img), ref(img2), n, inicio, fin));
		 
		inicio = fin;
	}
	for (int i = 0; i < threads; i++)
	{
		Zoomthreads[i].join();
	}
}