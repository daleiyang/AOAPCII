#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 11;

int A[maxn+1] = {0, -2, 3, -5, 3, 5, 3, -10, 1, 16, 20, -30};
int S[maxn];

int main(){
	S[0] = 0; 
	int maxnum = A[1], minnum = A[1];
	for(int i = 1; i <= maxn; i++) {
		S[i] = S[i-1]+A[i];
		maxnum = max(maxnum, S[i]);
		minnum = min(minnum, S[i]);
	}
	printf("%d", maxnum - minnum);
	return 0;
}

