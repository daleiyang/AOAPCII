#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;

struct Node{
	int v[3], dist;
};
vector<Node> nodes;

struct cmp{
	bool operator() (const int a, const int b) const{
		return nodes[a].dist > nodes[b].dist;
	}
};

const int maxn = 200 + 5;
int vis[maxn][maxn], cap[3], ans[maxn];

void update_ans(const Node & u){
	for(int i = 0; i < 3; i ++){
		int d = u.v[i];
		if(ans[d] < 0 || u.dist < ans[d]) ans[d] = u.dist; 
	}
}

void solve(int a, int b, int c, int d){
	cap[0] = a, cap[1] = b, cap[2] = c;
	nodes.clear();
	memset(vis, 0, sizeof(vis));
	memset(ans, -1, sizeof(ans));
	priority_queue<int, vector<int>, cmp> q;

	Node start;
	start.dist = 0;
	start.v[0] = 0; start.v[1] = 0; start.v[2] = c;
	nodes.push_back(start);
	q.push(nodes.size()-1);
	vis[0][0] = 1;

	while(!q.empty()){
		Node u = nodes[q.top()]; q.pop();
		update_ans(u);
		if(ans[d] >= 0) break;
		for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++) if(i != j){
			if(u.v[i] == 0 || u.v[j] == cap[j]) continue;
			int amount = min(cap[j], u.v[i] + u.v[j]) - u.v[j];
			Node u2;
			memcpy(&u2, &u, sizeof(u));
			u2.dist = u.dist + amount;
			u2.v[i] -= amount;
			u2.v[j] += amount;
			if(!vis[u2.v[0]][u2.v[1]]){
				vis[u2.v[0]][u2.v[1]] = 1;
				nodes.push_back(u2);
				q.push(nodes.size()-1);
			}
		}
	}
	while(d >= 0){
		if(ans[d] >= 0){
			printf("%d %d\n", ans[d], d);
			return;
		}
		d--;
	}
}

int main(){
#ifdef LOCAL
	freopen("UVa.10603.in", "r", stdin);
	freopen("UVa.10603.out", "w", stdout);
#endif
	int T, a, b, c, d;
	scanf("%d", &T);
	while(T--){
		scanf("%d%d%d%d", &a, &b, &c, &d);
		solve(a, b, c, d);
	}
	return 0;
}

