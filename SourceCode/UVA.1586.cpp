#include<stdio.h>
#include<string.h>
#include<ctype.h>
double m[] = {0, 0, 12.01, 0, 0, 0, 0, 1.008, 0, 0, 0, 0, 0, 14.01, 16.00};
int main(){
#ifdef LOCAL
	freopen("UVA.1586.in", "r", stdin);
	freopen("UVA.1586.out", "w", stdout);
#endif
	int T;
	scanf("%d", &T);
	while(T--){
		char a[85];
		scanf("%s", a);
		int n = strlen(a), pn = 0, f = 0;
		double sum = 0, pq = 0;
		for(int i = 0; i < n; i++){
			if(isalpha(a[i])){
				sum += pq * pn;
				pq = m[a[i] - 'A'];
				pn = 1;
				if(i == n - 1) sum += pq * pn;
				f = 1;
			}else{
				if(f == 1) pn = a[i] - '0';
				else pn = pn * 10 + (a[i] - '0');
				if(i == n - 1) sum += pq * pn;
				f = 0;
			}
		}
		printf("%.3lf\n", sum);
	}
	return 0;
}

