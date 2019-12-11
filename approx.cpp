#include <iostream>
#include <iomanip>
#include <string>
#include <functional>

using std::string;
using std::cout;
using std::endl;
using std::left;
using std::setw;
using std::setprecision;
using std::fixed;
using std::function;
using std::cin;

namespace approx {
	int prompt() {
		cout << "1) Tabulasi\n2) Biseksi\n3) Regula falsi\n4) Secant\n5) Newton-Raphson" << endl;
		cout << ">";
		int k;
		cin >> k;
		
		return k;
	}
}

/**
 * The main function, as defined in past slides.
 *
 * @param x value of x
 * @param nim sum of two last digits 
 * 	  of the student id. If it exceeds 10, 
 * 	  sum those two digits.
 * @return the value of the function.
 */
double f(double x, double nim) {
	return 5*x*x*x + 17*x*x - nim*x - 6;
}

/**
 * From a collection of tabular data, determine the next bound suitable.
 * It is said suitable if those to points crosses the X axis, meaning a solution exists between 
 * those two points. Assume the function is continuous.
 *
 * @param xvals x coordinates.
 * @param yvals values of x coordinates.
 * @param low the low bound.
 * @param high the high bound.
 */
void set_bounds(double *xvals, double *yvals, double &low, double &high) {
	for (int index = 0; index <= 10; ++index) {
		double pivot = yvals[index];
		if (pivot < 0) {
			if (index == 0) {
				if (yvals[1] >= 0) {
					low = xvals[index];
					high = xvals[1];
				} else {
					// not eligible
				}
			} else if (index == 10) {
				if (yvals[9] >= 0) {
					low = xvals[index];
					high = xvals[9];
				} else {
					// not eligible
				}
			} else {
				if (yvals[index-1] >= 0) {
					low = xvals[index];
					high = xvals[index-1];
				} else if (yvals[index+1] >= 0) {
					low = xvals[index];
					high = xvals[index+1];
				} else {
					// not eligible
				}
			}
		}
	}
}

/**
 * Prints a table. Assume number of elements is always 11.
 * This is because counting from n_0 to n_t with 10 increments always results in 11 elements.
 *
 * n_0+0*i, n_0+1*i, ... 9 more times, n_t -> 11 elements.
 *
 * @param xlist list of x values.
 * @param ylist list of mapped values of x. Note that f : xlist -> ylist is not neccessarily bijective.
 */
void print_table(double *xlist, double *ylist) {
	cout << left << setw(20) << "x" << setw(20) << "f(x)" << endl;

	for (int i = 0; i <= 10; ++i) {
		cout << left << setw(20) << setprecision(10) << fixed << xlist[i] << setw(20) << setprecision(10) << fixed << ylist[i] << endl;
	}
}

/**
 * Prints the table on each iteration. Assuming solution exists between low_bound and high_bound.
 *
 * @param low_bound the low bound
 * @param high_bound the high bound
 * @param nim student id
 * @param iter_count how many times to iterate through tabulation
 * @return true if tabulation is successful, false otherwise.
 */
bool tabulation(double low_bound, double high_bound, double nim, int iter_count) {
	double increment = 1.0;

	if (low_bound > high_bound) {
		return false;
	} else {
		for (int iteration = 1; iteration <= iter_count; ++iteration) {
			cout << "Iterasi " << iteration << endl;
			
			double x_in[11];
			double x_out[11];

			for (int index = 0; index <= 10; ++index) {
				x_in[index] = low_bound + (increment*index);
				x_out[index] = f(x_in[index], nim);
			}
			print_table(x_in, x_out);

			double new_low_bound;
			double new_high_bound;
			set_bounds(x_in, x_out, new_low_bound, new_high_bound);

			low_bound = new_low_bound;
			high_bound = new_high_bound;
			increment /= 10;
		}

		return true;
	}
}	

void print_bisection_header() {
	cout << left << setw(10) << "iterasi" << setw(10) << "a" <<
						setw(10) << "b" <<
						setw(10) << "c" <<
						setw(10) << "fa" << 
						setw(10) << "fb" << 
						setw(10) << "fc" <<
						endl;
}

void print_bisection_entry(int iteration, double a, double b, double c, double fa, double fb, double fc) {
	cout << left << setw(10) << iteration << fixed << setw(10) << setprecision(4) << a
					     << setw(10) << setprecision(4) << b
					     << setw(10) << setprecision(4) << c
					     << setw(10) << setprecision(4) << fa
					     << setw(10) << setprecision(4) << fb
					     << setw(10) << setprecision(4) << fc
					     << endl;
}

