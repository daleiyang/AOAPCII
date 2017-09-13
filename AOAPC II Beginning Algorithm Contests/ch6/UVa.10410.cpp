#include<cstdio>
#include<vector>
#include<stack>
using namespace std;

const int maxn= 1000 + 5;

stack<int> s;
vector<int> nodes[maxn];
int pos[maxn];

int main(){
#ifdef LOCAL
		freopen("UVa.10410.in", "r", stdin);
		freopen("UVa.10410.out", "w", stdout);
#endif
	int n, t;
	while(scanf("%d", &n) == 1){
		while(!s.empty()) s.pop();
		for(int i = 1; i <= n; i++){
			nodes[i].clear();
			scanf("%d", &t);
			pos[t] = i;
		}

		int root;
		scanf("%d", &root);
		s.push(root);

		for(int i = 2; i <=n; i++){
			scanf("%d", &t);

			while(1){
				int u = s.top();
				if(u == root || (pos[u]+1) < pos[t]){
					nodes[u].push_back(t);
					s.push(t);
					break;
				}
				else{s.pop();}
			}	
		}

		for(int i = 1; i <= n; i++){
			printf("%d:", i);
			for(unsigned int j = 0; j < nodes[i].size(); j++){
				printf(" %d", nodes[i][j]);
			}
			printf("\n");
		}
	}
	return 0;
}

