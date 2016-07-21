#include<cstdio>
#include<cstring>
using namespace std;

const int S = 1234, E = 98765;
int f[10];

int main(){
#ifdef LOCAL
	freopen("UVa.725.in", "r", stdin);
	freopen("UVa.725.out", "w", stdout);
#endif
	int n, kase = 0;
	while(scanf("%d", &n) == 1 && n){
		if(kase++) {printf("\n");}
		bool flag = false;
		int a = S, b = a*n;
		for(; b <= E; a++, b=a*n){
			memset(f, 0, sizeof(f));
			if(a < 10000 || b < 10000) f[0] = 1;
			int i = a, j = b;
			while(i){
				f[i%10]++;
				i /= 10;
			}
			while(j){
				f[j%10]++;
				j /= 10;
			}
			int k = 0;
			for(int i = 0; i < 10; i++){
				if(f[i] == 1) k++;
			}
			if(k == 10){
				printf("%05d / %05d = %d\n", b, a, n);
				flag = true;
			}
		 }
		 if(!flag) {
		 	printf("There are no solutions for %d.\n", n);
		 }
	}
	return 0;
}

