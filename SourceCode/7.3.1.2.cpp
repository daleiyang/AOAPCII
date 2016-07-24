#include<cstdio>
using namespace std;

const int maxn = 10;
int A[maxn],cnt = 0;
int p[] = {4, 5, 3};

void print_subset(int n, int * A, int cur){
	for(int i = 0; i < cur; i++) printf("%d ", p[A[i]]);
	printf("\n");
	int s = cur ? A[cur-1]+1 : 0;
	for(int i = s; i < n; i++){
		A[cur] = i;
		print_subset(n, A, cur+1);
	}
}

int main(){
	print_subset(3, A, 0);
	return 0;
}

