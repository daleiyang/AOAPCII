#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100 + 5;
char a[maxn], b[maxn];

int main(){
#ifdef LOCAL
		freopen("UVa.12545.in", "r", stdin);
		freopen("UVa.12545.out", "w", stdout);
#endif
	int n;
	scanf("%d", &n);
	for(int t = 1; t <= n; t++){
		scanf("%s%s", a, b);
		int n01 = 0, n10 = 0, nq1 = 0, nq0 = 0;
		for(unsigned int i = 0; i < strlen(a); i++){
			if(a[i] == '0' && b[i] == '1') n01++;
			if(a[i] == '1' && b[i] == '0') n10++;
			if(a[i] == '?' && b[i] == '1') nq1++;
			if(a[i] == '?' && b[i] == '0') nq0++;
		}
		if(n01+nq1+nq0 < n10+nq0) {
			printf("Case %d: -1\n", t);
			continue;
		}
		int ans = 0;
		if(n01 < n10+nq0){
			int d = n10+nq0-n01;
			int t = min(d, nq0);
			nq0 -= t;
			ans += t;
			if(d > t){nq1 -= d-t; n01 += d-t; ans += d-t;}
		}
		if(n01 > n10+nq0){
			int d = n01-(n10+nq0); 
			n01 -= d; 
			ans += d;
		}
		if(nq1 > 0) ans += nq1;
		if(nq0 > 0) {
			ans += nq0;
			n10 += nq0;
		}
		ans += (n10+ n01)/2;
		printf("Case %d: %d\n", t, ans);
	}
	return 0;
}

