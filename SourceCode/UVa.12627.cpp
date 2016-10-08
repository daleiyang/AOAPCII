#include<cstdio>
#include<iostream>
using namespace std;

typedef long long LL;
int K;

LL c(int k){
	return k == 0 ? 1 : c(k-1)*3;
}

LL f(int k, int i){
	if(i == 0) return 0;
	if(k == 0) return 1;

	int k2 = 1 << (k-1);
	if(i <= k2) return 2 * f(k-1, i);
	else return 2 * c(k-1) + f(k-1, i-k2);
}

LL g(int k, int i){
	if(i > (1 << K)) return 0;
	if(k == 0) return 1;

	int k2 = 1 << (k-1);
	if(i <= k2) return c(k-1) + 2* g(k-1, i);
	else return g(k-1, i-k2);
}

int main(){
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("UVa.12627.in", "r", stdin);
	freopen("UVa.12627.out", "w", stdout);
#endif
	int T;
	cin >> T;
	for(int i = 1; i <= T; i++){
		int A, B;
		cin >> K >> A >> B;
		//cout << "Case " << i << ": " << f(K, B) - f(K, A-1) << "\n";
		cout << "Case " << i << ": " <<  g(K, A) - g(K, B+1) << "\n";
	}
	return 0;
}

