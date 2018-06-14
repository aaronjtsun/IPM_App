#include "stdafx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>
#include <opencv2/opencv.hpp>
#include "Common.h"
#include "MapPair.h"

using namespace std;
using namespace cv;

MapPair::MapPair() {}

void MapPair::generateMaps(int m, int n, double cx, double cy, double cz, double theta, double gamma, double alpha_h, double alpha_v, int tv_width, int tv_height, double Sx, double Sy) {
	//create 2D arrays for u,v using output pixel size
	double** U = new double*[tv_height];
	double** V = new double*[tv_height];
	for (int i = 0; i < tv_height; ++i) {
		U[i] = new double[tv_width];
		V[i] = new double[tv_width];
	}

	//reverse map each u,v to an x,y coordinate using derived equations
	for (int r = 0; r < tv_height; ++r) {
		double yp = (tv_height - r) / Sy;
		for (int c = 0; c < tv_width; ++c) {
			double xp = (c - (tv_width - 1) / 2.0) / Sx;
			double atanValueU = atan((xp - cx) / (yp - cy));
			double atanValueV = atan(cz / (sqrt(pow((xp - cx), 2) + pow((yp - cy), 2))));
			U[r][c] = (atanValueU - gamma + alpha_h) / ((2 * alpha_h) / (m - 1));
			V[r][c] = (atanValueV - theta + alpha_v) / ((2 * alpha_v) / (n - 1));
		}
	}

	//create maps for u and v to insert into OpenCV remap function
	Mat map_u, map_v;
	map_u.create(tv_height, tv_width, CV_32FC1);
	map_v.create(tv_height, tv_width, CV_32FC1);

	//insert U and V into map_u and map_v if calculated pixel values are within range of the input image
	for (int j = 0; j < tv_height; ++j) {
		for (int i = 0; i < tv_width; ++i) {
			float u = U[j][i];
			float v = V[j][i];
			if (u >= 0.0 && u <= (double)m && v >= 0.0 && v <= (double)n) {
				map_u.at<float>(j, i) = u;
				map_v.at<float>(j, i) = v;
			}

		}
	}
	u = map_u;
	v = map_v;
}
