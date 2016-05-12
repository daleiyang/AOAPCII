#include<stdio.h>
#include<math.h>

int main()
{
	double r, h;
	const double pi = acos(-1);
	scanf("%lf%lf", &r, &h);
	printf("Area = %.3f\n", 2 * pi * r * r + 2 * pi * r * h);
	return 0;
}

