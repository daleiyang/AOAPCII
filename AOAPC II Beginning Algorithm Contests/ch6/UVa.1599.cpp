#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 5;
const int INF = 1000000000; //maximum color
int n;

struct Edge{
	int u, v, c;
	Edge(int u = 0, int v = 0, int c = 0):u(u),v(v),c(c){}
};

vector<Edge> edges;
vector<int> G[maxn];

void addEdge(int u, int v, int c){
	edges.push_back(Edge(u, v, c));
	int idx = edges.size()-1;
	G[u].push_back(idx);
}

int d[maxn], vis[maxn];
void reverse_bfs(){
	memset(d, 0, sizeof(d));
	memset(vis, 0, sizeof(vis));
	d[n-1] = 0;
	vis[n-1] = 1;
	queue<int> q;
	q.push(n-1);
	while(!q.empty()){
		int v = q.front(); q.pop();
		for(unsigned int i = 0; i < G[v].size(); i++){
			Edge e = edges[G[v][i]];
			int u = e.v;
			if(!vis[u]){
				vis[u] = 1;
				d[u] = d[v] + 1;
				q.push(u);
			}	
		}
	}
}

void bfs(){
	memset(vis, 0, sizeof(vis));
	vis[0] = 1;
	vector<int> currN, path;
	currN.push_back(0);
	
	for(int i = 0; i < d[0]; i++){ //step by step
		int minC = INF;
		for(unsigned int j = 0; j < currN.size(); j++){
			int u = currN[j]; 
			for(unsigned int k = 0; k < G[u].size(); k++){
				Edge e = edges[G[u][k]];
				int v = e.v;
				if(d[u] == d[v] + 1){
					minC =min(e.c, minC);
				}
			}
		}
		path.push_back(minC); //find the minimal color in the shortest path for this setp
		vector<int> newN;
		for(unsigned int j = 0; j < currN.size(); j++){
			int u = currN[j];
			for(unsigned int k = 0; k < G[u].size(); k++){
				Edge e = edges[G[u][k]];
				int v = e.v;
				if((d[u] == d[v] + 1) && !vis[v] && minC == e.c){
					vis[v] = true;
					newN.push_back(v);
				}
			}
		}
		currN = newN;
	}

	printf("%d\n", (int)path.size());
	printf("%d", path[0]);
	for(unsigned int i = 1; i < path.size(); i++)
		printf(" %d", path[i]);
	printf("\n");
}

int main(){
#ifdef LOCAL
	freopen("UVa.1599.in", "r", stdin);
	freopen("UVa.1599.out", "w", stdout);
#endif
	int m, u, v, c;
	while(scanf("%d%d", &n, &m) == 2){
		edges.clear();
		for(int i = 0; i < n; i++) G[i].clear();
		while(m--){
			scanf("%d%d%d", &u, &v, &c);
			addEdge(u-1, v-1, c);
			addEdge(v-1, u-1, c);
		}
		reverse_bfs();
		bfs();
	}
	return 0;
}

