//https://github.com/morris821028/UVa/blob/master/volume125/12559%20-%20Finding%20Black%20Circles%5BCut%5D.cpp
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;

const int R = 128; //radius.
const int maxr = R + 5;
const int maxn = 256; //~radius * 2.
const double EPS = 1e-6;
char cp[maxr][maxn][maxn]; // hold circle pattern.
vector<pair<int, int> > cv[maxr]; // '1' vertical list in specific circle. maxr is radius
char s[maxn][maxn]; //input data.
int cw[maxr], ch[maxr]; //circle width and height.
int cc[maxr]; //'1' count in circle with specific radius.
double dx[] = {0,  0,  1,  1,  1, -1, -1,  -1}; //we search 8 position around one 1*1 pixel central
double dy[] = {1, -1,  0,  1, -1,  0,  1,  -1}; //we search 8 position around one 1*1 pixel central

struct Pos{
	int x, y, r; //x for width, y for height 
	Pos(int x = 0, int y = 0, int r = 0):x(x), y(y), r(r){}
	bool operator < (const Pos & rhs) const{
		if(r != rhs.r) return r < rhs.r;
		if(x != rhs.x) return x < rhs.x;
		return y < rhs.y;
	}
};

void pattern(int r){
	double x, y; //8 position around (i, j)
	cw[r] = ch[r] = 2*r+1; //end index for this r.
	for(int i = 0; i <= 2*r; i++){
		for(int j = 0; j <= 2*r; j++){
			bool in = false, out = false;
			for(int k = 0; k < 8; k++){
				x = i + dx[k]/2;
				y = j + dy[k]/2;
				if(pow(x-r, 2) + pow(y-r, 2) < r*r + EPS)
					in = true; //find a position inside circle wlhose radius is r.
				if(pow(x-r, 2) + pow(y-r, 2) > r*r - EPS)
					out = true; //find a position outside of circle whose radius is r.
			}
			if(in && out){ //because there are position inside and outside the circle with radius r, (i, j) must be on the circle.
				cv[r].push_back(make_pair(i, j));
				cc[r]++; 
				cp[r][i][j] = '1';
			}
			else cp[r][i][j] = '0';
		}
		cp[r][i][2*r+1] = '\0';
	}
	random_shuffle(cv[r].begin(), cv[r].end());
}

int main(){
#ifdef LOCAL
			freopen("UVa.12559.in", "r", stdin);
			freopen("UVa.12559.out", "w", stdout);
#endif
	for(int i = 5; i <= R; i++)
		pattern(i);
	int T, kase = 0, w, h, p, q;
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &w, &h);
		for(int i = 0; i < h; i++)
			scanf("%s", s[i]);
		vector<Pos> ret;
		int r = min(w, h);
		for(int ir = 5; ir <= r; ir++){
			p = cw[ir], q = ch[ir];
			int pw = w-p; //max possible of start left width index.
			int qh = h-q; //max possible of start top hight index.
			//enumerate top left corner
			for(int i = 0; i <= pw; i++){
				for(int j = 0; j <= qh; j++){
					int c = 0;  // match position count
					int nc = 0; // not match position count
					for(int k = 0; k < (int)cv[ir].size(); k++){
						int x = cv[ir][k].first;
						int y = cv[ir][k].second;
						if(s[j+y][i+x] == '1') c++; //transfer corrdinate?
						else{
							nc++;
							//pruning based on a broader condition
							if(nc >= cc[ir]/20 && nc > 5)
								break;
						}
					}
					if(c >= cc[ir]*0.95) //magic number. It should be 0.98, but I couldn't get AC with 0.98
						ret.push_back(Pos(i+ir, j+ir, ir));
				}
			}
		}
		printf("Case %d: %d", ++kase, (int)ret.size());
		sort(ret.begin(), ret.end());
		for(int i = 0; i < (int)ret.size(); i++){
			printf(" (%d,%d,%d)", ret[i].r, ret[i].x, ret[i].y);
		}
		printf("\n");
	}
	return 0;
}

