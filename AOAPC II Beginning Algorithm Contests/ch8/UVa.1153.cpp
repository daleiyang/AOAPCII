#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;

const int maxn = 800000 + 5;

struct order{
	int len, end;
	order(int len = 0, int end = 0):len(len), end(end){	}
	bool operator < (const order & rhs) const{
		return len < rhs.len;
	}
}o[maxn];

bool cmp(order a,order b){
	return a.end < b.end;
}

int main(){
#ifdef LOCAL
		freopen("UVa.1153.in", "r", stdin);
		freopen("UVa.1153.out", "w", stdout);
#endif
	int n, m, kase = 0;
	scanf("%d", &n);
	while(n--){
		scanf("%d", &m);
		for(int i = 0; i < m; i++){
			scanf("%d%d", &o[i].len, &o[i].end);
		}
		sort(o, o+m, cmp);

		int ans = 0, t = 0;
		priority_queue<order> q;
		for(int i = 0; i < m; i++){
			q.push(o[i]);
			t += o[i].len;
			ans++;

			if(t > o[i].end){
				order temp = q.top(); q.pop();
				t -= temp.len;
				ans--;
			}
		}
		if(kase++) printf("\n");
		printf("%d\n", ans);
		
	}
	return 0;
}

