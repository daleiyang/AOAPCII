#include<stdio.h>
int main(){
#ifdef LOCAL
	freopen("data.in", "r", stdin);
	freopen("data.out", "w", stdout);
#endif
	int n, sum = 0, c = 0, min = 0, max = 0;
	scanf("%d", &n); c++; sum += n;
	min = max = n;
	while(scanf("%d", &n) == 1){
		if(min > n) min = n;
		if(max < n) max = n;
/*
		printf("n = %d, min = %d, max = %d\n", n, min, max);
*/
		sum += n;
		c++;
	}
	printf("%d %d %.3f", min, max, (double)sum / c);
	return 0;
}

