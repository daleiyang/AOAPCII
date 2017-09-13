#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 12;

int A[maxn] = {1, -2, 3, -5, 3, 5, 3, -10, 1, 16, 20, -30};

int maxnum(int * A, int x, int y){
	if(y-x == 1) return A[x];
	int m = x + (y-x)/2;
	int maxs = max(maxnum(A, x, m), maxnum(A, m, y));
	int v = 0, L = A[m-1];
	for(int i = m-1; i >= x; i--) L = max(L, v += A[i]);
	v = 0; int R = A[m];
	for(int i = m; i < y; i++) R = max(R, v += A[i]);
	return max(maxs, L+R);
}

int main(){
	printf("%d", maxnum(A, 0, 12));
	return 0;
}

