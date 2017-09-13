#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 11;

int A[maxn+1] = {0, -2, 3, -5, 3, 5, 3, -10, 1, 16, 20, -30};

int main(){
	int tot = 0;
	int best = A[1];
	for(int i = 1; i <= maxn; i++)
		for(int j = i; j <= maxn; j++){
			int sum = 0;
			for(int k = i; k <= j; k++){
				sum += A[k];
				tot++;
			}
			best = max(best, sum);
		}
	printf("%d %d", best, tot);
	return 0;
}

