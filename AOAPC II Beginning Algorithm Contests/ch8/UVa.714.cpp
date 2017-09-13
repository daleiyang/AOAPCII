#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 500 + 5;

int m, k, p[maxn], last[maxn];

int solve(long long maxp){
	long long done = 0;
	int ans = 1;
	for(int i = 0; i < m; i++){
		if(done + p[i] > maxp) {ans++; done = p[i];}
		else done += p[i];
	}
	return ans;
}

void print(long long ans){
	memset(last, 0, sizeof(last));
	int remain = k;
	long long done = 0;
	for(int i = m-1; i >= 0; i--){
		if(done + p[i] > ans || i+1 < remain){
			last[i] = 1;
			remain--;
			done = p[i];
		}
		else done += p[i];
	}
	for(int i = 0; i < m-1; i++){
		printf("%d ", p[i]);
		if(last[i]) printf("/ ");
	}
	printf("%d\n", p[m-1]);
}

int main(){
#ifdef LOCAL
	freopen("UVa.714.in", "r", stdin);
	freopen("UVa.714.out", "w", stdout);
#endif
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &m, &k);
		long long tot = 0;
		int maxp = -1;
		for(int i = 0; i < m; i++){
			scanf("%d", &p[i]);
			tot += p[i];
			maxp = max(maxp, p[i]);
		}
		long long L = maxp, R = tot;
		while(L < R){
			long long m = L + (R-L)/2;
			if(solve(m) <= k) R = m; else L = m+1;
		}
		print(L);
	}
	return 0;
}

