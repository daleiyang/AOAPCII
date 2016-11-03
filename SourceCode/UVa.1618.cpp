#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 5000 + 5;

int desc[maxn], asc[maxn], n;
struct Node{
	int val, idx;
	Node(int val = 0, int idx = 0):val(val), idx(idx){}
	bool operator < (const Node & rhs) const{
		return val > rhs.val;
	}
} N[maxn];

void input(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &N[i].val);
		N[i].idx = i;
	}
	sort(N+1, N+n+1);
	//descending order
	int cnt = 0;
	for(int i = 1; i <= n ; i++){
		desc[cnt] = N[i].idx;
		cnt = N[i].idx;
	}
	desc[cnt] = 0;
	//ascending order
	cnt = 0;
	for(int i = n; i >= 1 ; i--){
		asc[cnt] = N[i].idx;
		cnt = N[i].idx;
	}
	asc[cnt] = 0;
}

/*
	Because 1 <= p < q < r < s <= n && ( A[q] > A[s] > A[p] > A[r] || A[q] < A[s] < A[p] < A[r])
	We check the possibility in this order:  q -> s -> p -> r.
	Pruning:
	1.   2 <= q <= n-2
	2.   s <= n && s > q + 1
	3.   1 <= p < q
	4.   q < r < s
*/
bool solve(int * idx){
	//brutal force
	int q = idx[0], s, p, r;
	while(q){
		if(q >= 2 && q <= n-2){//pruning q
			s = idx[q];
			while(s){
				if(s <= n && s > q+1) {//pruning s
					p = idx[s];
					while(p){
						if(p >= 1 && p < q) { //pruning p
							r = idx[p];
							while(r){
								if(r > q && r < s) return true; //pruning r
								r = idx[r];
							}
						}	
						p = idx[p];
					}
				}
				s = idx[s];
			}
		}
		q = idx[q];
	}
	return false;
}

int main(){
#ifdef LOCAL
		freopen("UVa.1618.in", "r", stdin);
		freopen("UVa.1618.out", "w", stdout);
#endif
	int T;
	scanf("%d", &T);
	while(T--){
		input();
		if(!solve(desc) && !solve(asc)) printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}

