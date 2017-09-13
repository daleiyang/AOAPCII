#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;

int main(){
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("UVa.11054.in", "r", stdin);
	freopen("UVa.11054.out", "w", stdout);
#endif
	int n;
	while(cin >> n && n){
		long long sum = 0, a, last = 0;
		for(int i = 0; i < n; i++){
			cin >> a;
			sum += abs(last);
			last += a;
		}
		cout << sum << endl;
	}
	return 0;
}

