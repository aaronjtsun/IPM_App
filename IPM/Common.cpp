#include "stdafx.h"
#include "Common.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

int helpful(char *nameofprogram, string input_file_name) {
	cout << "usage: " << nameofprogram << input_file_name << endl;
	return badinput;
}

string lowercase(string rawString) {
	for (unsigned int i = 0; i < rawString.length(); ++i) {
		char rawChar = rawString[i];
		if (rawChar >= 'A' && rawChar <= 'Z') {
			rawChar = rawChar - ('Z' - 'z');
		}
		rawString[i] = rawChar;
	}
	cout << rawString << endl;
	return rawString;
}

string getNewConsoleInput() {
	std::cout << "Enter string:" << flush;
	std::string s;
	std::getline(std::cin, s);
	return s;
}

int getIntFromConsole(string message, int recommended, int min, int max) {
	string temp;
	int ans;
	while (1) {
		cout << "Please enter an integer between " << min << " and " << max << " for " << message << " (recommended: " << recommended << "):";
		cin >> temp;
		bool isInt = true;
		for (int i = 0; i < temp.length(); ++i) {
			char c = temp.at(i);
			if (!isdigit(c)) {
				isInt = false;
			}
		}
		if (!isInt) {
			cout << "Bad input - try again" << endl;
			continue;
		}
		ans = stoi(temp);
			
		if (ans >= min && ans <= max) {
			return ans;
		}
		else {
			cout << "Out of range - try again" << endl;
		}
	}
}

double getDoubleFromConsole(string message, double recommended, double min, double max) {
	string temp;
	double ans;
	while (1) {
		cout << "Please enter a double between " << min << " and " << max << " for " << message << " (recommended: " << recommended << "):";
		cin >> temp;
		int decimals = 0;
		bool isDouble = true;
		for (int i = 0; i < temp.length(); ++i) {
			char c = temp.at(i);
			if (!isdigit(c)) {
				if (c == '.') {
					decimals++;
					if (decimals > 1) {
						isDouble = false;
					}
				}
				else isDouble = false;
			}
		}
		if (!isDouble) {
			cout << "Bad input - try again" << endl;
			continue;
		}
		ans = stod(temp);

		if (ans >= min && ans <= max) {
			return ans;
		}
		else {
			cout << "Out of range - try again" << endl;
		}
	}
}

double average(double* arr, int size)
{
	double sum = 0;
	for (int i = 0; i < size; ++i) {
		sum += arr[i];
	}
	return sum / size;
}

double cot(double i)
{
	return 1 / tan(i);
}

vector<vector<double>> readdata(ifstream & fin) {
	vector<vector<double>> data;
	string s;
	while(getline(fin, s)) {
		vector<double> newline;
		istringstream sin(s);
		double tmp;
		while (sin >> tmp) {
			newline.push_back(tmp);
		}
		data.push_back(newline);
	}
	return data;
}