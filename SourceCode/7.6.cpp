#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long LL;

const int maxn = 100 + 5;
int ans[maxn], v[maxn], a, b, maxd;

LL gcd(LL a, LL b){
	return b == 0 ? a : gcd(b, a%b);
}

int get_first(LL a, LL b){
	return b/a + 1;
}

bool better(int d){
	for(int i = d; i >= 0; i--) if(v[i] != ans[i]){
		return (ans[i] == -1) || (v[i] < ans[i]);
	}
	return false;
}

bool dfs(int d, int from, LL aa, LL bb){
	if(d == maxd){
		if(bb % aa) return false;
		v[d] = bb/aa;
		if(better(d)) memcpy(ans, v, sizeof(LL) * (d+1));
		return true;
	}
	bool ok = false;
	from = max(from, get_first(aa, bb));
	for(int i = from; ; i++){
		if(bb*(maxd+1-d) <= aa*i) break;
		v[d] = i;
		LL a2 = aa*i - bb;
		LL b2 = bb*i;
		LL g = gcd(a2, b2);
		if(dfs(d+1, i+1, a2/g, b2/g)) ok = true;
	}
	return ok;
}

int main(){
#ifdef LOCAL
	freopen("7.6.in", "r", stdin);
	freopen("7.6.out", "w", stdout);
#endif
	int kase = 0;
	while(scanf("%d%d", &a, &b) == 2 && a){
		memset(ans, -1, sizeof(ans));
		int ok = 0;
		for(maxd = 1; maxd <= 100; maxd++){
			if(dfs(0, get_first(a, b), a, b)) {ok = 1; break;}
		}
		printf("Case %d: ", ++kase);
		if(ok){
			printf("%d/%d=", a, b);
			for(int i = 0; i < maxd; i++) printf("1/%d+", ans[i]);
			printf("1/%d\n", ans[maxd]);
		} else printf("No solution.\n");
	}
	return 0;
}

