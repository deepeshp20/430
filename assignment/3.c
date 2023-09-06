#include <stdio.h>
#include <math.h>

// Define the maximum dimensions
#define MAX_DIM 10

// Define global variables
double A[MAX_DIM][MAX_DIM];
double b[MAX_DIM];
double c;

// Function to calculate the objective function value for the given x
double calculateObjectiveFunctionValue(double x1, double x2) {
    double f = 0.5 * x1 * (A[0][0] * x1 + A[0][1] * x2) + 0.5 * x2 * (A[1][0] * x1 + A[1][1] * x2) - x1 * b[0] - x2 * b[1] + c;
    return f;
}

int main() {
    // Define the tolerance
    double tolerance = 1e-5;

    // Read data from the "SD.dat" file
    FILE *file = fopen("SD.dat", "r");
    if (file == NULL) {
        printf("Error: Unable to open the file 'SD.dat'.\n");
        return 1;
    }

    // Read the dimension from the file
    int dim;
    fscanf(file, "%d", &dim);

    // Read matrix A from the file
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            fscanf(file, "%lf", &A[i][j]);
        }
    }

    // Read vector b from the file
    for (int i = 0; i < dim; i++) {
        fscanf(file, "%lf", &b[i]);
    }

    // Read constant c from the file
    fscanf(file, "%lf", &c);

    // Read the initial point x0 from the file
    double x0[dim];
    for (int i = 0; i < dim; i++) {
        fscanf(file, "%lf", &x0[i]);
    }

    fclose(file);

    // Initialize variables
    double x[dim];
    double residual[dim];

    double stepSize;
    double normResidual;

    // Set the initial values
    for (int i = 0; i < dim; i++) {
        x[i] = x0[i];
    }

    int iteration = 0;

    // Perform steepest-descent iterations
    do {
        // Calculate the residual vector
        for (int i = 0; i < dim; i++) {
            residual[i] = b[i] - (A[i][0] * x[0] + A[i][1] * x[1]);
        }

        // Calculate the step size
        double numerator = 0.0;
        double denominator = 0.0;

        for (int i = 0; i < dim; i++) {
            numerator += residual[i] * residual[i];
            for (int j = 0; j < dim; j++) {
                denominator += residual[i] * (A[i][j] * residual[j]);
            }
        }

        stepSize = numerator / denominator;

        // Update x_k+1
        for (int i = 0; i < dim; i++) {
            x[i] = x[i] + stepSize * residual[i];
        }

        // Calculate the norm of the residual vector
        normResidual = sqrt(numerator);

        // Print intermediate values
        printf("Iteration %d: x = (%lf, %lf), ||residual|| = %lf, f(x) = %lf\n", iteration, x0[0], x0[1], normResidual, calculateObjectiveFunctionValue(x[0], x[1]));

        iteration++;
    } while (normResidual > tolerance);

    // Print the minimum point and minimum value
    printf("Minimum point: x = (%.8lf, %.8lf)\n", x[0], x[1]);
    printf("Minimum value: f(x) = %.7lf\n", calculateObjectiveFunctionValue(x[0], x[1]));

    return 0;
}
