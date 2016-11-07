#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;

const int maxn = 200000 + 5;
int a[maxn], f[maxn], g[maxn], n;

struct Candidate{
	int a, g;
	Candidate(int a, int g):a(a), g(g){}
	bool operator < (const Candidate & rhs) const{
		return a < rhs.a;
	}
};

set<Candidate> s;

int main(){
#ifdef LOCAL
	freopen("UVa.1471.in", "r", stdin);
	freopen("UVa.1471.out", "w", stdout);
#endif
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		for(int i = 0; i < n; i++) scanf("%d", &a[i]);
		if(n == 1) {printf("1\n"); continue;}

		// g[i] is the length of longest increasing continuous subsequence ending at i
		g[0] = 1;
		for(int i = 1; i < n; i++){
			if(a[i-1] < a[i]) g[i] = g[i-1]+1;
			else g[i] = 1;
		}
		
		// f[i] is the length of longest increasing continuous subsequence starting from i
		f[n-1] = 1;
		for(int i = n-2; i >= 0; i--){
			if(a[i] < a[i+1]) f[i] = f[i+1]+1;
			else f[i] = 1;
		}

		s.clear();
		s.insert(Candidate(a[0], g[0]));

		int ans = 1;
		//enumerate f
		for(int i = 1; i < n; i++){
			Candidate c(a[i], g[i]);
			set<Candidate>::iterator it = s.lower_bound(c);//first one that is >= c
			bool keep = true;
			if(it != s.begin()){
				Candidate last = *(--it); //(--it) points to the largest one that is < c
				int len = f[i] + last.g;
				ans = max(ans, len); //Because every  (f[i] +last.g) is a valid candidate, simplify logic here.
				if(c.g <= last.g) keep = false; // last.a < c.a, so, we only keep last.a and c.a is useless.
			}
			if(keep){
				//if c.a is already present in set and based on previous logic,  the value g in set is continuous increase.
				//line 58, so the old g must be < c.g.
				s.erase(c);
				s.insert(c);
				it = s.find(c);
				it++;
				//remove useless Candidate because of this new c.
				while( it != s.end() && it->a > c.a && it->g <= c.g) s.erase(it++); 
			}
		}	
		printf("%d\n", ans);
	}
	return 0;
}

