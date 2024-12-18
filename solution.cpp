void almost_triangulation(int n, Matrix& A) {
    double square_root = 0;
    double eps = 10e-10;
    for (int col = 0; col < n - 1; ++col) {		
        for (int k = col + 2; k < n; ++k) {  
            double cos = A[col + 1][col];
            double sin = A[k][col];
            
            //std::cout << "cos = " << cos << " sin = " << sin << "\n";
            //A.Print();
            //std::cout << "col = " << col << " k = " << k << "\n";
            
            square_root = std::sqrt(cos * cos + sin * sin);
                if (square_root > eps) {
		        for (int i = 0; i < n; ++i) {
		            double reserve = A[col + 1][i];
                            A[col + 1][i] = (cos * A[col + 1][i] + sin * A[k][i]) / square_root;
                            A[k][i] = (-1 * sin * reserve + cos * A[k][i]) / square_root;
		        }

		        
		        for (int i = 0; i < n; ++i) {
		            double reserve = A[i][col + 1];
                            A[i][col + 1] = (cos * A[i][col + 1] + sin * A[i][k]) / square_root;
                            A[i][k] = (-1 * sin * reserve + cos * A[i][k]) / square_root;
		        }

				
			}
        }
    }
}

void LR_decomposition(int n, Matrix& A) {
    for (int i = 1; i < n; i++) { 
		
		A[i][i - 1] = A[i][i - 1] / A[i - 1][i - 1];
		for (int k = i; k < n; k++) {
			A[i][k] = A[i][k] - A[i][i - 1] * A[i - 1][k];
		}
		
	}
}

void LR_test(int n, Matrix& A, Matrix& C) {  // проверяет правильность LR разложения
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			C[i][j] = 0;
		}
	}

	for (int i = 0; i < n; i++) {
		C[0][i] = A[0][i];
	}

	for (int i = 1; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i <= j) {
				C[i][j] += A[i][j];
			} 
			if (i - 1 <= j) {
				C[i][j] += A[i][i - 1] * A[i - 1][j];
			}
		}
	}
}

void RL_mult(int n, Matrix& A, Matrix& LR) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			LR[i][j] = A[i][j];
		}
	}

	for (int i = 1; i < n; i++) {
		A[i][i - 1] = LR[i][i] * LR[i][i - 1];
	}

	for (int i = 0; i < n; i++) {
		for (int k = i; k < n - 1; k++) {
			A[i][k] = LR[i][k] + LR[i][k + 1] * LR[k + 1][k];
		}
	}
}

double eigen_norm(int n, Matrix& A) {
	double sum = 0;
	for (int i = 1; i < n; i++) {
		sum += fabs(A[i][i - 1]);
	}
	return sum;
}

void find_eigenvalue(int n, Matrix& A, Matrix& LR, double eps) {
	almost_triangulation(n, A);	
	
	while (eigen_norm(n, A) > eps) {
		LR_decomposition(n, A);
		RL_mult(n, A, LR);
                //std::cout << eigen_norm(n, A) << "\n";
	}
}
