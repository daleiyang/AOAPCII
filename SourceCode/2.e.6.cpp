#include<stdio.h>
#include<string.h>
#include<time.h>
int main(){
	int a[10], x;
	for(int i = 123; i <= 329; i++){
		memset(a, 0, sizeof(int) * 10);
		int j = i * 2;
		int k = i * 3;
		
		a[i/100] = a[i%100/10] = a[i%10] = 1;
		a[j/100] = a[j%100/10] = a[j%10] = 1;
		a[k/100] = a[k%100/10] = a[k%10] = 1;

		for(x = 1; x <= 9; x++)
			if(a[x] == 0) break;
		if(x == 10) printf("%d %d %d\n", i, j, k);
	}
	printf("Time used:%lf", (double)clock()/CLOCKS_PER_SEC);
	return 0;
}

