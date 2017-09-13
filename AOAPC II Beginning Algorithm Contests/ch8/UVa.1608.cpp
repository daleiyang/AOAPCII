#include<cstdio>
#include<map>
using namespace std;

const int maxn = 200000 + 5;
int n, x[maxn], L[maxn], R[maxn];
map<int, int> m;

bool unique(int i, int l, int r){
	return l > L[i] && r < R[i]; 
}

bool check(int l, int r){
	if(l >= r) return true;
	for(int d = 0; l+d <= r-d; d++){
		if(unique(l+d, l, r))
			return check(l, l+d-1) && check(l+d+1, r);
		if(l+d == r-d) break;
		if(unique(r-d, l, r))
			return check(l, r-d-1) && check(r-d+1, r);
	}
	return false;
}

int main(){
#ifdef LOCAL
		freopen("UVa.1608.in", "r", stdin);
		freopen("UVa.1608.out", "w", stdout);
#endif
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		for(int i = 0; i < n; i++) scanf("%d", &x[i]);
		
		m.clear();
		for(int i = 0; i < n; i++){
			if(!m.count(x[i])) L[i] = -1;
			else L[i] = m[x[i]];
			m[x[i]] = i;
		}

		m.clear();
		for(int i = n-1; i >= 0; i--){
			if(!m.count(x[i])) R[i] = n;
			else R[i] = m[x[i]];
			m[x[i]] = i;
		}
		
		if(check(0, n-1)) printf("non-boring\n");
		else printf("boring\n");
	}
	return 0;
}

