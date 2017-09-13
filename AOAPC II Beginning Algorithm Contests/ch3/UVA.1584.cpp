#include<stdio.h>
#include<string.h>
const int maxn = 105;
int less(const char * a, int p, int q){
	int n = strlen(a);
	for(int i = 0; i < n; i++)
		if(a[(q + i) % n] != a[(p + i) % n])
			return a[(p + i) % n] < a[(q + i) % n];
	return 0;
}
int main(){
#ifdef LOCAL
	freopen("UVA.1584.in", "r", stdin);
	freopen("UVA.1584.out", "w", stdout);
#endif
	int T;
	scanf("%d", &T);
	char a[maxn];
	while(T--){
		scanf("%s", a);
		int n = strlen(a);
		int ans = 0;
		for(int i = 1; i < n; i++)
			if(less(a, i, ans))
				ans = i;
		for(int i = 0; i < n; i++)
			putchar(a[(ans + i) % n]);
		putchar('\n');
	}
	return 0;
}

