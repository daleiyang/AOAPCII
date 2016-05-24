#include<stdio.h>
#include<string.h>
const int maxn = 101;
char a[maxn], b[maxn];
int main(){
#ifdef LOCAL
	freopen("UVA.1588.in", "r", stdin);
	freopen("UVA.1588.out", "w", stdout);
#endif
	while(scanf("%s", b) != EOF){
		scanf("%s", a);
		int la = strlen(a), lb = strlen(b);
		int i = la-1, j = 0, min = la+lb;
		while(j<lb && i>=0){
			int f = 1, t = (i<j?i:j) + 1;
			int x = t, n = i, m = j;
			while(t--){
				if((a[n]-'0')+(b[m]-'0')>3) {f = 0; break;}
				n--; m--;
			}
			if(f && ((la+lb-x)<min)) min = la+lb-x;
			if(j<lb-1){j++; continue;}
			i--;
		}
		printf("%d\n", min);
	}
}

