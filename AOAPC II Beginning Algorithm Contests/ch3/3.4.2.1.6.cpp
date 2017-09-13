#include<stdio.h>
const int maxn = 100;
int a[maxn];
int main(){
	int n = 0, sum = 0, c = 0;
	while(scanf("%d", &a[n]) == 1) sum += a[n++];
	double avg = (double)sum/n;
	for(int i = 0; i < n; i++)
		if(a[i] <= avg) c++;
	printf("%d\n", c);
	return 0;
}

