#include<iostream>
#include<cstdio>
#include<cstring>
#include<set>
#include<algorithm>
using namespace std;

typedef long long LL;

const int maxn = 1000 + 10;
set<LL> skip;
LL v[maxn], ans[maxn];
int a, b, x, maxd;

LL gcd(LL a, LL b){
	return b == 0 ? a : gcd(b, a%b);
}

LL get_first(LL a, LL b){
	return b/a + 1;
}

bool better(int d){
	for(int i = d; i >= 0; i--){
		if(v[i] != ans[i]) {
			return ans[i] == -1 || v[i] < ans[i];
		}
	}
	return false;
}

bool dfs(int d, LL from, LL aa, LL bb){
	if(d == maxd){
		LL t = bb/aa;
		if(bb%aa || skip.count(t)) return false;
		v[d] = t;
		if(better(d)) memcpy(ans, v, sizeof(LL) * (d+1));
		return true;
	}
	bool ok = false;
	from = max(get_first(aa, bb), from);
	for(LL i = from; ; i++){
		if(skip.count(i)) continue;
		if((bb*(maxd+1-d))<=aa*i) break; //prune
		v[d] = i;
		LL a2 = aa*i-bb;
		LL b2 = bb*i;
		LL g = gcd(a2, b2);
		if(dfs(d+1, i+1, a2/g, b2/g)) {ok = true;}
	}
	return ok;
}

int main(){
	ios::sync_with_stdio(false);
#ifdef LOCAL
		freopen("UVa.12558.in", "r", stdin);
		freopen("UVa.12558.out", "w", stdout);
#endif
	int T, kase = 0, k;
	cin>>T;
	while(T--){
		skip.clear();
		memset(ans, -1, sizeof(ans));
		cin>>a>>b>>k;
		while(k--){
			cin>>x;
			skip.insert(x);
		}
		for(maxd = 1; maxd <= 100 ; maxd++){
			if(dfs(0, get_first(a, b), a, b)) break;
		}
		cout<<"Case "<<++kase<<": "<<a<<"/"<<b<<"=";
		for(int i = 0; i < maxd; i++) cout<<"1/"<<ans[i]<<"+";
		cout<<"1/"<<ans[maxd]<<"\n";
	}
	return 0;
}

