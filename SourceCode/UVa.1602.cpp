#include<cstdio>
#include<set>
#include<algorithm>
using namespace std;

struct Cell{
	int x, y;
	Cell(int x = 0, int y = 0):x(x), y(y){};
	bool operator < (const Cell & rhs) const {
		return (x < rhs.x) || (x == rhs.x && y < rhs.y ); 
	}
};

typedef set<Cell> Polyomino;

#define FOR_CELL(c, p) for(Polyomino::const_iterator c = (p).begin(); c != (p).end(); ++c)

Polyomino normalize(const Polyomino & p){
	int minx = p.begin()->x, miny = p.begin()->y;
	FOR_CELL(c, p){
		minx = min(minx, c->x);
		miny = min(miny, c->y);
	}
	Polyomino p2;
	FOR_CELL(c, p){
		p2.insert(Cell(c->x - minx, c->y - miny));
	}
	return p2;
}

Polyomino rotate(const Polyomino & p){
	Polyomino p2;
	FOR_CELL(c, p){
		p2.insert(Cell(c->y, -(c->x)));
	}
	return normalize(p2);
}

Polyomino flip(const Polyomino & p){
	Polyomino p2;
	FOR_CELL(c, p){
		p2.insert(Cell(-(c->x), c->y));
	}
	return normalize(p2);
}

int dx[4] = {-1, 1, 0,  0};
int dy[4] = { 0, 0, 1, -1};
const int maxn = 10;
set<Polyomino> poly[maxn+1];
int ans[maxn+1][maxn+1][maxn+1];

void check_polyomino(const Polyomino & p0, const Cell & c){
	Polyomino p = p0;
	p.insert(c);
	p = normalize(p);

	int n = p.size();
	for(int i = 0; i < 4; i++){
		if(poly[n].count(p) != 0) return;
		p = rotate(p);
	}
	p = flip(p);
	for(int i = 0; i < 4; i++){
		if(poly[n].count(p) != 0) return;
		p = rotate(p);
	}
	poly[n].insert(p);
}

void generate(){
	Polyomino p;
	p.insert(Cell(0, 0));
	poly[1].insert(p);

	//generate
	for(int i = 2; i <= maxn; i++){
		for(set<Polyomino>::iterator p = poly[i-1].begin(); p != poly[i-1].end(); p++){
			FOR_CELL(c, *p)
				for(int j = 0; j < 4; j++){
					Cell newc(c->x + dx[j], c->y + dy[j]);
					if(p->count(newc) == 0) check_polyomino(*p, newc);
				}
		}
	}

	//precompute answer
	for(int n = 1; n <= maxn; n++)
		for(int w = 1; w <= maxn; w++)
			for(int h = 1; h <= maxn; h++){
				int cnt = 0;
				for(set<Polyomino>::iterator p = poly[n].begin(); p != poly[n].end(); p++){
					int maxX = 0, maxY = 0;
					FOR_CELL(c, *p){
						maxX = max(maxX, c->x);
						maxY = max(maxY, c->y);
					}
					if(min(maxX, maxY) < min(h, w) && max(maxX, maxY) < max(h, w)){
						cnt++;
					}
				}
				ans[n][w][h] = cnt;
			}
}

int main(){
#ifdef LOCAL
		freopen("UVa.1602.in", "r", stdin);
		freopen("UVa.1602.out", "w", stdout);
#endif
	generate();

	int n, w, h;
	while(scanf("%d%d%d", &n, &w, &h) == 3){
		printf("%d\n", ans[n][w][h]);
	}
	return 0;
}

