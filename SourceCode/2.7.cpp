#include<stdio.h>
int main()
{
	int n;
	int sum = 0;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		int factorial = 1;
		for(int j = 1; j <= i; j++)
			factorial *= j;
		sum += factorial;
	}
	printf("%d", sum % 1000000);
	return 0;
}

