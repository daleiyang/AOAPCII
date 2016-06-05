#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=10000;
int a[maxn];

int main(){
#ifdef LOCAL
	freopen("UVA.10474.in", "r", stdin);
	freopen("UVA.10474.out", "w", stdout);
#endif
	int n, m, kase=0, q;
	while(scanf("%d%d", &n, &m) == 2 && n){
		printf("CASE# %d:\n", ++kase);
		for(int i=0; i<n; i++){scanf("%d", &a[i]);}
		sort(a, a+n);
		while(m--){
			scanf("%d", &q);
			int idx = lower_bound(a, a+n, q) -a;
			if(idx==n || a[idx] != q) printf("%d not found\n", q);
			else (printf("%d found at %d\n", q, idx+1));
		}
	}
	return 0;
}
	
