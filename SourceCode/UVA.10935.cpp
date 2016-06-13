#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 50 + 5;
int a[maxn];

int main(){
#ifdef LOCAL
	freopen("UVA.10935.in", "r", stdin);
	freopen("UVA.10935.out", "w", stdout);
#endif
	int n;
	while(scanf("%d", &n) == 1 && n){
		memset(a, 0, sizeof(int) * maxn);
		if(n == 1){
			printf("Discarded cards:\nRemaining card: 1\n");
			continue;
		}
		printf("Discarded cards: 1");
		int c = 1, idx = 0; a[0] = 1;
		while(c < n - 1){
			int num = 2;
			while(num){
				idx = (idx + 1) % n;
				if(a[idx] == 0) num--;
			}
			printf(", %d", idx + 1);
			a[idx] = 1;
			c++;
		}
		printf("\nRemaining card: ");
		for(;;){
			idx = (idx + 1) % n;
			if(a[idx] == 0) {
				printf("%d\n", idx + 1);
				break;
			}
		}
	}
	return 0;
}

