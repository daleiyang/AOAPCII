#include<stdio.h>
#include<string.h>
const int max = 100005;
int a[max];

int main(){
#ifdef LOCAL
freopen("UVA.1583.in", "r", stdin);
freopen("UVA.1583.out", "w", stdout);
#endif
	memset(a, 0, sizeof(a));
	for(int i = 1; i < max; i++){
		int t = i, x = i;
		while(x > 0) {
			t += x % 10;
			x = x / 10;
		}
		if(!a[t] || i < a[t]) a[t] = i;
		
	}
	int n, t;
	scanf("%d", &n);
	while(n--){
		scanf("%d", &t);
		printf("%d\n", a[t]);
	}
	return 0;
}

