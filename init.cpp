#include <iostream>
#include <vector>
#include <iomanip>

int max(int i, int j) {
	if (i > j) {
		return i;
	}
	return j;
}

double f(int k, int n, int i, int j) {
	switch(k) {
		case 1:
			return n - max(i, j) + 1;
			break;
		case 2:
			if (i == j) {
				return 2;
			} else if (abs(i - j) == 1) {
				return -1;
			} else {
				return 0;
			}
			break;
		case 3:
			if (j == n) {
				return i;
			} else if (i == n) {
				return j;
			} else if (i == j) {
				return 1;
			} else {
				return 0;
			}
			break;
		case 4:
			return 1.0 / (i + j - 1);
			break;
	}
	return 0;
}

void init(Matrix& A, int n, int k) {
	for (int i = 0; i != n; ++i) {
		for (int j = 0; j != n; ++j) {
			A[i][j] = f(k, n, i + 1, j + 1);
		}
	}
}

void print(Matrix& A, int m) {
	int n = A.getSize();
	for (int i = 0; i < n and i < m; ++i) {
		for (int j = 0; j < n and j < m; ++j) {
			std::printf("%10.3e", A[i][j]);
			//std::cout << std::setprecision(10) << A[i][j];
			std::cout << " ";
		}
		std::cout << "\n";
	}

}

double nevyazka (const Matrix& A) {
	int n = A.getSize();
	double sum = 0;
	for (int i = 0; i < n; ++i) {
            sum += A[i][i];
        }

	return sum;
}
