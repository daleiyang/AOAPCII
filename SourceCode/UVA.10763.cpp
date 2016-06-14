#include<cstdio>
#include<cstring>
#include<utility>
#include<algorithm>
using namespace std;

typedef pair<int, int> P;

const int maxn = 500000 + 5;
P a[maxn], b[maxn];

bool comp1(const P & a, const P & b){
	return (a.first < b.first) || (a.first == b.first && a.second < b.second);
}

bool comp2(const P & a, const P & b){
	return (a.second < b.second) || (a.second == b.second && a.first < b.first);
}

int main(){
#ifdef LOCAL
	freopen("UVA.10763.in", "r", stdin);
	freopen("UVA.10763.out", "w", stdout);
#endif
	int T, x, y;
	while(scanf("%d", &T) && T){
		for(int i = 0; i < T; i++){
			scanf("%d%d", &x, &y);
			a[i] = make_pair(x, y);
		}
		memcpy(b, a, sizeof(P)*T);
		sort(a, a + T, comp1);
		sort(b, b + T, comp2);
		bool r = true;
		for(int i = 0; i < T; i++){
			if(a[i].first != b[i].second || a[i].second != b[i].first) {r = false; break;}
		}
		if(r) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}

