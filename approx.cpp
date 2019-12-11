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
 */
double f(double x, double nim) {
	return 5*x*x*x + 17*x*x - nim*x - 6;
}

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

double midpoint(double a, double b, double fa, double fb) {
	return (a+b)/2.0;
}

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

double dfdx(double x, double nim) {
	return (f(x+0.00000001, nim) - f(x-0.00000001, nim))/(2*0.00000001);
}

void newton(int iter, double nim, double x0) {
	print_newton_header();
	for (int i = 1; i <= iter; ++i) {
		double x1 = x0 - f(x0, nim)/dfdx(x0, nim);

		print_newton_entry(i, x0, x1);

		x0 = x1;
	}
}

/*
int main() {
	//tabulation(-5, 5, 1, 20);
	//bisection(-5, 5, 1, 20, midpoint);
	//bisection(-5, 5, 1, 20, rf_mid);
	//secant(1, -5, 3, 15);
	//newton(10, 1, -5);
	return 0;
}
*/

