//https://github.com/morris821028/UVa/blob/master/temp/1580%20-%20Pirate%20Chest.cpp
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 500+5;
const int INF = 0x3f3f3f3f;

int g[maxn][maxn], mx[maxn], a, b, n, m;

int getHeight(int w, int h, int d){
	if(d == 0) return 0;
	d = -d; //d, prev and g[x][y] is negative number
	long long base = w*h*d; //water volumn is taken
	/*
	1. base is the water volumn is taken. Notice that with 'd', the block is touching the surface.
	2. n*m-w*h is the area without block. base/(n*m - w*h) is the height this arer could rise. We only need the round number because block is rising with unit 1.
	3. if base%(n*m - w*h) == 0, means if we rise block to base/(n*m - w*h), our block top surface will be the same as water level, in this case, subtract 1.
	*/
	int ret = base/(n*m - w*h) - (base%(n*m - w*h) == 0);
	return d+ret;
}

int main(){
#ifdef LOCAL
	freopen("UVA.1580.in", "r", stdin);
	freopen("UVA.1580.out", "w", stdout);
#endif
	while(scanf("%d%d%d%d", &a, &b, &m, &n) == 4){
		for(int i = 0; i < m; i++){
			for(int j = 0; j < n; j++){
				scanf("%d", &g[i][j]);
				g[i][j] = -g[i][j];
			}
		}
		if(a > b) swap(a, b); //make following logic easier, a and b are max width or height
		long long ans = 0;
		for(int i = 0; i < m; i++){ //enumerate column m combination with j
			for (int j = 0; j < n; j++) mx[j] = -INF; //leverage mx to remeber the max depth in this column => i,j combination
			for(int j = i; j < m; j++){//enumerate column m combination with i
				if(j-i+1 > b) break; //because b >= a,  j-i+1 is the width of column, this number shouldn't greater than b
				for(int k = 0; k < n; k++){ //enumerate row n combination with l
					int prev = -INF; // pass the max depth between rows.
					for(int l = k; l < n; l++){ //enumerate row n combination with k
						if(l-k+1 > b) break; //because b >= a,  l-k+1 is the length of column, this number shouldn't greater than b
						mx[l] = max(mx[l], g[j][l]); //find the max depth in the same row in this i,j combination.
						prev = max(prev, mx[l]);
						int w = j-i+1; //width for current block
						int h = l-k+1; //height for the current block. height here is not depth 
						if(w > h) swap(w, h);
						if(w <= a && h <=b){ //elegant logic is check a, b constrains with logic line number: 33, 38, 42 
							//based on w,h,depth in this enumerate round, we know the water volumn is taken by block is w*h*depth. 
							//we need to found out the max depth we could get based on the water volumn is taken.
							long long v = getHeight(w, h, prev)*w*h; 
							ans = max(ans, v);
						}
					}
				}
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}

