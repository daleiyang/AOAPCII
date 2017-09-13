#include<cstdio>
using namespace std;

int main(){
#ifdef LOCAL
	freopen("UVa.679.in", "r", stdin);
	freopen("UVa.679.out", "w", stdout);
#endif
	int T, D, I;
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &D, &I);
		int k = 1;
		for(int i = 0; i < D - 1; i++){
			if(I%2){k *= 2; I = I/2+1;}
			else{k = k*2+1; I /=2;}
		}
		printf("%d\n", k);
	}
	return 0;
}

