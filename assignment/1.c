#include <stdio.h>
#include <math.h>

int sgn(double val) {
    if (val == 0.0) return 0;
    if (val < 0) return -1;
    return 1;
}

double maximum(double x, double y) {
    return (x > y) ? x : y;
}

double minimum(double x, double y) {
    return (x < y) ? x : y;
}

double abs_value(double x) {
    return (x < 0) ? -x : x;
}

int main() {
    int numRows, numCols;

    printf("Enter the number of rows and columns: ");
    scanf("%d %d", &numRows, &numCols);

    numCols++; // Augmented column

    double matrix[numRows][numCols];

    printf("Enter the matrix elements:\n");
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            scanf("%lf", &matrix[i][j]);
        }
    }

    double beta[numCols], v[numRows], magnitude = 0, gamma = 0, solution[numCols - 1];

    for (int k = 0; k < numCols; k++) {
        beta[k] = 0;
        for (int i = k; i < numRows; i++) {
            magnitude += matrix[i][k] * matrix[i][k];
        }
        magnitude = sqrt(magnitude) * (-1) * sgn(matrix[k][k]);

        for (int i = 0; i < numRows; i++) {
            if (i < k) {
                v[i] = 0;
            } else if (i == k) {
                v[i] = matrix[i][i] - magnitude;
            } else {
                v[i] = matrix[i][k];
            }
            beta[k] += v[i] * v[i];
        }

        if (beta[k] != 0) {
            for (int j = k; j < numCols; j++) {
                for (int i = 0; i < numRows; i++) {
                    gamma += v[i] * matrix[i][j];
                }
                for (int i = 0; i < numRows; i++) {
                    matrix[i][j] -= (2 * gamma * v[i]) / beta[k];
                }
                gamma = 0;
            }
        }
        magnitude = 0;
    }

    for (int i = 0; i < numCols - 1; i++) {
        solution[i] = 0;
    }
    double temp = 0;

    if (matrix[numCols - 2][numCols - 2] == 0) {
        printf("The matrix has deficient rank.\n");
        return 0;
    }

    double maxDiagonal = matrix[0][0];
    double minDiagonal = abs_value(matrix[0][0]);

    for (int i = 0; i < numCols - 1; i++) {
        maxDiagonal = maximum(maxDiagonal, abs_value(matrix[i][i]));
        minDiagonal = minimum(minDiagonal, abs_value(matrix[i][i]));
    }

    printf("\nMaximum diagonal element: %lf\n", maxDiagonal);
    printf("Minimum diagonal element: %lf\n\n", minDiagonal);

    solution[numCols - 2] = matrix[numCols - 2][numCols - 1] / matrix[numCols - 2][numCols - 2];

    for (int i = numCols - 3; i >= 0; i--) {
        temp = 0;
        for (int j = numCols - 2; j > i; j--) {
            temp += solution[j] * matrix[i][j];
        }
        solution[i] = (matrix[i][numCols - 1] - temp) / matrix[i][i];
    }

    printf("Solutions:\n");
    for (int i = 0; i < numCols - 1; i++) {
        printf("%lf\n", solution[i]);
    }

    return 0;
}
