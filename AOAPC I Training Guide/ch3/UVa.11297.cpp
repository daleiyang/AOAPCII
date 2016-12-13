#include<cstdio>
#include<algorithm>
using namespace std;

const int INF = 1<<30;
const int maxn = 2000 + 5;

struct IntervalTree2D{
	int Max[maxn][maxn], Min[maxn][maxn], n;
	int xo, isleaf, x1, y1, x2, y2, x, y, v, vmax, vmin;

	void query1D(int o, int L, int R){
		if(y1 <= L && R <= y2) {
			vmax = max(Max[xo][o], vmax); 
			vmin = min(Min[xo][o], vmin);
		} else {
			int M = L + (R-L)/2;
			if(y1 <= M) query1D(o*2, L, M);
			if(M < y2) query1D(o*2+1, M+1, R);
		}
	}

	void query2D(int o, int L, int R){
		if(x1 <= L && R <= x2){xo = o; query1D(1, 1, n);}
		else {
			int M = L + (R-L)/2;
			if(x1 <= M) query2D(o*2, L, M);
			if(M < x2) query2D(o*2+1, M+1, R);
		}
	}

	void modify1D(int o, int L, int R){
		if(L == R){
			if(isleaf){ Max[xo][o] = Min[xo][o] = v; return;}
			Max[xo][o] = max(Max[xo*2][o], Max[xo*2+1][o]);
			Min[xo][o] = min(Min[xo*2][o], Min[xo*2+1][o]);
		} else {
			int M = L + (R-L)/2;
			if(y <= M) modify1D(o*2, L, M);
			else modify1D(o*2+1, M+1, R);
			Max[xo][o] = max(Max[xo][o*2], Max[xo][o*2+1]);
			Min[xo][o] = min(Min[xo][o*2], Min[xo][o*2+1]);
		}
	}

	void modify2D(int o, int L, int R){
		if(L == R){xo = o; isleaf = 1; modify1D(1, 1, n);}
		else{
			int M = L + (R-L)/2;
			if(x <= M) modify2D(o*2, L, M);
			else modify2D(o*2+1, M+1, R);
			xo = o; isleaf = 0; modify1D(1, 1, n); //maintain for x[n to m].
		}
	}

	void query() {vmax = -INF; vmin = INF; query2D(1, 1, n);}
	void modify() {modify2D(1, 1, n);}
} t;

int main(){
#ifdef LOCAL
		freopen("UVa.11297.in", "r", stdin);
		freopen("UVa.11297.out", "w", stdout);
#endif
	int q;
	char op[2];
	scanf("%d", &t.n);
	for(int i = 1; i <= t.n; i++)
		for(int j = 1; j <= t.n; j++){
			scanf("%d", &t.v);
			t.x = i; t.y = j;
			t.modify();
		}
	scanf("%d", &q);
	while(q--){
		scanf("%s", op);
		if(op[0] == 'q'){
			scanf("%d%d%d%d", &t.x1, &t.y1, &t.x2, &t.y2);
			t.query();
			printf("%d %d\n", t.vmax, t.vmin);
		} else if(op[0] == 'c'){
			scanf("%d%d%d", &t.x, &t.y, &t.v);
			t.modify();
		}
	}	
	return 0;
}

