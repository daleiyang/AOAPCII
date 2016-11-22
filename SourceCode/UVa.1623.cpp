//http://www.lai18.com/content/5545061.html?from=cancel
#include<cstdio>
#include<cstring>
#include<set>
#include<algorithm>
using namespace std;

const int maxn = 1e6+5;

int ans[maxn], lst[maxn];
set<int> s;
set<int>::iterator it;

int main(){
#ifdef LOCAL
		freopen("UVa.1623.in", "r", stdin);
		freopen("UVa.1623.out", "w", stdout);
#endif
	int T, n, m, a;
	scanf("%d", &T);
	while(T--){
		memset(ans, 0, sizeof(ans));
		memset(lst, 0, sizeof(lst));
		s.clear();
		bool f = true;
		scanf("%d%d", &n, &m);
		for(int i = 0; i < m; i++){
			scanf("%d", &a);
			if(!f) continue; //eat remaining input after case failed.
			if(!a) s.insert(i);
			else{
				ans[i] = -1;
				it = s.lower_bound(lst[a]);
				if(it == s.end()){
					f = false;
				}
				else{
					ans[*it] = a;
					lst[a] = i;
					s.erase(it);
				}
			}
		}
		if(!f) printf("NO\n");
		else {
			printf("YES\n");
			for(int i = 0; i < m; i++){
				if(ans[i] >= 0) 
					printf("%d ", ans[i]);
			}
			printf("\n");
		}
	}
	return 0;
}

