#include <iostream>
#include <iomanip>
#include <vector>
#include <utility>
#include <cmath>
#include <map>

using namespace std;

ostream& operator<<(ostream& out, vector<vector<double>> &v) {
	for (int i = 0; i < v.size(); ++i) {
		for (int j = 0; j < v.at(0).size(); ++j) {
			cout << left << fixed << setw(7) << setprecision(3) << v[i][j] << " ";
		}
		cout << endl;
	}

	return out;
}

void gauss(vector<vector<double>> &m) {
	int sz = m.size();

	cout << m << endl;
	// max of var-n
	for (int column = 0; column < sz; ++column) {
		
		double mx = abs(m[column][column]);
		int mx_index = column;

		// max col with index
		// check each row from column index+1 to end
		for (int row = column+1; row < sz; ++row) {
			double mx_val = abs(m[row][column]);
			
			if (mx_val > mx) {
				mx = mx_val;
				mx_index = row;
			}
		}

		// swap row=mx_index with row=column
		// swap each columns
		for (int c_i = 0; c_i < m[0].size(); ++c_i) {
			double temp = m[column][c_i];
			m[column][c_i] = m[mx_index][c_i];
			m[mx_index][c_i] = temp;
		}

		cout << "after swapped: " << endl;
		cout << m << endl;

		// from row=column to endrow
		// eliminate column=column.
		
		double pivot_val = m[column][column];
		cout << "pivot value is " << pivot_val << endl;
		for (int r = column+1; r < sz; ++r) {
			// 5 3 4 5
			// 2 2 1 4
			//
			// ratio is 2/5
			// ratio is currentcol/pivotval
			// 5 3 4 5 is all multiplied by ratio
			// 2 ... ... ...
			//
			// subtract.
			//
			//
			double ratio = m[r][column]/pivot_val;
			cout << "ratio is " << m[r][column] << "/pivot" << endl;
			for (int c = column; c < m[0].size(); ++c) {
				m[r][c] -= (ratio*m[column][c]);
			}

			cout << m << endl;
		}
	}
}

void backwards_sub(vector<vector<double>> &m, bool jordan=false) {
	map<int, double> ans;

	//start from the lowest row
	
	if (jordan) {
		cout << "reducing rows for: " << endl;
	} else {
		cout << "performing backwards subsitution for: " << endl;
	}

	cout << m << endl;
	for (int r = m.size()-1; r >= 0; --r) {
		// reduce from rightmost col to col=row
		for (int c = m.at(0).size()-1-1; c > r; --c) {
			m[r][m.at(0).size()-1] -= (ans[c]*m[r][c]);
			
			if (jordan) {
				m[r][c] = 0;
			}
		}

		ans[r] = m[r][m.at(0).size()-1]/m[r][r];

		// marking
		if (jordan) {
			m[r][m.at(0).size()-1] = ans[r];
			m[r][r] = 1;
			cout << m << endl;
		}
	}

	cout << "ans: ";
	for (int i = 0; i < m.size(); ++i) {
		cout << fixed << setw(7) << setprecision(3) << ans[i] << " ";
	}
	cout << endl;
}

int main() {
	vector<vector<double>> v = {{-3, 2, -6, 6}, {5, 7, -5, 6}, {1, 4, -2, 8}};

	gauss(v);
	backwards_sub(v, true);
	return 0;
}
