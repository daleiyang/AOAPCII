//http://blog.csdn.net/zyq522376829/article/details/46649767
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 5000 + 5;

int num[maxn], L[maxn][maxn], R[maxn][maxn], n;
/*
We have 1 <= p < q < r < s <= n  &&  Nq > Ns > Np > Nr.

We enumerate all possible q < r to minimize time complexity.

For every q < r  and Nq > Nr, we need to identify one "p" letting p < q < r and Np > Nr.  
In order to find a probable solution, we need find a Np which is the closest one to Nr. Make more room for Ns.
Array "L" is for this purpose.

For every q < r and Nq > Nr, we need to identify one "s" and q < r < s and Nq > Ns. 
In order to find a probable solution, we need find a Ns which is the closest one to Nq. Make more room for Np.
Array "R" is for this purpose.

After we identfy "p" and "s", we purning based on 1 <= p and s <= n. So 1 <= p < q < r < s <= n is meet.
we pruning based on Nq > Ns  and Ns > Np and Np > Nr. So Nq > Ns > Np > Nr. is meet.

For Nq < Ns < Np < Nr case, we only need to reverse the array "num" and apply the same logic.
Just write it down with sample data, we could make sure the logic is correct.
*/
bool solve(){
	//find a value which is larger than Ni and it's the smallest larger value than Ni among all Nj where j < i.
	//take this sample to understand: 10 30 60 40 20 50
	for(int i = 1; i <= n; i++){
		L[i][0] = 0; //init value for following steps
		for(int j = 1; j < i; j++){
			if(num[i] >= num[j]) L[i][j] = L[i][j-1];
			else if(!L[i][j-1] || num[j] < num[L[i][j-1]]) L[i][j] = j;
			else L[i][j] = L[i][j-1];
		}
	}

	//find a value which is smaller than Ni and it's the largest smaller value than Ni among all Nj where j > i.
	for(int i = 1; i <= n; i++){
		R[i][n+1] = 0; //init value for following steps
		for(int j = n; j > i; j--){
			if(num[i] <= num[j]) R[i][j] = R[i][j+1];
			else if(!R[i][j+1] || num[j] > num[R[i][j+1]] ) R[i][j] = j;
			else R[i][j] = R[i][j+1];
		}
	}

	//Enumerate all possible q < r.
	for(int q = 1; q <= n; q++){
		for(int r = q+1; r <= n; r++){
			//pruning
			if(num[q] <= num[r] || !R[q][r+1] || !L[r][q-1]) continue;
			int p = L[r][q-1], s = R[q][r+1];
			if(num[s] > num[p]) return true;
		}
	}
	return false;
}

int main(){
#ifdef LOCAL
		freopen("UVa.1618.in", "r", stdin);
		freopen("UVa.1618.out", "w", stdout);
#endif
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &num[i]);
		if(solve()) printf("YES\n");
		else{
			reverse(num+1, num+n+1);
			if(solve()) printf("YES\n");
			else printf("NO\n");
		}
	}
	return 0;
}

