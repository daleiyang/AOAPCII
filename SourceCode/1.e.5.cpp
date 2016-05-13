#include<stdio.h>
int main()
{
	const int u = 95;
	int n;
	scanf("%d", &n);
	int s = n * u;
	if(s >= 300) printf("%.2lf", s * 0.85);
	else printf("%.2lf", s * 1.0);
	return 0;
}

