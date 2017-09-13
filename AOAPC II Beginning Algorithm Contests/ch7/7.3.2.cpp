#include<cstdio>
using namespace std;

const int maxn = 10;
int B[maxn];
int p[3] = {4, 5, 3};

void print_subset(int n, int * b, int cur){
	if(cur == n){
		for(int i = 0 ; i < cur; i++){
			if(b[i]) printf("%d ", p[i]);
		}
		printf("\n");
		return ;
	}
	b[cur] = 1;
	print_subset(n, b, cur+1);
	b[cur] = 0;
	print_subset(n, b, cur+1);
}

int main(){
	print_subset(3, B, 0);
	return 0;
}

