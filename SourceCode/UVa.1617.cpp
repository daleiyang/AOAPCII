#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 5;

struct task{
	int L, R;
	task(int L = 0, int R = 0): L(L), R(R){}
	bool operator < (const task & rhs) const{
		return (L < rhs.L || (L == rhs.L && R < rhs.R));
	}
} t[maxn];

int main(){
#ifdef LOCAL
		freopen("UVa.1617.in", "r", stdin);
		freopen("UVa.1617.out", "w", stdout);
#endif
	int n, m;
	scanf("%d", &n);
	while(n--){
		scanf("%d", &m);
		for(int i = 0; i < m; i++){
			scanf("%d%d", &t[i].L, &t[i].R);
		}
		sort(t, t+m);
		int L = -(1<<30), R= 1<<30, cnt = 0;	
		for(int i = 0; i < m; i++){
			/*
			The first possible range from is [t[1],L, t[1].R. The second possible range is 
			[t[1].L+1, t[1].R+1]. we need to modify this range based on t[2].L and t[2.R].
			So, the new possible range is L = max(t[1].L+1, t[2].L), R = min(t[1].R+1, t[2].R).
			By this way, in each step, if we choice one position in current range, we could always
			find a way to choice positions for previous task without gap. This is the key for this sliding windows.
			*/
			L = max(L+1, t[i].L);
			R = min(R+1, t[i].R);
			if(L>=R){
				cnt++;
				L = t[i].L;
				R = t[i].R;
			}
		}
		printf("%d\n", cnt);
	}
	return 0;
}

