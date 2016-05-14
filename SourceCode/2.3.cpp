#include<stdio.h>
int main()
{
	for(int x = 1; ; x++){
		int n = x * x;
		if(n < 1000) continue;
		if(n > 9999) break;
		int hi = n / 100;
		int lo = n  % 100;
		if(hi/10 == hi%10 && lo/10 == lo%10)
			printf("%d\n", n);
	}
	return 0;
}

