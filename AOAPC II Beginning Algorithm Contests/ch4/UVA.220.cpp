#include<stdio.h>
#include<string.h>
const int maxn = 10;
char a[maxn][maxn];
int cb, cw;
char player;
int dx[] = {1, 1, 0, -1, -1, -1, 0, 1};
int dy[] = {0, -1, -1, -1, 0, 1, 1, 1};
void quit(){
	for(int i = 1; i <= 8; i++){
		for(int j = 1; j <= 8; j++){
			printf("%c", a[i][j]);
		}
		printf("\n");
	}
}
int checkone(int x, int y, int dx, int dy){
	int n = 0;
	while(1){
		x += dx; y += dy;
		if(x < 1 || x > 8 || y < 1 || y > 8) return 0;
		if(a[x][y] == '-') return 0;
		if(a[x][y] == player && n == 0) return 0;
		if(a[x][y] == player && n > 0) return 1;
		n++;
	}
}
void move(int x, int y){
	int f=0;
	for(int k = 0; k < 8; k++){
		if(checkone(x, y, dx[k], dy[k])){
			f = 1;
			break;
		}
	}
	if(f == 0) player = player == 'W'?'B':'W';
	int sum=0;
	for(int k = 0; k < 8; k++){
		int n[10], m[10], c = 0, x0 = x, y0 = y;
		while(1){
			x0 += dx[k];
			y0 += dy[k];
			if(x0 < 1 || x0 > 8 || y0 < 1 || y0 > 8) break;
			if(a[x0][y0] == '-') break;
			if(a[x0][y0] == player && c == 0) break;
			if(a[x0][y0] == player && c > 0){
				a[x][y] = player;
				for(int u = 0; u < c; u++) {a[n[u]][m[u]] = player;}
				sum += c;
				break;
			}else{
				n[c] = x0; m[c] = y0; c++;
			}
		}
	}
	if(player == 'B') {cb += sum + 1; cw -= sum;}
	else{cb -= sum; cw += sum + 1;}
	player = player == 'W'?'B':'W';
	printf("Black -%3d White -%3d\n", cb, cw);
}
void list(){
	int f = 0;
	for(int i = 1; i <=8; i++){
		for(int j = 1; j <= 8; j++){
			if(a[i][j] == '-'){
				for(int k = 0; k < 8; k++){
					if(checkone(i, j, dx[k], dy[k])){
						if(!f) printf("(%d,%d)", i, j);
						else printf(" (%d,%d)", i, j);
						f = 1;
						break;
					}
				}
			}
		}
	}
	if(f == 1) printf("\n");
	if(f == 0) printf("No legal move.\n");
}
int main(){
#ifdef LOCAL
	freopen("UVA.220.in", "r", stdin);
	freopen("UVA.220.out", "w", stdout);
#endif
	int n, kase = 0;
	scanf("%d", &n);
	while(n--){
		memset(a, 0, sizeof(a));
		cb=0, cw=0;
		char z[10];
		for(int i = 1; i <= 8; i++){
			scanf("%s", z);
			for(int j = 0; j < 8; j++){
				a[i][j+1] = z[j];
				if(z[j] == 'W') cw++;
				if(z[j] == 'B') cb++;
			}
		}
		scanf("%s", z);
		player = z[0];
		if(kase++) printf("\n");
		while(1){
			scanf("%s", z);
			if(z[0] == 'Q'){
				quit();
				break;
			}
			if(z[0] == 'L') list();
			if(z[0] == 'M') move(z[1]-'0', z[2]-'0');
		}
	}
	return 0;
}

