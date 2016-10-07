#include<cstdio>
#include<queue>
using namespace std;

const int maxn = 100000 + 5;

char s[maxn];
int sum[maxn];
deque<int> q;

int compare_avg(int x1, int x2, int x3, int x4){
	return (sum[x2]-sum[x1-1])*(x4-(x3-1)) - (sum[x4]-sum[x3-1])*(x2-(x1-1));
}

int main(){
#ifdef LOCAL
	freopen("UVa.1451.in", "r", stdin);
	freopen("UVa.1451.out", "w", stdout);
#endif
	int T;
	scanf("%d", &T);
	while(T--){
		int n, L;
		scanf("%d%d%s", &n, &L, s+1);
		
		sum[0] = 0;
		for(int i = 1; i <= n; i++) sum[i] = sum[i-1]+s[i]-'0';
		
		q.clear();
		int ansL = 1, ansR = L;
		for(int t = L; t <= n; t++){
			while(q.size()>1){
				int b = q[q.size()-1];
				int b2 = q[q.size()-2];
				if(compare_avg(b, t-L, b2, t-L) < 0){
					q.pop_back();
				}
				else break;
			}
			q.push_back(t-L+1);
			while(q.size()>1){
				if(compare_avg(q[0], t, q[1], t) <= 0){
					q.pop_front();
				}
				else break;
			}
			int c = compare_avg(q[0], t, ansL, ansR);
			if(c > 0 || (c == 0 && t-q[0] < ansR- ansL)){
				ansL = q[0];
				ansR = t;
			}
		}
		printf("%d %d\n", ansL, ansR);
	}
	return 0;
}

