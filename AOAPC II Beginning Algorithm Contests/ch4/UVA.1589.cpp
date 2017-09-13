#include<stdio.h>
#include<string.h>
const int maxn = 15;
char a[maxn][maxn];
int dx[4]={-1, 1, 0, 0}, dy[4]={0, 0, -1, 1};
int hx[8]={-2, -2, -1, 1, 2, 2, 1, -1}, hy[8]={-1, 1, 2, 2, 1, -1, -2, -2};
int bx[8]={-1, -1, 0, 0, 1, 1, 0, 0}, by[8]={0, 0, 1, 1, 0, 0, -1, -1};
int checkmate(int x, int y){
	for(int i=1; i<=10; i++){
		for(int j=1; j<=10; j++){
			char t = a[i][j];
			if(t=='Z'||t=='0') continue;
			int minx=x<i?x:i, maxx=x<i?i:x, miny=y<j?y:j, maxy=y<j?j:y;
			switch(t){
				case 'G':{
					if(j==y){
						for(minx++; minx<maxx; minx++) if(a[minx][j]!='0') break;
						if(minx==maxx) return 1;
					}
					break;
				}
				case 'R':{
					if(j==y){
						for(minx++; minx<maxx; minx++) if(a[minx][j]!='0') break;
						if(minx==maxx) return 1;
					}
					if(i==x){
						for(miny++; miny<maxy; miny++) if(a[i][miny]!='0') break;
						if(miny==maxy) return 1;
					}
					break;
				}
				case 'H':{
					for(int k=0; k<8; k++){
						int tx=i+hx[k], ty=j+hy[k];
						if(tx==x && ty==y && a[i+bx[k]][j+by[k]]=='0')
							return 1;
					}
					break;
				}
				case 'C':{
					if(j==y){
						int n=0;
						for(minx++; minx<maxx; minx++) if(a[minx][j]!='0') n++;
						if(n==1) return 1;
					}
					if(i==x){
						int n=0;
						for(miny++; miny<maxy; miny++) if(a[i][miny]!='0') n++;
						if(n==1) return 1;
					}
					break;
				}
			}
		}
	}
	return 0;
}
int main(){
#ifdef LOCAL
	freopen("UVA.1589.in", "r", stdin);
	freopen("UVA.1589.out", "w", stdout);
#endif
	int n, x0, y0;
	while(scanf("%d%d%d", &n, &x0, &y0) == 3 && n != 0){
		memset(a, '0', sizeof(a));
		a[x0][y0]='Z';
		while(n--){
			char t[2]; 
			int x, y;
			scanf("%s%d%d", t, &x, &y);
			a[x][y]=t[0];
		}
		int c=0, cc=0;
		for(int i=0; i<4; i++){
			int tx = x0 + dx[i];
			int ty = y0 + dy[i];
			if(tx < 1 || tx > 3 || ty < 4 || ty > 6) continue;
			c++;
			char t = a[tx][ty];
			a[tx][ty] = 'Z';
			a[x0][y0] = '0';
			if(checkmate(tx, ty)) cc++;
			a[tx][ty] = t;
			a[x0][y0] = 'Z';
		}
		if(c==cc) printf("YES\n");
		else printf("NO\n");
	};
}

