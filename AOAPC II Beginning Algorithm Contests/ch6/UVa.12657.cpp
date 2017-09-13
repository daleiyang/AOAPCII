#include<iostream>
#include<cstdio>
using namespace std;

const int maxn = 100000 + 5;
int l[maxn], r[maxn];

void link(int L, int R){
	r[L] = R; l[R] = L;
}

int main(){
#ifdef LOCAL
	freopen("UVa.12657.in", "r", stdin);
	freopen("UVa.12657.out", "w", stdout);
#endif
	int n, m, kase = 1;
	while(scanf("%d%d", &n, &m) == 2){
		//build left, right
		for(int i = 1; i <= n; i++){
			l[i] = i-1;
			r[i] = (i+1)%(n+1);
		}
		l[0] = n; r[0] = 1;
		//operation
		int op, x, y, inv = 0, lx, rx, ly, ry;
		while(m--){
			scanf("%d", &op);
			if(op == 4) {inv = !inv; continue;}
			scanf("%d%d", &x, &y);
			
			if(inv && op != 3) {op = 3 - op;}
			if(op == 1 && x == l[y]) {continue;}
			if(op == 2 && x == r[y]) {continue;}
			
			lx = l[x]; rx = r[x]; ly = l[y]; ry = r[y];
			if(op == 1) {
				link(lx, rx); link(ly, x); link(x, y); continue;
			}
			if(op == 2){
				link(lx, rx); link(x, ry); link(y, x); continue;
			}
			if(op == 3){
				if(r[x] == y){
					link(lx, y); link(x, ry); link(y, x);
				}
				else if(l[x] == y){
					link(y, rx); link(ly, x); link(x, y);
				}
				else{
					link(lx, y); link(y, rx); link(ly, x); link(x, ry);
				}
			}
		}
		//sum
		long long ans = 0; int b = 0;
		for(int i = 1; i<= n; i++){
			b = r[b];
			if(i % 2 == 1) {ans += b;}
		}
		//print
		if(inv && n%2==0){ans = (long long)n*(n+1)/2 - ans;}
		cout << "Case " << kase++ << ": " << ans << endl;
	}
	return 0;
}

