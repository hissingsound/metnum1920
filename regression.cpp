#include <iostream>
#include <iomanip>
#include <utility>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

typedef vector<pair<double, double>> Data;

namespace regression {
	int prompt() {
		cout << "1) Model linear\n2) Model exponensial\n3) Model power\n4) Model saturation growth rate" << endl;
		cout << ">";
		int k;
		cin >> k;
		
		return k;
	}
}

/**
 * Slope value of a linear regression.
 *
 * @param n amount of data.
 * @param x summed values of x.
 * @param y summed values of y.
 * @param xy summed values of x*y.
 * @param x2 summed values of x^2.
 * @return the slope of the regression.
 */
double slope(int n, double x, double y, double xy, double x2) {
	return (n*xy-(x*y))/(n*x2-x*x);
}

/**
 * Intercept value of a linear regression.
 *
 * @param n amount of data.
 * @param y summed values of y.
 * @param slope the slope value.
 * @param x summed values of x.
 */
double intercept(int n, double y, double slope, double x) {
	return (y-slope*x)/n;
}

void print_header(string x, string y, string xy, string x2) {
	cout << left << setw(15) << " " << setw(15) << x
		     << setw(15) << y
		     << setw(15) << xy
		     << setw(15) << x2 << endl;
}

void print_entry(double x, double y, double xy, double x2) {
	cout << left << setw(15) << " " << fixed << 
				 setw(15) << setprecision(5) << x <<
				 setw(15) << setprecision(5) << y <<
				 setw(15) << setprecision(5) << xy <<
				 setw(15) << setprecision(5) << x2 << endl;
}

void print_sum_entry(double x, double y, double xy, double x2) {
	cout << left << setw(15) << "sum" 
		<< setw(15) << setprecision(5) << x
		<< setw(15) << setprecision(5) << y
		<< setw(15) << setprecision(5) << xy
		<< setw(15) << setprecision(5) << x2 << endl;
}

/**
 * Performs a linear regression based on Data values
 *
 * @param D the data.
 * @param x table lable for x.
 * @param y table lable for y.
 * @param xy table lable for x*y.
 * @param x2 table lable for x^2.
 * @return a pair of <slope, intercept> in double.
 */
pair<double, double> linear(Data &D, string x, string y, string xy, string x2) {
	double sum_x = 0;
	double sum_y = 0;
	double sum_xy = 0;
	double sum_x2 = 0;

	print_header(x, y, xy, x2);
	for (int i = 0; i < D.size(); ++i) {
		double xv = D.at(i).first;
		double yv = D.at(i).second;
		double xyv = xv*yv;
		double x2v = xv*xv;

		print_entry(xv, yv, xyv, x2v);

		sum_x += xv;
		sum_y += yv;
		sum_xy += xyv;
		sum_x2 += x2v;
	}

	print_sum_entry(sum_x, sum_y, sum_xy, sum_x2);

	double m_val = slope(D.size(), sum_x, sum_y, sum_xy, sum_x2);
	double y_val = intercept(D.size(), sum_y, m_val, sum_x);
	pair<double, double> sol = make_pair(m_val, y_val);

	return sol;
}

void linear_model(Data &D) {
	pair<double, double> sol = linear(D, "x", "y", "xy", "x^2");

	cout << "y = " << sol.first << "x + " << sol.second << endl;
}

void exponent_model(Data &D) {
	for (auto &dd : D) {
		dd.second = log(dd.second);
	}

	pair<double, double> sol = linear(D, "x", "ln(y)", "x ln(y)", "x^2");

	sol.second = exp(sol.second);

	cout << "y = " << sol.second << "e^(" << sol.first << "x)" << endl;
}

void power_model(Data &D) {
	for (auto &dd : D) {
		dd.first = log(dd.first);
		dd.second = log(dd.second);
	}

	pair<double, double> sol = linear(D, "ln(x)", "ln(y)", "ln(x) ln(y)", "ln^2(x)");

	sol.second = exp(sol.second);

	cout << "y = " << sol.second << "x^" << sol.first << endl;
}

void saturation_growth_model(Data &D) {
	for (auto &dd : D) {
		dd.first = 1/dd.first;
		dd.second = 1/dd.second;
	}

	pair<double, double> sol = linear(D, "1/x", "1/y", "1/(xy)", "(1/x)^2");

	sol.second = 1/sol.second;
	sol.first = sol.first*sol.second;

	cout << sol.second << "(x/(" << sol.first << "+x))" << endl;
}

