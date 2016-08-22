#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 15;

int s[maxn], st[maxn], vis[maxn], n;

int bitCount(int i){
	return i == 0 ? 0 : bitCount(i>>1) + (i&1);
}

void dfs(int u,int pre)
{
    for(int i=0; i < n; i++){
        if(i != pre && st[u] & (1 << i)){
            vis[i]++;
            if(vis[i] < 2)
                dfs(i,u);
        }
    }
}

bool solve(int test){
	for(int i = 0; i < n; i++) {st[i] = s[i];}

	//remove
	for(int i = 0; i < n; i++){
		if(test&(1<<i)){
			st[i] = 0;
			for(int j = 0; j < n; j++){
				if(j!=i && (st[j]&(1<<i)))
					st[j] ^= (1<<i);
			}
		}
	}

	//check degree
	for(int i = 0; i < n; i++){
		if(!(test&(1<<i))&&bitCount(st[i])>2)
			return false;
	}

	// checking ring
    int link=0;
    memset(vis,0,sizeof(vis));
    for(int i=0; i<n; i++){
        if(!vis[i]&&!(test&(1<<i))){
            link++;
            vis[i]++;
            dfs(i,-1);
        }
    }
    for(int i=0; i<n; i++)
        if(vis[i] >= 2)
            return false;

	if(link-1>bitCount(test))
		return false;

	return true;
		
}

int main(){
#ifdef LOCAL
	freopen("UVa.818.in", "r", stdin);
	freopen("UVa.818.out", "w", stdout);
#endif
	int kase = 0;
	while(scanf("%d", &n) && n){
		int x, y;
		memset(s, 0, sizeof(s));
		while(scanf("%d%d", &x, &y) == 2 && x != -1 && y != -1){
			s[x-1] |= (1<<(y-1));
			s[y-1] |= (1<<(x-1));
		}
		int ans = n;
		for(int i = 0; i < (1<<n); i++)
			if(solve(i))
				ans = min(ans, bitCount(i));
		printf("Set %d: Minimum links to open is %d\n", ++kase, ans);
	}
	return 0;
}

