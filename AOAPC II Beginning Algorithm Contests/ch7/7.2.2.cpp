#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 10;
int s[maxn];

void print_permutation(int n, int * P, int * A, int cur){
	if(n == cur){
		for(int i = 0; i < n; i++){printf("%d ", A[i]);}
		printf("\n");
	}else{
		for(int i = 0; i < n; i++) if(!i || P[i] != P[i-1]){
			int c1 = 0, c2 = 0;
			for(int j = 0; j < cur; j++) if(A[j] == P[i]) c1++;
			for(int j = 0; j < n; j++) if(P[j] == P[i]) c2++;
			if(c1<c2){
				A[cur] = P[i];
				print_permutation(n, P, A, cur+1);
			}
		}
	}
}

int main(){
	int p[] = {1, 1, 1};
	sort(p, p+3);
	print_permutation(3, p, s, 0);
	return 0;
}

