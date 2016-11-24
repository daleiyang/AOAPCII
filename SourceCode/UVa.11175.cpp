//http://www.cnblogs.com/137033036-wjl/p/4945084.html
#include<cstdio>
#include<vector>
#include<set>
using namespace std;

const int maxn = 300+5;

int m, k;
vector<int> in[maxn], out[maxn];
set<int> s;

bool solve(){
	for(int i = 0; i < m; i++){
		if(!in[i].size()) continue;
		s.clear();
		int len = out[in[i][0]].size();
		for(int j = 0; j < (int)out[in[i][0]].size(); j++)
			s.insert(out[in[i][0]][j]);
		for(int j = 1; j < (int)in[i].size(); j++){
			if((int)out[in[i][j]].size() != len){
				return false;
			}
			for(int p = 0; p < (int)out[in[i][j]].size(); p++){
				if(!s.count(out[in[i][j]][p]))
					return false;
			}
		}
	}
	return true;
}

int main(){
#ifdef LOCAL
		freopen("UVa.11175.in", "r", stdin);
		freopen("UVa.11175.out", "w", stdout);
#endif
	int T, kase = 0, a, b;
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &m, &k);
		for(int i = 0; i < maxn; i++){
			in[i].clear(); 
			out[i].clear();
		}
		for(int i = 0; i < k; i++){
			scanf("%d%d", &a, &b);
			out[a].push_back(b);
			in[b].push_back(a);
		}
		printf("Case #%d: ", ++kase);
		if(solve()) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}

