#include<stdio.h>
#include<math.h>

int main()
{
	int n;
	scanf("%d", &n);
	const double pi = acos(-1);
	double i = n / 180.0 * pi;
	printf("%lf %lf", sin(i), cos(i));
	return 0;
}

