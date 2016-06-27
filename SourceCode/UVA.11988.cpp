#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 100000 + 5;
int last, cur, next[maxn];
char s[maxn];
	
int main(){
#ifdef LOCAL
	freopen("UVA.11988.in", "r", stdin);
	freopen("UVA.11988.out", "w", stdout);
#endif
	while(scanf("%s", s + 1) != EOF){
		int n = strlen(s + 1);
		last = cur = 0;
		next[0] = 0;

		for(int i = 1; i <=n; i++){
			char c = s[i];
			if(c == '[') {cur = 0;}
			else if(c == ']') cur = last;
			else{
				next[i] = next[cur];
				next[cur] = i;
				if(cur == last) last = i;
				cur = i;
			}
		}
		for(int i = next[0]; i!= 0; i = next[i]){
			printf("%c", s[i]);
		}
		printf("\n");
	}
	return 0;
}

