#include<cstdio>
#include<algorithm>
#include<map>
using namespace std;

const int maxn = 1000000 + 5;
int A[maxn], last[maxn];
map<int, int> cur;

int main(){
#ifdef LOCAL
	freopen("UVa.11572.in", "r", stdin);
	freopen("UVa.11572.out", "w", stdout);
#endif
	int T, n;
	scanf("%d", &T);
	while(T--){
		cur.clear();
		scanf("%d", &n);
		for(int i = 0; i < n; i++){
			scanf("%d", &A[i]);
			if(!cur.count(A[i])) last[i] = -1;
			else last[i] = cur[A[i]];
			cur[A[i]] = i;
		}

		int L = 0, R = 0, ans = 0;
		while(R < n){
			while(R < n && last[R] < L) R++;
			ans = max(ans, R - L);
			L++;
		}
		printf("%d\n", ans);
	}
	return 0;
}

