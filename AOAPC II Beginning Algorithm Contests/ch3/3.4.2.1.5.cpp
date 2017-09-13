#include<stdio.h>
const int maxn = 100;
int a[maxn];
int main(){
	int i = 0, sum = 0;
	while(scanf("%d", &a[i]) == 1) sum += a[i++];
	double avg = (double)sum / i;
	double esum = 0;
	for(int j = 0; j < i; j++) esum += (a[j]-avg) * (a[j]-avg);
	printf("%lf\n", esum / i);
	return 0;
}zzzzz

