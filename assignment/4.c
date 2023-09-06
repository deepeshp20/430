#include <stdio.h>
#include <math.h>

void multiply(int n, double A[][n], double x[n], double res[n]) {
    for (int i = 0; i < n; i++) {
        res[i] = 0.0;
        for (int j = 0; j < n; j++) {
            res[i] += A[i][j] * x[j];
        }
    }
}

double dot(int n, double a[n], double b[n]) {
    double result = 0.0;
    for (int i = 0; i < n; i++) {
        result += a[i] * b[i];
    }
    return result;
}

double f(int n, double x[n], double A[][n], double b[n], double c) {
    double res[n], Axk[n];
    multiply(n, A, x, Axk);

    double fValue = 0.5 * dot(n, x, Axk);
    fValue -= dot(n, b, x);
    fValue += c;

    return fValue;
}

int main() {
    FILE *dataFile = fopen("CG.dat", "r");
    if (dataFile == NULL) {
        printf("File not found!\n");
        return 0;
    }

    int n;
    fscanf(dataFile, "%d", &n);

    double A[n][n], b[n], x[n], r_k[n], s_k[n], Axk[n], c;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(dataFile, "%lf", &A[i][j]);
        }
        fscanf(dataFile, "%lf", &b[i]);
    }

    fscanf(dataFile, "%lf", &c);

    for (int i = 0; i < n; i++) {
        fscanf(dataFile, "%lf", &x[i]);
    }

    multiply(n, A, x, Axk);

    for (int i = 0; i < n; i++) {
        r_k[i] = b[i] - Axk[i];
        s_k[i] = r_k[i];
    }

    double alpha, temp[n], gamma;

    printf("Iteration\t x1_k\t x2_k\t ||r_k||\t f_k\n");

    for (int k = 0; k <= n; k++) {
        printf("%02d\t %e\t %e\t %e\t %e\n", k, x[0], x[1], sqrt(dot(n, r_k, r_k)), f(n, x, A, b, c));

        multiply(n, A, s_k, temp);
        alpha = dot(n, r_k, r_k) / dot(n, s_k, temp);

        for (int i = 0; i < n; i++) {
            x[i] += alpha * s_k[i];
        }

        double t1 = dot(n, r_k, r_k);

        multiply(n, A, x, Axk);

        for (int i = 0; i < n; i++) {
            r_k[i] = b[i] - Axk[i];
        }

        double t2 = dot(n, r_k, r_k);
        gamma = t2 / t1;

        for (int i = 0; i < n; i++) {
            s_k[i] = r_k[i] + gamma * s_k[i];
        }
    }

    printf("Minimum point = (");

    for (int i = 0; i < n; i++) {
        printf(" %e,", x[i]);
    }
    printf("), Minimum value = %e\n", f(n, x, A, b, c));

    fclose(dataFile);
    return 0;
}
