#include<stdio.h>
#include<string.h>
const int maxn = 100;
const int big = 10000;
int r, c, n, d[maxn][maxn], d2[maxn][maxn], ans[maxn][maxn], f[maxn];
void copy(char type, int p, int q){
	if(type=='R'){
		for(int i=1; i<=c; i++)
			d[p][i]=d2[q][i];
	}else{
		for(int i=1; i<=r; i++)
			d[i][p]=d2[i][q];
	}
}
void del(char type){
	memcpy(d2, d, sizeof(d));
	int cnt = type=='R'?r:c, cnt2=0;
	for(int i=1; i<=cnt; i++){
		if(f[i]!=1) copy(type, ++cnt2, i);
	}
	if(type=='R') r=cnt2;
	else c=cnt2;
}
void ins(char type){
	memcpy(d2, d, sizeof(d));
	int cnt = type=='R'?r:c, cnt2=0;
	for(int i=1; i<=cnt; i++){
		if(f[i]==1) copy(type, ++cnt2, 0);
		copy(type, ++cnt2, i);
	}
	if(type=='R') r=cnt2;
	else c=cnt2;
}
int main(){
#ifdef LOCAL
	freopen("UVA.512.in", "r", stdin);
	freopen("UVA.512.out", "w", stdout);
#endif
	int r1, c1, r2, c2, kase=0, q;
	memset(d, 0, sizeof(d));
	char cmd[10];
	while(scanf("%d%d%d", &r, &c, &n) == 3 && !(r==0 && c==0)){
		for(int i=1; i<=r; i++)
			for(int j=1; j<=c; j++)
				d[i][j]=big*i+j;
		while(n--){
			scanf("%s", cmd);
			if(cmd[0]=='E'){
				scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
				int t=d[r1][c1]; d[r1][c1]=d[r2][c2]; d[r2][c2]=t;
			}else{
				int a, x;
				scanf("%d", &a);
				memset(f, 0, sizeof(f));
				for(int i=0; i<a; i++){
					scanf("%d", &x);
					f[x]=1;
				}
				if(cmd[0]=='D') del(cmd[1]);
				else ins(cmd[1]);
			}
		}
		memset(ans, 0, sizeof(ans));
		for(int i=1; i<=r; i++)
			for(int j=1; j<=c; j++)
				ans[d[i][j]/big][d[i][j]%big]=i*big+j;
		if(kase) printf("\n");
		printf("Spreadsheet #%d\n", ++kase);
		scanf("%d", &q);
		while(q--){
			scanf("%d%d", &r1, &c1);
			printf("Cell data in (%d,%d) ", r1, c1);
			if(ans[r1][c1]==0) printf("GONE\n");
			else printf("moved to (%d,%d)\n", ans[r1][c1]/big, ans[r1][c1]%big);
		}
	}
	return 0;
}

