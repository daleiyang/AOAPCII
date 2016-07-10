#include<cstdio>
#include<cstring>
using namespace std;

char s[128+5], leaf[128];
int order[7], input[7], n, m;

int main(){
#ifdef LOCAL
	freopen("UVa.712.in", "r", stdin);
	freopen("UVa.712.out", "w", stdout);
#endif
	int kase = 0;
	while(scanf("%d", &n) == 1 && n){
		for(int i = 0; i < n; i++){
			scanf("%s", s);
			order[i] = s[1]-'0'-1;
		}
		scanf("%s", leaf);
		scanf("%d", &m);
		printf("S-Tree #%d:\n", ++kase);
		while(m--){
			scanf("%s", s);
			for(unsigned int i = 0; i < strlen(s); i++){
				input[i] = s[i]-'0';
			}
			int ans = 0;
			for(int i = 0; i < n; i++){
				ans = ans * 2 + input[order[i]];
			}
			printf("%c", leaf[ans]);
		}
		printf("\n\n");
	}
	return 0;
}

