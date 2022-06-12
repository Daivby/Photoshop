#ifndef FILTERS_H
#define FILTERS_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include "ppm.h"
#include <atomic>


// SINGLE-THREAD FILTERS

void blackWhite(ppm& img, int inicio, int fin);
void contrast(ppm& img, int contrast, int inicio, int fin);
void brightness(ppm& img, float b, int start, int end);
void shades(ppm& img, unsigned char shades);
void merge(ppm& img1, ppm& img2, float alpha, int inicio, int fin);
void frame(ppm& img, int color, int x, int inicio, int fin);
void boxBlur(ppm &img);
void zoom(ppm &img, ppm &img_zoom, int n, int inicio, int fin);
void edgeDetection(ppm &img, ppm &img_target);
void plain(ppm &img, unsigned char c);
void sharpen(ppm& img, ppm &img2, int inicio, int fin, int idthread, int threads);

// MULTI-THREAD FILTERS
void blackWhiteMultithread(ppm &img, int n);
void MergeMultithread (ppm &img1, ppm& img2, float p1, int threads);
void ContrastMultithread (ppm &img, int contrast, int threads);
void SharpenMultithread(ppm &img, ppm &img2, int threads);
void FrameMultithread (ppm &img, int color, int pixels, int threads);
void ZoomMultithread (ppm &img, ppm &img2, int n, int threads);

#endif