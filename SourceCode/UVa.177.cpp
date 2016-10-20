#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
using namespace std;

//0: left; 1: up; 2:right; 3:down
char d[4] = {'_', '|', '_', '|'};

//0->3: left to down; 1->0: up to left; 2->1: rigth to up; 3->2: down to right
int rot[4] = {3, 0, 1, 2};

//when create the fisrt new line, calculate the start location based on the old start location.
//0->3: left to down; 1->0: up to left; 2->1: rigth to up; 3->2: down to right
int dx[4] = {0, 1,  0, -1};
int dy[4] = {1, 0, -1,  0};

int const maxn = (1<<13) + 5;

struct line{
	int sx, sy, ex, ey, type;
	line(int sx = 0, int sy = 0, int ex = 0, int ey = 0, int type = 0):sx(sx), sy(sy), ex(ex), ey(ey), type(type){};
	int mx, my; //relative x, y. for "|", we take lower point. for"_", we take left point.
	int r,c; //the row and column based on mx, my in output.
	int fr, fc; //final row and colmn.
} lines[maxn];

int nx[maxn];
int ans[512][512];

int main(){
#ifdef LOCAL
		freopen("UVa.177.in", "r", stdin);
		freopen("UVa.177.out", "w", stdout);
#endif
	int n;
	while(scanf("%d", &n) == 1 && n){
		fill(nx, nx+(1<<n)+5, 0);
		
		//draw unfolded lines
		int cnt = 1, minx = 0, miny = 0;
		lines[1] = line(1, 0, 0, 0, 0); //init line, start from (1,0) to (0,0), type  = 0 (left). line[0] is a dummy node.
		nx[0] = 1; // nx[0] represent header position.
		nx[1] = 0; //nx line for line[1], 0 represent it's the last one.
		for(int i = 1; i <= n; i++){ //unfold n times
			int nsx = lines[nx[0]].sx + dx[lines[nx[0]].type];
			minx = min(minx, nsx);
			int nsy = lines[nx[0]].sy + dy[lines[nx[0]].type];
			miny = min(miny, nsy);
			lines[++cnt] = line(nsx, nsy, lines[nx[0]].sx, lines[nx[0]].sy, rot[lines[nx[0]].type]);
			nx[cnt] = nx[0];
			int cur = nx[nx[0]];
			nx[0] = cnt;
			while(cur){
				int nsx = lines[nx[0]].sx + dx[lines[cur].type];
				minx = min(minx, nsx);
				int nsy = lines[nx[0]].sy + dy[lines[cur].type];
				miny = min(miny, nsy);
				lines[++cnt] = line(nsx, nsy, lines[nx[0]].sx, lines[nx[0]].sy, rot[lines[cur].type]);
				nx[cnt] = nx[0];
				nx[0] = cnt;
				cur = nx[cur];
			}
		}

		//coordinate translation
		for(int i = 1; i <= cnt; i++){
			lines[i].sx -= minx; lines[i].sy -= miny;
			lines[i].ex -= minx; lines[i].ey -= miny;
		}

		//calculate the relative x, y to get intermediate result to produce the final row and column.
		int maxr = 0;
		for(int i = 1; i <= cnt; i++) {
			if(lines[i].type == 1 || lines[i].type == 3){ //relative x, y. for "|", we take lower point.
				lines[i].mx = lines[i].sx;
				lines[i].my = min(lines[i].sy, lines[i].ey);

				lines[i].r = lines[i].my;
				lines[i].c = 2*lines[i].mx;
			}
			else if(lines[i].type == 0 || lines[i].type == 2){ //relative x, y. for "_", we take left point.
				lines[i].mx = min(lines[i].sx, lines[i].ex);
				lines[i].my = lines[i].sy;

				lines[i].r = lines[i].my;
				lines[i].c = 2*lines[i].mx+1;
			}
			maxr = max(maxr, lines[i].r);
		}

		memset(ans, 0, sizeof(ans));
		
		int maxc[1024];
		memset(maxc, 0, sizeof(maxc));
		//row, column coordinate translation
		int minfc = 0x7FFFFFFF;
		for(int i = 1; i <= cnt; i++) {
			lines[i].fr = abs(maxr - lines[i].r);
			lines[i].fc = lines[i].c;
			minfc = min(minfc, lines[i].fc);
			maxc[lines[i].fr] = max(maxc[lines[i].fr], lines[i].fc);
			if(lines[i].type == 1 || lines[i].type == 3){
				ans[lines[i].fr][lines[i].fc] = 1; //"|"
			}
			if(lines[i].type == 0 || lines[i].type == 2){
				ans[lines[i].fr][lines[i].fc] = 2; //"_"
			}
		}

		for(int r = 0; r <= maxr; r++){
			for(int c = minfc; c <= maxc[r]; c++){
				if(ans[r][c] == 0) printf(" ");
				else if(ans[r][c] == 1) printf("|");
				else if(ans[r][c] == 2) printf("_");
			}
			printf("\n");
		}
		printf("^\n");
	}
	//printf("Time used = %.4f", (double)clock()/CLOCKS_PER_SEC);
	return 0;
}

