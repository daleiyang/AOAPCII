#include<stdio.h>
#include<string.h>
char x[256], y[256], ch[30];

int main(){
#ifdef LOCAL
	freopen("UVA.489.in", "r", stdin);
	freopen("UVA.489.out", "w", stdout);
#endif
	int n;
	while(scanf("%d", &n) && (n != -1)){
		printf("Round %d\n", n);
		scanf("%s%s", x, y);
		memset(ch, 0, sizeof(ch));
		int err=0, lx=strlen(x), ly=strlen(y), c=0, w=0, l=0;
		for(int i=0; i<ly; i++){
			if(ch[y[i]-'a']==1) continue;
			else ch[y[i]-'a']=1;
			int f=0;
			for(int j=0; j<lx; j++){
				if(x[j]==y[i]){f=1; c++;}
			}
			if(c==lx) {w=1;break;}
			if(!f) err++;
			if(err==7) {l=1; break;}
		}
		if(w) printf("You win.\n");
		else if(l) printf("You lose.\n");
		else printf("You chickened out.\n");
	}
	return 0;
}

