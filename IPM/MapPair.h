#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <opencv2/opencv.hpp>
#include "Common.h"

using namespace std;
using namespace cv;

#ifndef mappairs
#define mappairs
class MapPair {
public:
	MapPair();
	Mat u;
	Mat v;
	void generateMaps(int m, int n, double cx, double cy, double cz, double theta, double gamma, double alpha_h, double alpha_v, int tv_width, int tv_height, double Sx, double Sy);
};
#endif