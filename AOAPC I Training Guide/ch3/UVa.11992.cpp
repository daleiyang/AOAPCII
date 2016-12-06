#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 1<<17;

int _sum, _min, _max, op, x1, x2, y1, y2, v;

struct IntervalTree{
	int sumv[maxn], minv[maxn], maxv[maxn], setv[maxn], addv[maxn];

	void maintain(int o, int L, int R){
		int lc = o*2, rc = o*2+1;
		if(R > L){
			sumv[o] = sumv[lc] + sumv[rc];
			minv[o] = min(minv[lc], minv[rc]);
			maxv[o] = max(maxv[lc], maxv[rc]);
 		}
		if(setv[o] >= 0) {minv[o] = maxv[o] = setv[o]; sumv[o] = setv[o] * (R-L+1);}
		if(addv[o]) {minv[o] += addv[o]; maxv[o] += addv[o]; sumv[o] += addv[o] * (R-L+1); }
	}

	void pushdown(int o){
		int lc = o*2, rc =o*2+1;
		if(setv[o] >= 0){
			setv[lc] = setv[rc] = setv[o];
			addv[lc] = addv[rc] = 0;
			setv[o] = -1;
		}
		if(addv[o]){
			addv[lc] += addv[o];
			addv[rc] += addv[o];
			addv[o] = 0;
		}
	}

	void update(int o, int L, int R){
		int lc = o*2, rc = o*2+1;
		if(y1 <= L && y2 >= R){
			if(op == 1) addv[o] += v;
			else{setv[o] = v; addv[o] = 0;}
		}else {
			pushdown(o);
			int M = L + (R-L)/2;
			if(y1 <= M) update(lc, L, M); else maintain(lc, L, M);
			if(y2 > M) update(rc, M+1, R); else maintain(rc, M+1, R);
		}
		maintain(o, L, R);
	}

	void query(int o, int L, int R, int add){
		if(setv[o] >= 0){
			int v = setv[o] + add + addv[o];
			_sum += v * (min(R, y2)-max(L, y1)+1);
			_min = min(_min, v);
			_max = max(_max, v);
		}
		else if(y1 <= L && y2 >= R){
			_sum += sumv[o] + add*(R-L+1);
			_min = min(_min, minv[o]+add);
			_max = max(_max, maxv[o]+add);
		}
		else{
			int M = L + (R-L)/2;
			if(y1 <= M) query(o*2, L, M, add + addv[o]);
			if(y2 > M) query(o*2+1, M+1, R, add + addv[o]);
		}
	}
};

const int maxr = 20 + 5;
const int INF = 1000000000;

IntervalTree tree[maxr];

int main(){
#ifdef LOCAL
		freopen("UVA.11992.in", "r", stdin);
		freopen("UVA.11992.out", "w", stdout);
#endif
	int r, c, m;
	while(scanf("%d%d%d", &r, &c, &m) == 3){
		memset(tree, 0, sizeof(tree));
		for(int i = 1; i <= r; i++){
			memset(tree[i].setv, -1, sizeof(tree[i].setv));
			tree[i].setv[1] = 0;
		}
		while(m--){
			scanf("%d%d%d%d%d", &op, &x1, &y1, &x2, &y2);
			if(op < 3){
				scanf("%d", &v);
				for(int i = x1; i <= x2; i++) tree[i].update(1, 1, c);
			} 
			else{
				_sum = 0; _min = INF; _max = -INF;
				for(int i = x1; i <= x2; i++) tree[i].query(1, 1, c, 0);
				printf("%d %d %d\n", _sum, _min, _max);
			}
		}
	}
	return 0;
}

