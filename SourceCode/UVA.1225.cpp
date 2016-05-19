#include<stdio.h>
#include<string.h>
int main(){
#ifdef LOCAL
	freopen("UVA.1225.in", "r", stdin);
	freopen("UVA.1225.out", "w", stdout);
#endif

	int T;
	scanf("%d", &T);
	int a[10];
	while(T--){
		memset(a, 0, sizeof(a));
		int n;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++){
			int x = i;
			while(x != 0) {
				a[x % 10]++;
				x = x / 10;
			}
		}
		for(int i = 0; i < 9; i++){
			printf("%d ", a[i]);
		}
		printf("%d\n", a[9]);
	}
	return 0;
}

