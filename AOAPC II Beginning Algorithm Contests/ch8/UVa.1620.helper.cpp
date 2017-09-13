#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<vector>
using namespace std;

const int maxn = 15, maxm = 200000000, maxd = 10;
int num[maxn], n, m;

struct node{
	int num[maxn];
	int pre, d;
	bool check(){
		int a = 0, b = 0, c = 0, d = 0; //a = -1, b = 1, c= n-1, d= -(n-1)
		for(int i = 0; i < n; i++){
			int t = num[(i+n)%n] - num[(i-1+n)%n];
			if(t == -1) a++;
			else if(t == 1) b++;
			else if(t == n-1) c++;
			else if(t == -(n-1)) d++;
			else return false;
		}
		if((c == 1 && a == n-1) || (b == n-1 && d == 1)) return true;
		else return false;
	}
} nodes[maxm];

void print(int idx){
	vector<int> v;;
	while(idx != -1){
		v.push_back(idx);
		idx = nodes[idx].pre;
	}
	for(int i = (int)v.size()-1; i >= 0; i--){
		for(int j = 0; j < n; j++){
			printf("%d ", nodes[v[i]].num[j]);
		}
		printf("\n");
	}
}

int main(){
#ifdef LOCAL
	freopen("UVa.1620.helper.in", "r", stdin);
	freopen("UVa.1620.helper.out", "w", stdout);
#endif
	while(scanf("%d%d", &n, &m) == 2 && n){
		while(m--){
			set<int> s;
			
			node first;
			first.d = 0; first.pre = -1;
			for(int i = 0; i < n; i++) scanf("%d", &first.num[i]);
			nodes[0] = first;
			
			int hh = first.num[0];
			for(int i = 1; i < n; i++) hh = 10 * hh + nodes[0].num[i];
			s.insert(hh);

			bool f = false;
			int h = 0, t = 1;
			while(h < t){
				node tmp = nodes[h];
				if(tmp.check()){
					print(h);
					f = true;
					break;
				}
				for(int i = 0; i < n; i++){
					node ne = tmp;
					swap(ne.num[i], ne.num[(i+3+n)%n]);
					swap(ne.num[(i+1+n)%n], ne.num[(i+2+n)%n]);
					ne.d = tmp.d+1;
					ne.pre = h;
					
					int hh = ne.num[0];
					for(int i = 1; i < n; i++) hh = 10 * hh + ne.num[i];
					if(!s.count(hh) && ne.d <= maxd) {
						nodes[t++] = ne;
						s.insert(hh);
					}
				}
				h++;
			}
			if(f) printf("possible\n\n");
			else printf("impossible in %d steps\n\n", maxd);
		}
	}
	return 0;
}

