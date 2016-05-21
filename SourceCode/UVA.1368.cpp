#include<stdio.h>
#include<string.h>
const int maxn = 51;
const int maxl = 1001;
char a[maxn][maxl];
int b[26];

int main(){
#ifdef LOCAL
	freopen("UVA.1368.in", "r", stdin);
	freopen("UVA.1368.out", "w", stdout);
#endif
	int T;
	scanf("%d", &T);
	while(T--){
		memset(a, 0, sizeof(a));
		int n, m;
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; i++){
			scanf("%s", a[i]);
		}	
		int hm = 0;
		for(int i = 0; i < m; i++){
			memset(b, 0, sizeof(b));
			for(int j = 0; j < n; j++){
				b[a[j][i] - 'A']++;
			}
			int t = 'A'-'A';
			if(b['A'-'A'] < b['C'-'A']) t = 'C'-'A';
			if(b[t] < b['G'-'A']) t= 'G'-'A';
			if(b[t] < b['T'-'A']) t= 'T'-'A';
			printf("%c", 'A' + t);
			hm += n - b[t];
		}
		printf("\n%d\n", hm);
	}
}

