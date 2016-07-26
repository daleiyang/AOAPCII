#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<ctime>
using namespace std;

const int maxn = 30;
char line[1000];
int p[maxn], vis[maxn][maxn], mark[maxn];

int main(){
#ifdef LOCAL
	freopen("UVa.140.in", "r", stdin);
	freopen("UVa.140.out", "w", stdout);
#endif
	while(scanf("%s", line) == 1 && line[0] != '#'){
		memset(vis, 0, sizeof(vis));
		memset(mark, 0, sizeof(mark));
		
		vector<int> v[maxn];
		int len = strlen(line), i = 0, f = 0, x, y; 
		while(i < len){
			if(line[i] == ':') {f = 1; i++; continue;}
			if(line[i] == ';') {f = 0; i++; continue;}
			if(!f){x = line[i++] - 'A'; mark[x] = 1;}
			else if(f){
				y = line[i++] - 'A'; 
				mark[y] = 1;
				if(!vis[x][y]){
					vis[x][y] = 1;
					v[x].push_back(y);
				}
			}
		}

		int n = 0, ans = maxn;
		for(int i = 0; i < maxn; i++){
			if(mark[i]) p[n++] = i;
		}
		int pos[maxn], best[maxn];
		do{
			for(int i = 0; i < n ;i++){
				pos[p[i]] = i;
			}
			int bandwidth = 0;
			for(int i = 0; i < n; i++){
				int le = v[p[i]].size();
				if(le/2 >= ans) goto L; //prune
				for(int j = 0; j < le;  j++){
					int band = abs(pos[p[i]] - pos[v[p[i]][j]]);
					if(band >= ans) goto L; //prune
					else{bandwidth = max(bandwidth, band);}
				}
			}	
			if(bandwidth < ans){
				ans = bandwidth;
				memcpy(best, p, sizeof(p));
			}
			L:;
		}while(next_permutation(p, p+n));

		for(int i = 0; i < n; i++){
			printf("%c ", best[i] + 'A');
		}
		printf("-> %d\n", ans);
	}
	//printf("Time used = %.4f\n", (double)clock()/CLOCKS_PER_SEC);
	return 0;
}

