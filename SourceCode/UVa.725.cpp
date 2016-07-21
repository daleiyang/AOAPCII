#include<cstdio>
#include<cstring>
using namespace std;

const int S = 1234, E = 98765;
int f[10], y;

bool validate(int z){
	if(z > 99999) return false;
	if(z < 10000 && f[0]) return false;
	else if(z < 10000 && !f[0]) {f[0] = 1;}
	do{
		y = z % 10, z = z / 10;
		if(f[y]) return false;
		else f[y] = 1;
	}while(z);
	return true;
}

int main(){
#ifdef LOCAL
	freopen("UVa.725.in", "r", stdin);
	freopen("UVa.725.out", "w", stdout);
#endif
	int n,kase = 0;
	while(scanf("%d", &n) == 1 && n){
		if(kase++) {printf("\n");}
		bool flag = false;
		 for(int i = S; i <= E; i++){
			memset(f, 0, sizeof(f));
			if(!validate(i)) continue;
			int j = i * n;
			if(!validate(j)) continue;
			printf("%05d / %05d = %d\n", j, i, n);
			flag = true;
		 }
		 if(!flag) {
		 	printf("There are no solutions for %d.\n", n);
		 }
	}
	return 0;
}

