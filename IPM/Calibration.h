#include <string>
using namespace std;

#ifndef calibration
#define calibration
class Calibration {
public:
	Calibration();
	double gamma;
	double theta;
	void calibrate(int m, int n, double cx, double cy, double cz, double alpha_h, double alpha_v, int points, double** xy, double** uv);
};
#endif