#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 5000 + 5;

struct Node{
	int L, R, C, Id;
	Node(int L = 0, int R = 0, int Id = 0):L(L), R(R), Id(Id){}
}X[maxn], Y[maxn];

int comp(Node & n, Node & n2){
	return (n.R < n2.R) || (n.R == n2.R && n.L < n2.L); //there is the key
}

int comp2(Node &n, Node & n2){
	return n.Id < n2.Id;
}

bool solve(Node * node, int n){
	int vis[maxn];
	memset(vis, 0, sizeof(vis));
	for(int i = 0; i < n; i++){
		bool f = false;
		for(int j = node[i].L; j <= node[i].R; j++){
			if(!vis[j]) {
				node[i].C = j;
				vis[j] = 1;
				f = true;
				break;
			}
		}
		if(!f) return false;
	}
	return true;
}

int main(){
#ifdef LOCAL
	freopen("UVa.11134.in", "r", stdin);
	freopen("UVa.11134.out", "w", stdout);
#endif
	int n;
	while(scanf("%d", &n) == 1 && n){
		for(int i = 0; i < n; i++){
			scanf("%d%d%d%d", &X[i].L, &Y[i].L, &X[i].R, &Y[i].R);
			X[i].Id = Y[i].Id = i;
		}
		sort(X, X+n, comp);
		sort(Y, Y+n, comp);
		if(solve(X, n) && solve(Y, n)){
			sort(X, X+n, comp2);
			sort(Y, Y+n, comp2);
			for(int i = 0; i < n; i++){
				printf("%d %d\n", X[i].C, Y[i].C);
			}
		}
		else{
			printf("IMPOSSIBLE\n");
		}
	}
	return 0;
}

