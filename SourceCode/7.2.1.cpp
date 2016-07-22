#include<cstdio>
using namespace std;

const int maxn = 10;
int s[maxn];

void print_permutation(int n, int * A, int cur){
	if(n ==  cur){
		for(int i = 0; i < n; i++){
			printf("%d ", A[i]);
		}
		printf("\n");
	}
	else{
		for(int i = 1; i <= n; i++){
			int k = 1;
			for(int j = 0; j < cur; j++){
				if(A[j] == i) {k = 0; break;}
			}
			if(k){
				A[cur] = i;
				print_permutation(n, A, cur+1);
			}
		}
	}
}	

int main(){
	print_permutation(3, s, 0);
	return 0;
}

