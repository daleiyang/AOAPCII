#include<stdio.h>
int main()
{
	int n, m, a, b;
	scanf("%d%d", &n, &m);
	a = (4 * n - m) / 2;
	b = n - a;
	//if(n < 0 || m < 0 || m % 2  == 1 || 2 * n > m)
	if(m % 2 == 1 || a < 0 || b < 0)
		printf("No answser\n");
	else
		printf("%d %d\n", a, b);
	return 0;
}

