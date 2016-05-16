#include<stdio.h>
int main(){
	int n, max, e, l;
	scanf("%d", &n);
	max = 2 * (n - 1) + 1;
	for(int i = n - 1; i >=0; i--){
		l = 2 * i + 1;
		e = (max - l) / 2;
		for(int j = 0; j < e; j++) printf(" ");
		for(int j = 0; j < l; j++) printf("*");
		for(int j = 0; j < e; j++) printf(" ");
		printf("\n");
	}
	return 0;
}

