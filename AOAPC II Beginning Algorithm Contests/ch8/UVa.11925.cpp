#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 300 + 5;
int a[maxn];
int h[2*maxn*maxn];

int main(){
#ifdef LOCAL
		freopen("UVa.11925.in", "r", stdin);
		freopen("UVa.11925.out", "w", stdout);
#endif
	int n;
	while(scanf("%d", &n) == 1 && n){
		for(int i = 0; i < n; i++) scanf("%d", &a[i]);
		if(n == 1) {printf("\n"); continue;}
		
		int sidx = 0;// start from index 0 VS n-1. Will be changed when swap happens.
		int cnt = 0; //counter to identify if it;s in order.
		int idx = 0; //start from index 0 VS n-1.
		int hn = 0; //history steps
		while(1){
			int nidx = (idx+n-1)%n; //0->3; 3->2; 2->1; 1->0
			if(a[idx] > a[nidx]) cnt++;
			else if((a[idx] < a[nidx]) && (a[idx] == 1 && a[nidx] == n)) cnt++;
			else if((a[idx] < a[nidx]) && !(a[idx] == 1 && a[nidx] == n)){
				cnt++;
				for(int i = 0; i < cnt; i++) h[hn++] = 2;
				swap(a[idx], a[nidx]); h[hn++] = 1;
				sidx = nidx;
				cnt = 0;
			}
			idx = nidx;
			if(cnt == n){
				int t = 0;
				//if sidx = 1, then chech 1, 0, 3, 2 to find out how many "2" needed before we hit value 1.
				for(int i = 0; i > -n; i--){
					if(a[(sidx+i+n)%n] == 1) break;
					t++;
				}
				while(t--) h[hn++] = 2;
				for(int i = hn-1; i >=0 ; i--) printf("%d", h[i]);
				printf("\n");
				break;
			}
		}
	}
	return 0;
}

