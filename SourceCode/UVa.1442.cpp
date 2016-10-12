#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 1000000 + 5;
int p[maxn], s[maxn], h[maxn], n;

int main(){
#ifdef LOCAL
		freopen("UVa.1442.in", "r", stdin);
		freopen("UVa.1442.out", "w", stdout);
#endif
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		for(int i = 0; i < n; i++) scanf("%d", &p[i]);
		for(int i = 0; i < n; i++) scanf("%d", &s[i]);
		int level = h[0] = s[0];
		for(int i = 1; i < n; i++){
			if(s[i] < level) level = s[i];
			if(p[i] > level) level = p[i];
			h[i] = level;
		}
		level = s[n-1];
		int ans = min(level, h[n-1]) - p[n-1];
		for(int i = n-2; i >= 0; i--){
			if(s[i] < level) level = s[i];
			if(p[i] > level) level = p[i];
			ans += min(level, h[i]) - p[i];
		}
		printf("%d\n", ans);
	}
	return 0;
}

