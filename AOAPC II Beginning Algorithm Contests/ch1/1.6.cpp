#include<stdio.h>
int main()
{
	int n, m;
	scanf("%d", &n);
	//printf("%d%d%d",  n%10 ,n/10%10 ,n/100);
	m = (n%10)*100 + (n/10%10)*10 + n/100;;
	printf("%.3d", m);
	return 0;
}