/**
 * Computing two values between a and b.
 * 
 * @param a value of a
 * @param b value of b
 * @param fa compatibility for function arguments.
 * @param fb compatibility for function arguments.
 * @return the value between a and b.
 */
double midpoint(double a, double b, double fa, double fb) {
	return (a+b)/2.0;
}

/**
 * Performs a bisection using specified function as the next point.
 *
 * Such functions can be midpoint function or a regula falsi function.
 *
 * @param low_bound the current low bound of function.
 * @param high_bound the current high bund of function.
 * @param nim numeralized identification number.
 * @param iter_count iteration count.
 * @param cf specifying function for the next point.
 */
void bisection(double low_bound, double high_bound, double nim, int iter_count, function<double (double, double, double, double)> cf) {
	print_bisection_header();
	for (int i = 1; i <= iter_count; ++i) {
		double a = low_bound;
		double b = high_bound;
		double fa = f(a, nim);
		double fb = f(b, nim);

		double c = cf(a, b, fa, fb);
		double fc = f(c, nim);

		print_bisection_entry(i, a, b, c, fa, fb, fc);

		if (fb*fc < 0) {
			if (b < c) {
				low_bound = b;
				high_bound = c;
			} else {
				low_bound = c;
				high_bound = b;
			}
		} else {
			if (a < c) {
				low_bound = a;
				high_bound = c;
			} else {
				low_bound = c;
				high_bound = a;
			}
		}
	}		
}

/**
 * Regula falsi function to determine the next point in a bisection.
 *
 * @param a the value of a.
 * @param b the value of b.
 * @param fa the value of f(a).
 * @param fb the value of f(b).
 * @return the next point based on the regula falsi method.
 */
double rf_mid(double a, double b, double fa, double fb) {
	return (fb*a-fa*b)/(fb-fa);
}

void print_secant_header() {
	cout << left << setw(10) << "iterasi" << fixed << setw(15) << "x_0" 
					       << setw(15) << "x_1" 
					       << setw(15) << "x_new" << endl;
}

void print_secant_entry(int iter, double x0, double x1, double xn) {
	cout << left << setw(10) << iter << fixed << setw(15) << setprecision(8) << x0 
	       					  << setw(15) << setprecision(8) << x1 
					  	  << setw(15) << setprecision(8) << xn << endl;	  
}

/**
 * Secant method of determining roots by picking two points, assuming a solution exists.
 *
 * @param nim numeralized identification number.
 * @param x0 initial guess x0.
 * @param x1 initial guess x1.
 * @param iter_count iteration count.
 */
void secant(double nim, double x0, double x1, int iter_count) {
	print_secant_header();

	for (int i = 1; i <= iter_count; ++i) {
		double fx0 = f(x0, nim);
		double fx1 = f(x1, nim);

		double xn;
		if (fx1 == fx0) {
			xn = x1;
		} else {
			xn = x1-fx1*((x1-x0)/(fx1-fx0));
		}

		print_secant_entry(i, x0, x1, xn);
		
		x0 = x1;
		x1 = xn;	
	}
}

void print_newton_header() {
	cout << left << setw(10) << "iterasi" << setw(15) << "x_0" << setw(15) << "x_n" << endl;
}

void print_newton_entry(int iter, double x0, double xn) {
	cout << left << setw(10) << iter << fixed << setw(15) << setprecision(8) << x0
						  << setw(15) << setprecision(8) << xn << endl;
}

/**
 * Calculate an approximate derivative of f(x).
 *
 * @param x the value of x.
 * @param nim numeralized identification number.
 */
double dfdx(double x, double nim) {
	return (f(x+0.00000001, nim) - f(x-0.00000001, nim))/(2*0.00000001);
}

/**
 * Newton's method of root finding.
 *
 * @param iter iteration count.
 * @param nim numeralized identification number.
 * @param x0 initial guess.
 */
void newton(int iter, double nim, double x0) {
	print_newton_header();
	for (int i = 1; i <= iter; ++i) {
		double x1 = x0 - f(x0, nim)/dfdx(x0, nim);

		print_newton_entry(i, x0, x1);

		x0 = x1;
	}
}
