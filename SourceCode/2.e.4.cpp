#include<stdio.h>
#include<time.h>
int main(){
	int n, m, kase = 0;
	while(scanf("%d%d", &n, &m) == 2 && !((n == 0) && (m == 0))){
		double sum = 0, t;
		for(int i = n; i <= m; i++){
			t = (1.0 / i) * (1.0 / i);
			sum += t;
			//printf("t = %.50lf sum = %lf\n", t, sum);
		}
		printf("Case %d: %.5f\n", ++kase, sum);
	}
	//printf("Time used: %.2lf", (double) clock() / CLOCKS_PER_SEC);
	return 0;
}

