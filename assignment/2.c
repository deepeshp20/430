#include <stdio.h>
#include <math.h>

double abs_value(double x)
{
    return (x < 0) ? -x : x;
}

double func(double x)
{
    return abs_value(x - 3) + (x - 2) * (x - 2);
}

int main()
{
    double a,b;

    printf("enter a and b:\n");
    scanf("%lf %lf",&a,&b);

    double tol = 0.001;
    double rho = (3-sqrt(5))/2;

    double x1 = a + rho * (b - a);
    double x2 = a + (1 - rho) * (b - a);

    double f1 = func(x1);
    double f2 = func(x2);

    int it = 0;
    while (tol < (b - a))
    {
        printf("%d %lf %lf\n", it++, a, b);

        if (f1 > f2)
        {
            a = x1;
            x1 = x2;
            f1 = f2;
            x2 = a + (1 - rho) * (b - a);
            f2 = func(x2);
        }
        else
        {
            b = x2;
            x2 = x1;
            f2 = f1;
            x1 = a + rho * (b - a);
            f1 = func(x1);
        }
    }
    printf("%d %lf %lf\n", it++, a, b);
    
    double pt = (a + b) / 2;
    printf("\nMinimum point: %lf\n", pt);
    printf("Minimum value: %lf\n", func(pt));

    return 0;
}