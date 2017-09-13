#include<stdio.h>
#include<math.h>

int main()
{
	int a;
	a = 11111*11111;
	printf("%d\n", a);

	double b;
	b = 111111111.0*111111111.0;
	printf("%lf\n", b);

	printf("%.2lf\n", sqrt(-10));

	double x = 1.0/0.0;
	printf("%lf\n", x);

	double y = 0.0/0.0;
	printf("%lf\n", y);

	int z = 1/0;
	printf("%d\n", z);

	return 0;
}
