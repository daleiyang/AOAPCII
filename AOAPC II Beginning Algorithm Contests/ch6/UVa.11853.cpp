#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

const int maxn = 1000 + 5;
const double W = 1000.0;

double x[maxn], y[maxn], r[maxn], left, right;
int vis[maxn], n;

bool intersect(int u, int v){
	return sqrt((x[u]-x[v])*(x[u]-x[v])+(y[u]-y[v])*(y[u]-y[v])) <= r[u]+r[v];
}

void check_circle(int u){
	if(x[u]-r[u] <= 0)
		left = min(left, y[u]-sqrt(r[u]*r[u]-x[u]*x[u]));
	if(x[u]+r[u] >= W)
		right = min(right, y[u]-sqrt(r[u]*r[u]-(W-x[u])*(W-x[u])));
}

//return ture if u can reach bottom finally.
bool dfs(int u){
	if(vis[u]) return false;
	vis[u] = 1;
	if(y[u] - r[u] < 0) return true;
	for(int v = 0; v < n; v++){
		if(intersect(u, v) && dfs(v)) return true; // if v has been visited, just go to next v. refer to line 21.
	}
	check_circle(u); //if u can't reach the bottom finally, calculate the possible left, right values.
	return false;
}

int main(){
#ifdef LOCAL
		freopen("UVa.11853.in", "r", stdin);
		freopen("UVa.11853.out", "w", stdout);
#endif
	while(scanf("%d", &n) == 1){
		memset(vis, 0, sizeof(vis));
		bool OK = true; left = right = W;
		for(int i = 0; i < n; i++){
			scanf("%lf%lf%lf", &x[i], &y[i], &r[i]);
		}
		for(int i = 0; i < n; i++){
			if(y[i] + r[i] >= W && dfs(i)) {OK = false; break;}
		}
		if(OK) printf("0.00 %.2lf %.2lf %.2lf\n", left, W, right);
		else printf("IMPOSSIBLE\n");
	}
	return 0;
}

