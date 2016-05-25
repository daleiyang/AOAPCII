#include<stdio.h>
#include<string.h>
char x[256], y[256], ch[30];
int win, lost, left, chance;
void guess(char c){
	if(ch[c-'a']==1) return;
	else ch[c-'a']=1;
	int bad=1;
	for(unsigned int j=0; j<strlen(x); j++){
		if(x[j]==c){bad=0; left--;}
	}
	if(bad) chance--;
	if(!chance) lost=1;
	if(!left) win=1;
}
int main(){
#ifdef LOCAL
	freopen("UVA.489.in", "r", stdin);
	freopen("UVA.489.out", "w", stdout);
#endif
	int rnd;
	while(scanf("%d%s%s", &rnd, x, y) == 3 && (rnd != -1)){
		printf("Round %d\n", rnd);
		memset(ch, 0, sizeof(ch));
		chance=7, win=0, lost=0, left=strlen(x);
		for(unsigned int i=0; i<strlen(y); i++){
			guess(y[i]);
			if(win||lost) break;		
		}
		if(win) printf("You win.\n");
		else if(lost) printf("You lose.\n");
		else printf("You chickened out.\n");
	}
	return 0;
}

