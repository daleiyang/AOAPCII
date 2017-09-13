#include<stdio.h>
#include<string.h>
const int max = 1000000;
int a[max];

int main(){
	memset(a, 0, sizeof(a));
	int i = 0, n;
	while(scanf("%d", &n) == 1)
		a[i++] = n;
	for(int j = i - 1; j > 0 ; j--)
		printf("%d ", a[j]);
	printf("%d\n", a[0]);
	return 0;
}

