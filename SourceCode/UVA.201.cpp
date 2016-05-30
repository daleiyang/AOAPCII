#include<stdio.h>
#include<string.h>
const int maxn = 15;
int h[maxn][maxn];
int v[maxn][maxn];
int count[maxn];

int main(){
#ifdef LOCAL
		freopen("UVA.201.in", "r", stdin);
		freopen("UVA.201.out", "w", stdout);
#endif
	int d, kase=0;
	while(scanf("%d", &d) != EOF){
		memset(h, 0, sizeof(h));
		memset(v, 0, sizeof(v));
		memset(count, 0, sizeof(count));
		int n, tx, ty;
		char a[2];
		scanf("%d", &n);
		while(n--){
			scanf("%s%d%d", a, &tx, &ty);
			if(a[0] == 'H') h[tx][ty] = 1;
			if(a[0] == 'V') v[tx][ty] = 1;
		}
		if(kase) printf("\n**********************************\n\n");
		printf("Problem #%d\n\n", ++kase);
		for(int len = 1; len <= d - 1; len++){
			for(int x = 1; x <= d - len; x++){
				for(int y = 1; y <= d - len; y++){
					int k;
					for(k = 0; k < len; k++){
						if(h[x][y + k] != 1) break;
					}
					if(k != len) continue; 
					for(k = 0; k < len; k++){
						if(h[x + len][y + k] != 1) break;
					}
					if(k != len) continue; 
					for(k = 0; k < len; k++){
						if(v[y][x + k] != 1) break;
					}
					if(k != len) continue; 
					for(k = 0; k < len; k++){
						if(v[y + len][x + k] != 1) break;			
					}
					if(k != len) continue; 
					count[len]++;
				}
			}	
		}
		n=0;
		for(int i = 1; i <= maxn; i++){
			if(count[i] > 0){
				printf("%d square (s) of size %d\n", count[i], i);
				n++;
			}
		}
		if(n == 0) printf("No completed squares can be found.\n");
	}
	return 0;
}

