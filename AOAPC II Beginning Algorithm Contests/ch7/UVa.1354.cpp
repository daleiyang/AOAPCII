#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

struct Tree{
	double L, R;
	Tree(): L(0), R(0){}
};

const int maxn = 6;

int vis[1<<maxn], n;
double r, sum[1<<maxn], w[maxn];
vector<Tree> tree[1<<maxn];

void dfs(int subset){
	if(vis[subset]) return;
	vis[subset] = 1;

	int has_children = 0;
	for(int left = (subset-1) & subset; left; left = (left-1)&subset){
		has_children = 1;
		
		int right = left^subset;
		double d1 = sum[right] / sum[subset];
		double d2 = sum[left] / sum[subset];

		dfs(left); dfs(right);

		for(unsigned int i = 0; i < tree[left].size(); i++){
			for(unsigned int j = 0; j < tree[right].size(); j++){
				Tree t;
				t.L = max(tree[left][i].L+d1, tree[right][j].L-d2);
				t.R = max(tree[right][j].R+d2, tree[left][i].R-d1);
				if((t.L + t.R) < r) tree[subset].push_back(t);
			}
		}
	}
	if(!has_children) tree[subset].push_back(Tree());
}

int main(){
#ifdef LOCAL
	freopen("UVa.1354.in", "r", stdin);
	freopen("UVa.1354.out", "w", stdout);
#endif
	int T;
	scanf("%d", &T);
	while(T--){		
		scanf("%lf%d", &r, &n);
		for(int i = 0; i < n; i++) scanf("%lf", &w[i]);
		for(int i = 0; i < (1<<n); i++){
			sum[i] = 0;
			tree[i].clear();
			for(int j = 0; j < n; j++){
				if(i & (1<<j)) sum[i] += w[j];
			}
		}
		
		int root = (1<<n)-1;
		memset(vis, 0, sizeof(vis));
		dfs(root);

		double ans = -1;
		for(unsigned int i = 0; i < tree[root].size(); i++){
			ans = max(ans, tree[root][i].L + tree[root][i].R);
		}
		printf("%.10lf\n", ans);

	}
	return 0;
}

