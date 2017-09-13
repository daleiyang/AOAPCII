#include<cstdio>
#include<queue>
#include<utility>
using namespace std;

int main(){
#ifdef LOCAL
	freopen("UVA.12100.in", "r", stdin);
	freopen("UVA.12100.out", "w", stdout);
#endif
	int T, n, m, x;
	scanf("%d", &T);
	while(T--){
		queue<pair<int, int> > q;
		priority_queue<int> pq;
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; i++){
			scanf("%d", &x);
			q.push(make_pair(x, i == m ? 1 : 0)); 
			pq.push(x);
		}
		int t = 0;
		while(1){
			if(pq.top() == q.front().first){
				t++; 
				if(q.front().second == 1) {printf("%d\n", t); break;}
				pq.pop(); q.pop(); 
			}
			else{ q.push(q.front()); q.pop();}
		}
	}
	return 0;
}

