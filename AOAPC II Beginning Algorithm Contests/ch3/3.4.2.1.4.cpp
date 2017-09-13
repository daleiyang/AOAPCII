#include<stdio.h>
int main(){
	int n, max, min;
	scanf("%d", &max);
	scanf("%d", &min);
	if(min > max) {n = max; max = min; min = n;}
	while(scanf("%d", &n) == 1){
		if(n >= max){min = max; max = n;}
		else if(n >= min){min = n;}
	}
	printf("%d", min);
	return 0;	
}

