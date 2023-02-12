#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>
using namespace std;

typedef vector<vector<long>> Matrix;

long numberOfDigits(double n) {
	std::ostringstream strs;

	strs << n;
	return strs.str().size();
}

void printMatrix(const Matrix& M) {
	long max_len_per_column[M.size()];
	long n = M.size(), m = M[0].size();

	for (long j = 0; j < m; ++j) {
		long max_len {};

		for (long i = 0; i < n; ++i){
			long num_length {numberOfDigits(M[i][j])};
			if (num_length > max_len)
				max_len = num_length;
		}

		max_len_per_column[j] = max_len;
	}

	for (long i = 0; i < n; ++i)
		for (long j = 0; j < m; ++j)
			std::cout << (j == 0 ? "\n| " : "") << std::setw(max_len_per_column[j]) << M[i][j] << (j == m - 1 ? " |" : " ");

	std::cout << '\n';
}

long parseNumber(string line) {
	return (long) (line[0]-'0') / (long) (line[2]-'0');
}

Matrix enterMatrix(int numberParams) {
	Matrix matrix(numberParams, vector<long>(numberParams));
	string number;
	for (int i=0; i<numberParams; i++) {
		for (int j=0; j<numberParams; j++) {
			cin >> matrix[i][j];
		}
	}
	return matrix;
}

Matrix createMatrixRisk(const Matrix& matrix) {
    int size = matrix.size();
    Matrix newMatrix(size, vector<long>(size));
    for (int i=0; i<size; i++) {
        newMatrix[i][i] = matrix[i][i];
		for (int j=0; j<size; j++) {
			newMatrix[j][i] = matrix[i][i] - matrix[j][i];
		}
	}
    return newMatrix;
}

vector<int> getSolutions(const Matrix& matrix) {
    vector<int> solutions;
    vector<long> maximums;
    for (int i=0; i<matrix.size(); i++) {
        maximums.push_back(*max_element(matrix[i].begin(), matrix[i].end()));
    }
    long min = *min_element(maximums.begin(), maximums.end());
    for (int i=0; i<maximums.size(); i++) {
        if (maximums[i] == min) {
            solutions.push_back(i+1);
        }
    }
    return solutions;
}

int main() {
	cout << "Enter number of alternative" << endl;
	int numberA; cin >> numberA;

    cout << "Enter matrix of alternative" << endl;
    Matrix matrixAlternatives = enterMatrix(numberA);

    cout << "Matrix of alternatives:" << endl;
    printMatrix(matrixAlternatives);

    Matrix matrixRisks = createMatrixRisk(matrixAlternatives);

    cout << "Matrix of risks" << endl;
    printMatrix(matrixRisks);

    vector<int> solutions = getSolutions(matrixRisks);
    for (int i=0; i<solutions.size(); i++) {
        cout << "The optimal alternative - " << solutions[i] << endl;
    }


    return 0;
}