#include "stdafx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <cmath>
#include <vector>
#include <fstream>
#include <opencv2/opencv.hpp>
#include "Calibration.h"
#include "Common.h"
using namespace std;
using namespace cv;


Calibration::Calibration() {}

void Calibration::calibrate(int m, int n, double cx, double cy, double cz, double alpha_h, double alpha_v, int points, double** xy, double** uv)
{
	//center left, center right, far left, far right x-coordinates in field test calibration image
	//double cl, cr, fl, fr;

	//cl = -21.5 / 12.0;
	//cr = 21.5 / 12.0;
	//fl = (-21.5 - 186.0) / 12.0;
	//fr = (21.5 + 196.0) / 12.0;

	//fill in actual x,y coordinates of points in calibration image as measured in field test, in terms of feet
	//double xy[points][2] = { { fl, 16 + 1 / 12.0 },{ fl, 32 + 2 / 12.0 },{ fl,48 + 1 / 12.0 },{ fl,64 + 1 / 12.0 },{ fl,80 + 1 / 12.0 },{ fl,96 + 1 / 12.0 },{ fl,112 + 1 / 12.0 },{ fl,128 + 1 / 12.0 },{ cl, 16 + 1 / 12.0 },{ cl, 32 + 2 / 12.0 },{ cl,48 + 1 / 12.0 },{ cl,64 + 1 / 12.0 },{ cl,80 + 1 / 12.0 },{ cl,96 + 1 / 12.0 },{ cl,112 + 1 / 12.0 },{ cl,128 + 1 / 12.0 },{ cr,15 + 11 / 12.0 },{ cr,32.0 },{ cr,48.0 },{ cr,63 + 11 / 12.0 },{ cr,79 + 11 / 12.0 },{ cr,95 + 11 / 12.0 },{ cr,112.0 },{ cr,128 + 1 / 12.0 },{ fr,15 + 11 / 12.0 },{ fr,32.0 },{ fr,48.0 },{ fr,63 + 11 / 12.0 },{ fr,79 + 11 / 12.0 },{ fr,95 + 11 / 12.0 },{ fr,112.0 },{ fr,128 + 1 / 12.0 } };


	//fill in u,v pixel coordinates of points in calibration image, measured through any photo editing/viewing software
	//double uv[points][2] = { { 911,1685 },{ 1295,1575 },{ 1488,1523 },{ 1597,1490 },{ 1671,1470 },{ 1722,1456 },{ 1763,1446 },{ 1793,1438 },{ 1879,1741 },{ 1937,1600 },{ 1957,1535 },{ 1971,1501 },{ 1978,1479 },{ 1984,1464 },{ 1988,1453 },{ 1992,1444 },{ 2131,1747 },{ 2085,1601 },{ 2065,1537 },{ 2055,1503 },{ 2049,1481 },{ 2044,1465 },{ 2040,1454 },{ 2037,1444 },{ 3149,1747 },{ 2753,1615 },{ 2558,1550 },{ 2439,1514 },{ 2364,1489 },{ 2312,1472 },{ 2273,1459 },{ 2242,1449 } };

	//initialize arrays for gamma and theta values for each point.
	double* gammas = new double[points];
	double* thetas = new double[points];

	//calculate gamma and theta values for each point using derived equations
	for (int i = 0; i < points; ++i) {
		double xp = xy[0][i];
		double yp = xy[1][i];
		double u = uv[0][i];
		double v = uv[1][i];
		double atan_val1 = atan((xp - cx) / (yp - cy));
		double atan_val2 = atan(cz * sin(atan_val1) / (xp - cx));
		gammas[i] = (atan_val1 - u * (2 * alpha_h) / (m - 1) + alpha_h) * 180 / M_PI;
		thetas[i] = (atan_val2 - v * (2 * alpha_v) / (n - 1) + alpha_v) * 180 / M_PI;
	}

	//average gamma and theta values for all points and convert to radians
	double averagegamma = average(gammas, points);
	double averagetheta = average(thetas, points);
	gamma = averagegamma * M_PI / 180;
	theta = averagetheta * M_PI / 180;

	/*
	//print out all gamma and theta values for debugging purposes
	for (int i = 0; i < points; ++i){
	cout << "gamma: " << gammas[i] << " theta: " << thetas[i] << endl;
	}
	*/

}
