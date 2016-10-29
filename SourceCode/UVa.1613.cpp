#include<cstdio>
#include<algorithm>
#include<vector>
#include<climits>
using namespace std;

const int maxn = 9999 + 5;

int ans[maxn], cnt[maxn], k, vis[maxn];
vector<int> G[maxn];

void dfs(int idx){
	vis[idx] = 1;
	//color sub node first;
	for(unsigned int i = 0; i < G[idx].size(); i++){
		if(!vis[G[idx][i]]) dfs(G[idx][i]);
	}
	//calculate the color around current node
	for(unsigned int i = 0; i < G[idx].size(); i++){
		if(ans[G[idx][i]] != -1) cnt[ans[G[idx][i]]] += 1;
	}
	//color current node based on the color around it.
	int t = 0;
	while(cnt[t] > 0) t++;
	ans[idx] = t;
	//for performance consideration
	for(unsigned int i = 0; i < G[idx].size(); i++){
		if(ans[G[idx][i]] != -1) cnt[ans[G[idx][i]]] -= 1;
	}
}

int main(){
#ifdef LOCAL
		freopen("UVa.1613.in", "r", stdin);
		freopen("UVa.1613.out", "w", stdout);
#endif
	int n, m, a, b;
	while(scanf("%d%d", &n, &m) == 2){
		for(int i = 0; i < n; i++) G[i].clear();
		for(int i = 0; i < m; i++){
			scanf("%d%d", &a, &b);
			a--, b--;
			G[a].push_back(b);
			G[b].push_back(a);
		}
		k = INT_MIN; int s = INT_MAX, sidx;
		for(int i = 0; i < n; i++){
			if((int)G[i].size() > k) k = G[i].size(); //find the max degree
			if((int)G[i].size() < s) {
				s = G[i].size(); //find the min degree
				sidx = i;
			}
		}
		if(k%2 == 0) k += 1;
		fill(vis, vis+n, 0);
		fill(ans, ans+n, -1);
		/*
			There must be a node whose degree <= k-1, there is the prove:
			based on the problem description, n and k are all odd number.
			if all the node has k degree, we will have n*k edges which is alos a odd number.
			But the G is a undirected graph, so the real edge number must be n*k % 2 == 0, there we 
			have a conflict.

			The reason we start dfs from this min degree is: from the dfs code, you
			could find out that we color the surrounding node frist, and calculate the color for the current
			node second. because we start from min degree whose degree <=k-1, this means after surronding
			color has been decided, we still has an option color for this node to choose.
			
			by dfs, we color the deepest node first, and it's parent node is not color yet, so, the child node need to 
			decide it's color with the degree <= k-1, which means child node will find a appropriate color. This logic 
			will happen again and again, utill we back to the sidx node which is described in the previous paragraph.
 		*/
		dfs(sidx); 
		printf("%d\n", k);
		for(int i = 0; i < n; i++) printf("%d\n", ans[i]+1);
		printf("\n");
	}
	return 0;
}

