#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 18 + 1;
int s[maxn];

int main(){
#ifdef LOCAL
	freopen("UVa.11059.in", "r", stdin);
	freopen("UVa.11059.out", "w", stdout);
#endif
	int n, kase = 0;
	while(scanf("%d", &n) == 1){
		for(int i = 0; i < n; i++){scanf("%d", &s[i]);}
		long long maxn = 0;
		for(int i = 0; i < n; i++){
			for(int j = i; j < n; j++){
				int a = i;
				long long sum = 1;
				while(a <= j){
					sum *= s[a++];
				}
				maxn = max(maxn, sum);
			}
		}
		cout << "Case #" << ++kase << ": The maximum product is " << maxn << ".\n\n" ;
	}
	return 0;
}

