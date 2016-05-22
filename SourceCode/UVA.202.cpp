#include<stdio.h>
#include<string.h>
const int maxn = 3001;
int x[maxn], y[maxn], f[maxn];
int main(){
#ifdef LOCAL
	freopen("UVA.202.in", "r", stdin);
	freopen("UVA.202.out", "w", stdout);
#endif
	int n, m, s;
	while(scanf("%d%d", &n, &m) == 2){
		memset(x, 0, sizeof(x));
		memset(y, 0, sizeof(y));
		memset(f, 0, sizeof(f));
		int a = n, b = m, c = 0;
		int t = n/m;
		n = n%m;
		while(!f[n]){
			f[n] = 1;
			c++;
			x[c] = n;
			y[c] = n*10/m;
			n = n*10%m;	
		}
		printf("%d/%d = %d.", a, b, t);
		for(int i = 1; (i<=c) && (i<=50); i++){
			if(x[i] == n){
				printf("(");
				s = i;
			}
			printf("%d", y[i]);
		}
		if((c-s+1)>50) printf("...");
		printf(")\n   %d = number of digits in repeating cycle\n\n", c-s+1);
	}
	return 0;
}

