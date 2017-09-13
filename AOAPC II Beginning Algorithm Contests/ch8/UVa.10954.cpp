#include<cstdio>
#include<queue>
using namespace std;

int main(){
#ifdef LOCAL
		freopen("UVa.10954.in", "r", stdin);
		freopen("UVa.10954.out", "w", stdout);
#endif
	int n, x;
	while(scanf("%d", &n) == 1 && n){
		priority_queue<int, vector<int>, greater<int> > q;
		for(int i = 0; i < n; i++) {
			scanf("%d", &x);
			q.push(x);
		}
		int ans = 0;
		for(int i = 0; i < n-1; i++){
			int a = q.top(); q.pop();
			int b = q.top(); q.pop();
			ans += a+b;
			q.push(a+b);
		}
		printf("%d\n", ans);
	}
	return 0;
}

