//https://github.com/morris821028/UVa/blob/master/temp/1624%20-%20Knots.cpp
#include<cstdio>
using namespace std;

const int maxn = 1e6 + 5;

struct Node{
	int l, r, face;
} nodes[maxn];

int f[maxn], used[maxn];

void remove(int idx){
	used[idx] = 1;
	nodes[nodes[idx].l].r = nodes[idx].r;
	nodes[nodes[idx].r].l = nodes[idx].l;
}

int main(){
#ifdef LOCAL
		freopen("UVa.1624.in", "r", stdin);
		freopen("UVa.1624.out", "w", stdout);
#endif
	int T, kase = 0, L, P, x, y;
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &L, &P);
		for(int i = 0; i < L; i++){
			nodes[i].l = i-1; nodes[i].r = i+1; f[i] = 0; used[i] = 0;
		}
		nodes[0].l = L-1; nodes[L-1].r = 0;
		for(int i = 0; i < P; i++){
			scanf("%d%d", &x, &y);
			nodes[x].face = y;
			nodes[y].face = x;
			f[x] = 1;
			f[y] = -1;
		}

		int sidx = 0, cnt = P*2;
		for(int i = 0; i < L; i++){
			if(!f[i]) remove(i);
		}

		while(cnt){
			bool update = false;
			while(used[sidx]) sidx++;
			for(int i = nodes[sidx].r; !update && i != sidx; i = nodes[i].r){
				x = i; y = nodes[i].r;
				if(f[x] == f[y] && (nodes[nodes[x].face].r == nodes[y].face ||   //take care of test case 1
									nodes[nodes[y].face].r == nodes[x].face )){  //take care of test case 2
					remove(x);
					remove(nodes[x].face);
					remove(y);
					remove(nodes[y].face);
					cnt -= 4;
					update = true;
				}//passing
				else if(y == nodes[x].face){
					remove(x);
					remove(y);
					cnt -= 2;
					update = true;
				}//self loop
			}
			if(!update) break;
		}
		printf("Case #%d: %s\n", ++kase, cnt ? "NO" : "YES");
	}
	return 0;
}

