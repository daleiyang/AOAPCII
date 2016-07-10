#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 7 + 5;
char s[128+5];
int order[7], leaf[128], input[7], n, m;

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
		scanf("%s", s);
		for(unsigned int i = 0; i < strlen(s); i++){
			leaf[i] = s[i]-'0';
		}
		printf("S-Tree #%d:\n", ++kase);
		scanf("%d", &m);
		while(m--){
			scanf("%s", s);
			for(unsigned int i = 0; i < strlen(s); i++){
				input[i] = s[i]-'0';
			}
			int ans = 0;
			for(int i = n-1, j = 0; i >=0; i--, j++){
				ans += (1<<i)*input[order[j]];
			}
			printf("%d", leaf[ans]);
		}
		printf("\n\n");
	}
	return 0;
}

