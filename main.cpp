#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <pthread.h>

#include "matrix.hpp"
#include "init.cpp"
#include "solution.cpp"



class MyException {
  private:
	std::string exc;
	
  public:	
	MyException() : exc("File opening failure\n") {}
	MyException(std::string str) : exc(str) {}
		
	const std::string what() {
		return exc;
	}
};

class File {
  private:
	std::FILE* f;

  public:
	File(const std::string& name) {
		if (f = std::fopen(name.c_str(), "r"); f == nullptr) {
			throw MyException();
		}
	}

	~File() noexcept {
		std::fclose(f);
	}

	void Read (Matrix& A) const {
		int n = A.getSize();
		for (int i = 0; i != n; ++i) {
			for (int j = 0; j != n; ++j) {
				std::fscanf(f, "%lf", &A[i][j]);
			}
		}
	}
};


Matrix operator * (const Matrix& A, const Matrix& B) {
	int n = A.getSize();
	Matrix C(n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < n; ++k) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	return C;
}


int main(int argc, char* argv[]) {
	int n, m, k;
        n = argc;
	double eps;
	std::string file_name;

	n = std::atoi(argv[1]);
	eps = std::atof(argv[2]);
	m = std::atoi(argv[3]);
	k = std::atoi(argv[4]);

	Matrix A (n);
	
	if (k != 0) {
		init(A, n, k);
	} else {
		file_name = argv[5];
		try {
			File file(file_name);
			file.Read(A);
		} catch (MyException& exc) {
			std::cout << exc.what() << "\n";
			return 0;
		}
	}
	
	Matrix C (n);
	Matrix B = A;

	print(B, m);
    std::cout << "\n";
	/*
    almost_triangulation(n, B);
	
	std::cout << "\nNevyazka dlya pochti treugolnoy: " << nevyazka(A) - nevyazka(B) << "\n";
	print(B, m);
	std::cout << "\n";

	Matrix D = B;

	LR_decomposition(n, B);
	LR_test(n, B, C);	

	double norm = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			norm = norm + (C[i][j] - D[i][j]) * (C[i][j] - D[i][j]);
		}
	}	
    eps = eps;
	*/

    find_eigenvalue(n, B, C, eps);
	   
	//std::cout << "\nResult of LR test: " << norm << "\n";
	print(C, m);
	std::cout << "\n";

	std::cout << "\nNevyazka: " << nevyazka(A) - nevyazka(B) << "\n";
	return 0;
}
