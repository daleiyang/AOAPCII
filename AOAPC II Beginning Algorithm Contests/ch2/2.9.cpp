#include<stdio.h>
int main()
{
	int min = 0, max = 0, sum = 0, n = 0, c = 0;
	scanf("%d", &n); c++;
	min = max = n;
	while(scanf("%d", &n) == 1){
		if(min > n) min = n;
		if(max < n) max = n;
		sum += n;
		c++;
	}

	printf("%d %d %.3f", min, max, (double)sum / c);
	return 0;
}

