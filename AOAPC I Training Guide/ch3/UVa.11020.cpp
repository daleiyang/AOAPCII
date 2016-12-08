#include<cstdio>
#include<set>
using namespace std;

struct Point{
	int x, y;
	bool  operator < (const Point & rhs) const{
		return x < rhs.x || (x == rhs.x && y < rhs.y);
	}
};

multiset<Point> S;
multiset<Point>::iterator it;

int main(){
#ifdef LOCAL
	freopen("UVa.11020.in", "r", stdin);
	freopen("UVa.11020.out", "w", stdout);
#endif
	int T, n, x, y;
	scanf("%d", &T);
	for(int kase = 1; kase <= T; kase++){
		if(kase > 1) printf("\n");
		printf("Case #%d:\n", kase);
		S.clear();
		scanf("%d", &n);
		while(n--){
			scanf("%d%d", &x, &y);
			Point p = (Point){x, y};
			it = S.lower_bound(p);
			if(it == S.begin() || (--it)->y > y){
				S.insert(p);
				it = S.upper_bound(p);
				while(it != S.end() && it->y >= y) S.erase(it++);
			}
			printf("%d\n", (int)S.size());
		}
	}
	return 0;
}

