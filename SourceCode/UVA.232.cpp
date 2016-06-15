#include<stdio.h>
#include<string.h>
char a[11][11];
int p[11][11];
int main(){
#ifdef LOCAL
	freopen("UVA.232.in", "r", stdin);
	freopen("UVA.232.out", "w", stdout);
#endif
	int r, c, kase = 0;
	char temp[11];
	while(1){
		memset(a, 0, sizeof(a));
		memset(p, 0, sizeof(p));
		scanf("%d", &r);
		if(r == 0) break;
		scanf("%d", &c);
		for(int i = 0; i < r; i++){
			scanf("%s", temp);
			for(int j = 0; j < c; j++){
				a[i][j] = temp[j];
			}
		}
		int t = 0;
		for(int i = 0; i < r; i++){
			for(int j = 0; j < c; j++){
				if(a[i][j] != '*' 
					&& ((j-1<0) || ((j-1>=0) && a[i][j-1] == '*') || (i-1 < 0) || ((i-1>=0) && a[i-1][j] == '*'))){
					p[i][j] = ++t;
				}
			}
		}
		if(kase) printf("\n");
		printf("puzzle #%d:\nAcross\n", ++kase);
		for(int i = 0; i < r; i++){
			int j = 0;
			while(j < c){
				if(p[i][j] != 0 && ((j - 1 < 0) || a[i][j-1] == '*')){
					printf("%3d.", p[i][j]);
					do{
						printf("%c", a[i][j++]);
					}while(j < c && a[i][j] != '*');
					printf("\n");
				}else j++;
			}
		}
		printf("Down\n");
		for(int i = 0; i < r; i++){
			for(int j = 0; j < c; j++){
				if(p[i][j] != 0 && ((i - 1 < 0) || a[i-1][j] == '*')){
					int x = i;
					printf("%3d.", p[i][j]);
					do{
						printf("%c", a[x++][j]);
					}while(x < r && a[x][j] != '*');
					printf("\n");
				}
			}
		}
	}
	return 0;
}

