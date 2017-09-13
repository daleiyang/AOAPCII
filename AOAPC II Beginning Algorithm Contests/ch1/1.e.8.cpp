#include<stdio.h>

int main()
{
/*
	int a;
	scanf("%d", &a);
	printf("%d", a);
*/

/*
	double a;
	scanf("%lf", &a);
	printf("%.80lf", a);
*/

	int a = 0, b = 0, c = 1, d = 1;
	printf("%d\n", a && b || c);

	printf("%d\n", !a && b);

	printf("%d\n", !c || d);

	if(c)
		if(b)
			printf("b\n");
		else
			printf("c\n");
	
	return 0;
}

