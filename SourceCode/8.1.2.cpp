#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 11;

int A[maxn+1] = {0, -2, 3, -5, 3, 5, 3, -10, 1, 16, 20, -30};
int S[maxn];

int main(){
	S[0] = 0; 
	int best = A[1], tot = 0;
	for(int i = 1; i <= maxn; i++) S[i] = S[i-1]+A[i];
	for(int i = 1; i <= maxn; i++)
		for(int j = i; j <= maxn; j++){
			best = max(best, S[j]-S[i-1]);
			tot++;
		}
	printf("%d %d", best, tot);
	return 0;
}

