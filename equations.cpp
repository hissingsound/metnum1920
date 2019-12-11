#include <iostream>
#include <iomanip>
#include <vector>
#include <utility>
#include <cmath>
#include <map>

using namespace std;

typedef vector<vector<double>> Matrix;

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

vector<double> forward_sub(Matrix &m) {
	map<int, double> ans;

	//start from the highest row
	cout << "performing forward substitution for: " << endl;

	cout << m << endl;
	
	for (int r = 0; r < m.size(); ++r) {
		// reduce from leftmost col to col+row
		for (int c = 0; c < r; ++c) {
			m[r][m.at(0).size()-1] -= (ans[c]*m[r][c]);
			
			m[r][c] = 0;
		}

		ans[r] = m[r][m.at(0).size()-1]/m[r][r];
		
		m[r][m.at(0).size()-1] = ans[r];
		m[r][r] = 1;
		cout << m << endl;
	}

	vector<double> vd;
	for (int r = 0; r < m.size(); ++r) {
		vd.push_back(ans[r]);
	}
	return vd;
}

vector<double> backwards_sub(Matrix &m, bool jordan=false) {
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

	vector<double> vd;
	for (int r = 0; r < m.size()-1; ++r) {
		vd.push_back(ans[r]);
	}
	return vd;
}

vector<Matrix> crout(Matrix &v) {
	vector<Matrix> ans;

	int n = v.size();

	Matrix L;
	Matrix U;

	vector<double> empty_row(n, 0);
	for (int i = 0; i < n; ++i) {
		L.push_back(empty_row);
		U.push_back(empty_row);
	}

	for (int k = 0; k < n; ++k) {
		double sum = 0;
		
		// L does not contain marking unlike doolittle
		// performing multiplication sum and dividing
		for (int m = 0; m < k; ++m) {
			sum += (L[k][m]*U[m][k]);
		}
		L[k][k] = v[k][k]-sum;

		for (int j = k; j < n; ++j) {
			sum = 0;

			for (int m = 0; m < k; ++m) {
				sum += (L[k][m]*U[m][j]);
			}

			U[k][j] = (v[k][j]-sum)/L[k][k];
		}

		for (int i = k+1; i < n; ++i) {
			sum = 0;

			for (int m = 0; m < k; ++m) {
				sum += (L[i][m]*U[m][k]);
			}

			L[i][k] = (v[i][k]-sum)/U[k][k];
		}
	}

	ans.push_back(L);
	ans.push_back(U);

	return ans;
}

vector<Matrix> doolittle(Matrix &v) {
	vector<Matrix> ans;

	Matrix L;
	Matrix U;

	vector<double> empty_row(v.at(0).size(), 0);
	for (int i = 0; i < v.size(); ++i) {
		L.push_back(empty_row);
		U.push_back(empty_row);
	}

	// mark L diagonal to 1
	
	for (int i = 0; i < L.size(); ++i) {
		L.at(i).at(i) = 1;
	}

	
	for (int pivot_row = 0; pivot_row < L.size(); ++pivot_row) {
		// solve for upper triangular first
		for (int column = pivot_row; column < L.at(0).size(); ++column) {
			double multiplication_sum = 0;
			for (int row = 0; row < pivot_row; ++row) {
				multiplication_sum += (L[pivot_row][row]*U[row][column]);
			}
			
			U[pivot_row][column] = v[pivot_row][column]-multiplication_sum;
		}

		
		// then solve for lower triangular
		// because main diagonal is already defined, we skip to pivot_row+1
		for (int row = pivot_row+1; row < L.size(); ++row) {
			double multiplication_sum = 0;
			for (int column = 0; column < pivot_row; ++column) {
				multiplication_sum += (L[row][column]*U[column][pivot_row]);
			}

			L[row][pivot_row] = (v[row][pivot_row]-multiplication_sum)/U[pivot_row][pivot_row];
		}
	}

	ans.push_back(L);
	ans.push_back(U);

	return ans;

}

/*
int main() {
	Matrix v;
	
	cout << "input n: ";
	int n;
	cin >> n;

	for (int i = 0; i < n; ++i) {
		vector<double> vd;
		for (int j = 0; j < n; ++j) {
			int val;
			cin >> val;
			vd.push_back(val);
		}

		v.push_back(vd);
	}

	vector<double> vals;
	cout << "input ans: ";
	for (int i = 0; i < n; ++i) {
		int vl;
		cin >> vl;
		vals.push_back(vl);
	}

	//gauss(v);
	//backwards_sub(v, true);
	
	vector<Matrix> ans = crout(v);

	Matrix L = ans[0];
	Matrix U = ans[1];

	// solving for LY = B
	// using forward sub
	
	Matrix augmented_L = L;
	
	for (int r = 0; r < L.size(); ++r) {
		augmented_L.at(r).push_back(vals.at(r));
	}

	vector<double> y_ans = forward_sub(augmented_L);

	for (auto &yv : y_ans) {
		cout << yv << " ";
	}
	//cout << "end of y vals" << endl;

	Matrix augmented_U = U;
	
	for (int r = 0; r < U.size(); ++r) {
		augmented_U.at(r).push_back(y_ans.at(r));
	}

	vector<double> result = backwards_sub(augmented_U);

	return 0;
}
*/
