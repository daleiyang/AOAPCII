#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 100;

struct Node{
	int x, y;
	Node(int x = 0, int y = 0):x(x), y(y){};
	bool operator < (const Node & rhs) const{
		return y < rhs.y;
	}
	void read(){
		scanf("%d%d", &x, &y);
	}
}N[maxn];

int main(){
#ifdef LOCAL
	freopen("8.4.2.1.in", "r", stdin);
	freopen("8.4.2.1.out", "w", stdout);
#endif
	int k, n;
	scanf("%d", &k);
	while(k--){
		scanf("%d", &n);
		for(int i = 0; i < n; i++){
			N[i].read();
		}
		sort(N, N+n);
		int idx = 0;
		printf("(%d, %d)\n", N[0].x, N[0].y);
		for(int i = 1; i < n; i++){
			if(N[i].x < N[idx].y) continue;
			else{
				printf("(%d, %d)\n", N[i].x, N[i].y);
				idx = i;
			}
		}
		printf("\n");
	}
	return 0;
}

