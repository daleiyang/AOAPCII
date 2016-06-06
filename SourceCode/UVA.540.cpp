#include<cstdio>
#include<queue>
#include<map>
using namespace std;
const int maxn = 1000+10;

int main(){
#ifdef LOCAL
	freopen("UVA.540.in", "r", stdin);
	freopen("UVA.540.out", "w", stdout);
#endif
	int kase=0, t;
	while(scanf("%d", &t) == 1 && t){
		printf("Scenario #%d\n", ++kase);
		map<int, int> mp;
		for(int i=0; i<t; i++){
			int n, m;
			scanf("%d", &n);
			while(n--){scanf("%d", &m); mp[m]=i;}
		}
		queue<int> qs, q[maxn];
		for(;;){
			int x;
			char cmd[10];
			scanf("%s", cmd);
			if(cmd[0]=='S') break;
			else if(cmd[0]=='E'){
				scanf("%d", &x);
				int i=mp[x];
				if(q[i].empty()){qs.push(i);}
				q[i].push(x);
			}
			else if(cmd[0]=='D'){
				int i=qs.front();
				printf("%d\n", q[i].front());
				q[i].pop();
				if(q[i].empty()) qs.pop();
			}
		}
		printf("\n");
	}
	return 0;
}

