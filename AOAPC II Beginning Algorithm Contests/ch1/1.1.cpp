#include<stdio.h>
#include<math.h>

int main()
{
	printf("%d\n", 1+2);
	printf("%d\n", 3-4);
	printf("%d\n", 5*6);
	printf("%d\n", 8/4);
	printf("%d\n", 8/5);
	printf("%.1f\n", 8.0/5.0);
	printf("%.2f\n", 8.0/5.0);
	printf("%f\n", 8.0/5.0);
	//printf("%.1f\n", 8/5);
	//printf("%d\n", 8.0/5.0);
	printf("%.8f\n", 1 + 2 * sqrt(3) / (5 - 0.3));
	return 0;
}

