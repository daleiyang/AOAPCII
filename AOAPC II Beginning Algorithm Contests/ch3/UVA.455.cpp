#include<stdio.h>
#include<string.h>
const int maxn = 85;
int main(){
#ifdef LOCAL
	freopen("UVA.455.in", "r", stdin);
	freopen("UVA.455.out", "w", stdout);
#endif

	int T;
	scanf("%d", &T);
	while(T--){
		char a[maxn];
		scanf("%s", a);
		int n = strlen(a), i, j;
		for(i = 1; i <= n; i++){
			if(n % i == 0){
				for(j = i; j < n; j++){
					if(a[j] != a[j%i]) break;
				}
			}
			if(j == n) break;
		}
		if(T) printf("%d\n\n", i);
		else printf("%d\n", i);
	}
	return 0;
}

