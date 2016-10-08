#include<cstdio>
using namespace std;

const int maxn = 100000 + 5;

int p[maxn], q[maxn], d[maxn], n;

int solve(int s){
	int ans = 0;
	for(int i = 0; i < n; i++){
		int idx = (s+i)%n;
		ans += d[idx];
		if(ans < 0) return i; 
	}
	return -1;
}

int main(){
#ifdef LOCAL
	freopen("UVa.11093.in", "r", stdin);
	freopen("UVa.11093.out", "w", stdout);
#endif
	int T;
	scanf("%d", &T);
	for(int i = 1; i <= T; i++){
		scanf("%d", &n);
		for(int j = 0; j < n; j++) scanf("%d", &p[j]);
		for(int j = 0; j < n; j++) scanf("%d", &q[j]);
		for(int j = 0; j < n; j++) d[j] = p[j] - q[j];
		bool f = false; int j;
		for(j = 0; j < n;){
			if(d[j] < 0) {j++; continue;}
			int t = solve(j);
			if(t == -1) {f = true; break;}
			else j += t+1;
		}
		if(!f) printf("Case %d: Not possible\n", i);
		else printf("Case %d: Possible from station %d\n", i, j+1);
	}	
	return 0;
}

