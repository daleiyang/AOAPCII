#include<stdio.h>
int main()
{
	int n;
	scanf("%d", &n);
	long long n2 = n;
	int count = 0;
	while(n2 > 1){
		if(n2 % 2 ==1)
			n2 = n2 * 3 + 1;
		else
			n2 = n2 / 2;
/*
		printf("%lld\n", n);
*/
		count++;
	}
	printf("%d\n", count);
	return 0;
}

