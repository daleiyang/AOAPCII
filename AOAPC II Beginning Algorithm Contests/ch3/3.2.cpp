#include<stdio.h>
#include<string.h>
const int max = 1005;
int a[max];

int main(){
	memset(a, 0, sizeof(a));
	int n, k, first = 1;
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= k; i++)
		for(int j = 1; j <= n; j++)
			if (j % i == 0) a[j] = !a[j];
	for(int j = 1; j <= n; j++)
		if(a[j] == 1) {
			if(first == 1){
				first = 0; 
			}else{
				printf(" ");
			}
			printf("%d", j);
		}
	return 0;
}

