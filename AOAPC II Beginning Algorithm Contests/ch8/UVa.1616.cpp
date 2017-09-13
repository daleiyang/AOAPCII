#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 5;
const double EPS = 1e-9;

struct gang{
	int L, R;
	gang(int L = 0, int R = 0):L(L), R(R){}
	bool operator < (const gang & rhs) const{
		return L < rhs.L;
	}
} g[maxn];

int main(){
#ifdef LOCAL
		freopen("UVa.1616.in", "r", stdin);
		freopen("UVa.1616.out", "w", stdout);
#endif
	int n;
	while(scanf("%d", &n) == 1){
		for(int i = 0; i < n; i++){
			scanf("%d%d", &g[i].L, &g[i].R);
		}
		sort(g, g+n);

		double L = 0, R = 1000000, ans;
		//binary search to close the maxiaml length.
		while(R-L > EPS){
			double m = (R+L)/2;
			bool ok = true;
			double s = 0;
			for(int i = 0; i < n; i++){
				if(s < g[i].L) s = g[i].L;
				if(s + m > g[i].R) {
					ok = false;
					break;
				}
				s += m;
			}
			if(ok){
				ans = m;
				L = m;
			}
			else R = m;
		}

		//construct the fraction
		int rp = 0, rq = 1;
		for(int p, q = 1; q <= n; q++){
			p = round(ans * q);
			if(fabs((double)p/q - ans) < fabs((double)rp/rq - ans)){
				rp = p; rq = q;
			}
		}
		printf("%d/%d\n", rp, rq);
	}
	return 0;		
}

