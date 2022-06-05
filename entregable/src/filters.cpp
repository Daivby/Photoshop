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

void blackWhite(ppm& img)
{
	for(int i = 0; i < img.height; i++)
		for(int j = 0; j < img.width; j++)
		{
			pixel pix = img.getPixel(i,j); // Fijo en p, la posicion del pixel en i y j, la variable pixen le da al pixel los valores r g y b
			int res = (pix.r + pix.g + pix.b) / 3; // aplico la cuenta del filtro B&W, si seguido del ., pongo r, g o b, puedo llamar los valores rgb de la variable pixel
			img.setPixel(i, j, pixel(res,res,res)); // Reemplaza los valores del pixel original, con los del pixel filtrado
		}
}
void merge(ppm& img1, ppm& img2, float p1)
{
	float p2 = 1 - p1;
	for(int i = 0; i < img1.height; i++)
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
void contrast(ppm& img, float contrast)
{

	for(int i = 0; i < img.height; i++)
		for(int j = 0; j < img.width; j++){
			pixel pix = img.getPixel(i,j);
			int altR = pix.r - 128;
			int R = ((259*(altR + 255))/(255*(259 - altR))) + 128;
			int altG = pix.g - 128;
			int G = ((259*(altG + 255))/(255*(259 - altG))) + 128;
			int altB = pix.b - 128;
			int B = ((259*(altB + 255))/(255*(259 - altB))) + 128;
			img.setPixel(i, j, pixel(R,G,B)); // Reemplaza los valores del pixel original, con los del pixel filtrado
		}
}
void sharpen(ppm& img)
{
	for (int i = 0; i+2 < img.height; i++)
	{
		for (int j = 0; j+2 < img.width; j++)
		{
			pixel pix11 = img.getPixel(i,j);
			pixel pix12 = img.getPixel(i+1,j);
			pixel pix13 = img.getPixel(i+2,j);
			pixel pix21 = img.getPixel(i,j+1);
			pixel pix22 = img.getPixel(i+1,j+1);
			pixel pix23 = img.getPixel(i+2,j+1);
			pixel pix31 = img.getPixel(i,j+2);         //(pix11 pix12 pix13)       ( 0 -1  0 )
			pixel pix32 = img.getPixel(i+1,j+2);
			pixel pix33 = img.getPixel(i+2,j+2);       //(pix21 pix22 pix23)    +  (-1  5 -1 )
			
			       									   //(pix31 pix32 pix33)       ( 0 -1  0 )
			int R = (pix11.r * 0) + (pix12.r + -1) + (pix13.r * 0) + (pix21.r * -1) + (pix22.r * 5) + (pix23.r * -1) + (pix31.r * 0) + (pix32.r * -1) + (pix33.r * 0);
			int G = (pix11.g * 0) + (pix12.g + -1) + (pix13.g * 0) + (pix21.g * -1) + (pix22.g * 5) + (pix23.g * -1) + (pix31.g * 0) + (pix32.g * -1) + (pix33.g * 0);
			int B = (pix11.b * 0) + (pix12.b + -1) + (pix13.b * 0) + (pix21.b * -1) + (pix22.b * 5) + (pix23.b * -1) + (pix31.b * 0) + (pix32.b * -1) + (pix33.b * 0);
			img.setPixel(i, j, pixel(R,G,B));
		}
	}
}
void frame(ppm& img, int color, int x)
{
	for (int i = 0; i < img.height; i++)
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
void zoom(ppm &img, ppm &img_zoomed, int n)
{

}