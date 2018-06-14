#include <vector>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

#ifndef generic
#define generic
	
int helpful(char *nameofprogram, string input_file_name);
string lowercase(string rawString);
string getNewConsoleInput();
int getIntFromConsole(string message, int recommended, int min, int max);
double getDoubleFromConsole(string message, double recommended, double min, double max);
double average(double* arr, int size);
double cot(double i);
vector<vector<double>> readdata(ifstream & fin);

enum {
	programname,
	inputfilename,
	datafilename,
	arguments,
	badinput,
	noimageerror,
	baddatafile,
};
#endif