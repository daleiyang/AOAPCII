#include<stdio.h>
#include<string.h>
int IP[1000+5][32+5];
int main(){
#ifdef LOCAL
	freopen("UVA.1590.in", "r", stdin);
	freopen("UVA.1590.out", "w", stdout);
#endif
	int n;
	while(scanf("%d", &n) != EOF){
		memset(IP, 0, sizeof(IP));
		for(int i=1; i<=n; i++){
			int t[4], idx=1;
			scanf("%d.%d.%d.%d", t, t+1, t+2, t+3);
			for(int j=0; j<4; j++){
				for(int k=7; k>=0; k--){
					IP[i][idx++]=(t[j]>>k)&1;
				}
			}
		}
		int m=32;
		for(int j=1; j<=32; j++){
			int f=1;
			for(int i=1; i<n; i++){
				if(IP[i][j]!=IP[i+1][j]){
					f=0;
					break;
				}
			}
			if(!f){
				for(int _j=j; _j<=32; _j++){
					for(int i=1; i<=n; i++){
						IP[i][_j]=0;
					}
				}
				m=j-1;
				break;
			}
		}
		for(int i=1; i<=4; i++){
			int num=0;
			for(int j=1; j<=8; j++){
				num = num*2 + IP[1][(i-1)*8 + j];
			}
			printf("%d%c", num, i==4?'\n':'.');
		}
		for(int i=1; i<=4; i++){
			int num=0;
			for(int j=1; j<=8; j++){
				num = num*2 + (((i-1)*8+j)<=m);
			}
			printf("%d%c", num, i==4?'\n':'.');
		}
	}
	return 0;
}

