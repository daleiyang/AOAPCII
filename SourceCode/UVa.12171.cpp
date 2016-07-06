#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;

const int maxn = 50 + 5;
const int maxc = 1000 + 1;

//original data
int n, x0[maxn], y0[maxn], z0[maxn], x[maxn], y[maxn], z[maxn];

//discretization related
int nx, ny, nz;
int xd[maxn*2], yd[maxn*2], zd[maxn*2];

//floodfill related
const int dx[] = {1, -1, 0,  0, 0,  0};
const int dy[] = {0,  0, 1, -1, 0,  0};
const int dz[] = {0,  0, 0,  0, 1, -1};
int color[maxn*2][maxn*2][maxn*2];

struct Cell{
	int x, y, z;
	Cell(int x = 0, int y = 0, int z = 0):x(x), y(y), z(z){}
	Cell neighbor(int i){
		return Cell(x+dx[i], y+dy[i], z+dz[i]);
	}
	bool valid(){
		return x >=0 && x < nx-1 && y >= 0 && y < ny-1 && z >= 0 && z < nz-1;
	}
	bool solid(){
		return color[x][y][z] == 1;
	}
	bool getVis(){
		return color[x][y][z] == 2;
	}
	void setVis(){
		color[x][y][z] = 2;
	}
	int volume(){
		return (xd[x+1]-xd[x]) * (yd[y+1]-yd[y]) * (zd[z+1]-zd[z]);
	}
	int area(int i){
		if(dx[i] != 0){return (yd[y+1]-yd[y]) * (zd[z+1]-zd[z]);} 
		else if(dy[i] != 0){return (xd[x+1]-xd[x]) * (zd[z+1]-zd[z]);}
		else return  (xd[x+1]-xd[x]) * (yd[y+1]-yd[y]);
	}
};

void discretize(int * a, int & n){
	sort(a, a+n);
	n = unique(a, a+n) - a;
}

int ID(int * a, int n, int x){
	return lower_bound(a, a+n, x) - a;
}

void floodfill(int & v, int & s){
	v = 0; s = 0;
	Cell c;
	c.setVis();
	queue<Cell> q;
	q.push(c);
	while(!q.empty()){
		Cell c = q.front(); q.pop();
		v += c.volume();
		for(int i = 0; i < 6; i++){
			Cell c2 = c.neighbor(i);
			if(!c2.valid()) continue;
			if(c2.solid()) s += c.area(i);
			else if(!c2.getVis()){
				c2.setVis();
				q.push(c2);
			}
		}
	}
	v = maxc * maxc * maxc - v;
}

void print(){
	for(int i = 0; i < nx; i++) printf("%d ", xd[i]); printf("\n");
	for(int i = 0; i < ny; i++) printf("%d ", yd[i]); printf("\n");
	for(int i = 0; i < nz; i++) printf("%d ", zd[i]); printf("\n");
}

int main(){
#ifdef LOCAL
	freopen("UVa.12171.in", "r", stdin);
	freopen("UVa.12171.out", "w", stdout);
#endif
	int T;
	scanf("%d", &T);
	while(T--){
		xd[0] = yd[0] = zd[0] = 0;
		xd[1] = yd[1] = zd[1] = maxc;
		nx = ny = nz = 2;
		scanf("%d", &n);
		for(int i = 0; i < n; i++){
			scanf("%d%d%d%d%d%d", &x0[i], &y0[i], &z0[i], &x[i], &y[i], &z[i]);
			x[i] += x0[i]; y[i] += y0[i]; z[i] += z0[i];
			xd[nx++] = x0[i]; xd[nx++] = x[i]; 
			yd[ny++] = y0[i]; yd[ny++] = y[i];
			zd[nz++] = z0[i]; zd[nz++] = z[i];
		}
		discretize(xd, nx);
		discretize(yd, ny);
		discretize(zd, nz);
		//print();

		memset(color, 0, sizeof(color));
		for(int i = 0; i < n; i++){
			int X0 = ID(xd, nx, x0[i]), X1 = ID(xd, nx, x[i]);
			int Y0 = ID(yd, ny, y0[i]), Y1 = ID(yd, ny, y[i]);			
			int Z0 = ID(zd, nz, z0[i]), Z1 = ID(zd, nz, z[i]);
			//printf("x0:%d X0:%d x:%d X1:%d; y0:%d Y0:%d y:%d Y1:%d; z0:%d Z0:%d z:%d Z1:%d\n", x0[i], X0, x[i], X1, y0[i], Y0, y[i], Y1, z0[i], Z0, z[i], Z1);
			for(int X = X0; X < X1; X++)
				for(int Y = Y0; Y < Y1; Y++)
					for(int Z = Z0; Z < Z1; Z++){
						color[X][Y][Z] = 1;
						//printf("%d %d %d\n", X, Y, Z);
					}
		}

		int v, s;
		floodfill(v, s);
		printf("%d %d\n", s, v);

	}
	return 0;
}

