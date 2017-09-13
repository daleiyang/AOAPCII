#include<cstdio>
#include<map>
#include<utility>
#include<cmath>
using namespace std;

const double EPS=1e-5;
typedef pair<int, int> P;
map<int, P> m;
map<int, P>::iterator it;

int main(){
#ifdef LOCAL
	freopen("UVA.1595.in", "r", stdin);
	freopen("UVA.1595.out", "w", stdout);
#endif
	int T, n, x, y;
	scanf("%d", &T);
	while(T--){
		m.clear();
		scanf("%d", &n);
		while(n--){
			scanf("%d%d", &x, &y);
			if(!m.count(y)){m[y] = make_pair(1, x);}
			else{m[y].first++; m[y].second += x;}
		}
		bool f = true; double xf; bool fi = true;
		for(it = m.begin(); it != m.end(); it++){
			P p = (*it).second;
			double t = (double)p.second / p.first;
			if(fi) {fi = false; xf = t;}
			else if(abs(xf - t) > EPS) {f = false; break;}
		}
		printf("%s", f?"YES\n":"NO\n");
	}
	return 0;
}

