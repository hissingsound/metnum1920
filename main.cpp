#include <iostream>

#include "approx.cpp"
#include "nimutils.cpp"
#include "equations.cpp"
#include "regression.cpp"

#include <utility>

using namespace std;

/**
 * Main prompt. Displayed once and once only when launching the application.
 *
 * @return User's selection in integer.
 */
int prompt() {
	cout << "Applications of various numerical methods" << endl;
	cout << "by Caroline, Muslimah, and Steven Hans." << endl;
	cout << "Choose an option: " << endl;
	cout << "1) Aproksimasi\n2) Sistem persamaan linear\n3) Regresi linear" << endl;
	cout << ">";
	int k;
	cin >> k;
	
	return k;
}

int main() {
	int choice = prompt();
	
	if (choice == 1) {
		cout << "Memilih bagian aproksimasi." << endl;
		double nim = prompt_nim();
		int choice_approx = approx::prompt();
		
		if (choice_approx == 1) {
				cout << "Memilih tabulasi." << endl;
				cout << "Tabulasi dilakukan dengan jumlah entri yang tetap tiap iterasi." << endl;
				cout << "Asumsikan ada solusi diantara batas bawah l_b dan l_b+10" << endl;
				cout << "Asumsikan batas bawah adalah bilangan bulat." << endl;
				cout << "Masukkan batas bawah: ";
				double lb;
				cin >> lb;
				
				cout << "Masukkan jumlah iterasi: ";
				int iter_count;
				cin >> iter_count;
				tabulation(lb, lb+10, nim, iter_count);
		} else if (choice_approx == 2) {
				cout << "Memilih biseksi." << endl;
				cout << "Biseksi dilakukan dengan mengambil titik tengah dari kedua titik, dengan asumsi terdapat solusi di antara kedua titik tersebut." << endl;
				cout << "Batas bawah: ";
				double lb;
				cin >> lb;
				cout << "Batas atas: ";
				double ub;
				cin >> ub;
				
				cout << "Masukkan jumlah iterasi: ";
				int iter_count;
				cin >> iter_count;
				bisection(lb, ub, nim, iter_count, midpoint);
		} else if (choice_approx == 3) {
				cout << "Memilih Regula falsi." << endl;
				cout << "Regula falsi dilakukan sama seperti biseksi, namun dengan mengambil titik tengah dengan rumus yang berbeda." << endl;
				cout << "Batas bawah: ";
				double lb;
				cin >> lb;
				cout << "Batas atas: ";
				double ub;
				cin >> ub;
				
				cout << "Masukkan jumlah iterasi: ";
				int iter_count;
				cin >> iter_count;
				bisection(lb, ub, nim, iter_count, rf_mid);
		} else if (choice_approx == 4) {
				cout << "Memilih metode secant." << endl;
				cout << "x1: ";
				double x0;
				cin >> x0;
				cout << "x2: ";
				double x1;
				cin >> x1;
				cout << "Masukkan jumlah iterasi: ";
				int iter_count;
				cin >> iter_count;
				
				secant(nim, x0, x1, iter_count);
		} else if (choice_approx == 5) {
				cout << "Memilih metode Newton-Raphson." << endl;
				cout << "Tebakan awal: ";
				double x0;
				cin >> x0;
				
				cout << "Masukkan jumlah iterasi: ";
				int iter_count;
				cin >> iter_count;
				
				newton(iter_count, nim, x0);
		} else {
				cout << "Entri tidak ada.";
		}
	} else if (choice == 2) {
		cout << "Memilih bagian sistem persamaan linear" << endl;
		
		Matrix v;
		cout << "Input jumlah variabel: ";
		
		int n;
		cin >> n;
		
		// Inputting to the coefficient matrix.
		for (int i = 0; i < n; ++i) {
			vector<double> vd;
			cout << "Koefisien-koefisien baris ke-" << i+1 << ": ";
			for (int j = 0; j < n; ++j) {
				int val;
				cin >> val;
				vd.push_back(val);
			}

			v.push_back(vd);
		}
		
		// Inputting to the result matrix.
		vector<double> vals;
		cout << "Input solusi-solusi persamaan: ";
		for (int i = 0; i < n; ++i) {
			int vl;
			cin >> vl;
			vals.push_back(vl);
		}
		
		int choice_eqn = equations::prompt();
		
		if (choice_eqn == 1) {
				augment_matrix(v, vals);
				gauss(v);
				backwards_sub(v);
		} else if (choice_eqn == 2) {
				augment_matrix(v, vals);
				gauss(v);
				backwards_sub(v, true);
		} else if (choice_eqn == 3) {
				vector<Matrix> ans = crout(v);
				
				Matrix L = ans[0];
				Matrix U = ans[1];
				
				augment_matrix(L, vals);
				
				vector<double> y_ans = forward_sub(L);
				
				cout << "Nilai-nilai Y: ";
				for (auto &yv : y_ans) {
					cout << yv << " ";
				}
				cout << endl;
				
				augment_matrix(U, y_ans);
				
				vector<double> result = backwards_sub(U);
		} else if (choice_eqn == 4) {
				vector<Matrix> ans = doolittle(v);
				
				Matrix L = ans[0];
				Matrix U = ans[1];
				
				augment_matrix(L, vals);
				
				vector<double> y_ans = forward_sub(L);
				
				cout << "Nilai-nilai Y: ";
				for (auto &yv : y_ans) {
					cout << yv << " ";
				}
				cout << endl;
				
				augment_matrix(U, y_ans);
				
				vector<double> result = backwards_sub(U);
		} else {
				cout << "Entri tidak ada." << endl;
		}
	} else if (choice == 3) {
		cout << "Memilih bagian regresi." << endl;
		
		int choice_regression = regression::prompt();
		
		Data D;
		
		int n;
		cout << "Jumlah data: ";
		cin >> n;
		
		cout << "Input data x y: ";
		
		while (n--) {
			double x;
			double y;
			cin >> x >> y;
			D.push_back(make_pair(x, y));
		}
		
		switch(choice_regression) {
			case 1:
				linear_model(D);
				break;
			case 2:
				exponent_model(D);
				break;
			case 3:
				power_model(D);
				break;
			case 4:
				saturation_growth_model(D);
				break;
			default:
				cout << "Entri tidak ada." << endl;
				break;
		}
	} else {
		cout << "Entri tidak ada. Keluar dari program." << endl;
	}
	
	return 0;
}

