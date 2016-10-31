#include<cstdio>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

int L, D, N;
struct village{
	int x, y;
	double l, r;
	village(int x = 0, int y = 0):x(x), y(y){
		double d = sqrt((D+y)*(D-y));
		l = max(0.0, x-d);
		r = min((double)L, x+d);
	}
	bool operator < (const village & rhs) const{
		return r < rhs.r;
	}
};
vector<village> v;

int main(){
#ifdef LOCAL
		freopen("UVa.1615.in", "r", stdin);
		freopen("UVa.1615.out", "w", stdout);
#endif
	int x, y;
	while(scanf("%d%d%d", &L, &D, &N) == 3){
		v.clear();
		while(N--){
			scanf("%d%d", &x, &y);
			v.push_back(village(x, y));
		}
		sort(v.begin(), v.end());
		int ans = 1;
		double x = v[0].r;
		for(unsigned int i = 1; i < v.size();){
			if(v[i].l <= x && v[i].r >= x) {
				i++;
				continue;
			}
			else{
				x = v[i].r;
				ans++;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

