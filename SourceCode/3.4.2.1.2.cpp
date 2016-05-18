#include<stdio.h>
int main(){
	int n, min = 0, max = 0, sum = 0 , c = 0;
	scanf("%d", &n);
	min = max = n;
	sum += n; c++;
	while(scanf("%d", &n) == 1){
		if(n < min) min = n;
		if(n > max) max = n;
		sum += n;
		c++;
	}
	printf("max = %d, min = %d, avg = %lf", max, min, (double)sum / c);
	return 0;
}

