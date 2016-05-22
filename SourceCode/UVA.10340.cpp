#include<stdio.h>
#include<string.h>
const int maxn = 102400;
char t[maxn], s[maxn];

int main(){
#ifdef LOCAL
	freopen("UVA.10340.in", "r", stdin);
	freopen("UVA.10340.out", "w", stdout);
#endif
	int tl, sl, it, is;
	while(scanf("%s", t) != EOF){
		scanf("%s", s);
		tl = strlen(t);
		sl = strlen(s);
		it = 0, is = 0;
		while(is<sl){
			if(t[it] != s[is]) is++;
			else {
				it++; 
				is++;
				if(it == tl) break;
			}
		}
		if(it==tl) printf("Yes\n");
		else printf("No\n");
	}
}

