#include<stdio.h>
int main(){
	int x, n, kase = 0;
	while(scanf("%d", &n) == 1 && n){
		int min = 0, max = 0, c = 0, sum = 0;
		scanf("%d", &x);
		min = max = x;
		sum += x; 
		c++;
		for(int i = 0; i < n - 1; i++){
			scanf("%d", &x);
			if(min > x) min = x;
			if(max < x) max = x;
			sum += x;
			c++;
		}
		if(kase) printf("\n");
		printf("Case %d: %d %d %.3f\n", ++kase, min, max, (double)sum/c);
	}
	return 0;
}	

