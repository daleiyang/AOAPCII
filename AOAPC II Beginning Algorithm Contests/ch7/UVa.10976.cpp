#include<cstdio>
using namespace std;

const int maxn = 20000;
int ax[maxn], ay[maxn], y;

int main(){
#ifdef LOCAL
	freopen("UVa.10976.in", "r", stdin);
	freopen("UVa.10976.out", "w", stdout);
#endif
	int k;
	while(scanf("%d", &k)== 1){
		int cnt = 0;
		for(y = k+1; y <= 2*k; y++){
			if(((k*y)%(y-k)) == 0){
				ax[cnt] = (k*y)/(y-k);
				ay[cnt] = y;
				cnt++;
			}
		}
		printf("%d\n", cnt);
		for(int i = 0; i < cnt; i++){
			printf("1/%d = 1/%d + 1/%d\n", k, ax[i], ay[i]);
		}
	}
	return 0;
}

