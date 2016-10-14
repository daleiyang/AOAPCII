#include<cstdio>
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

const int maxL = 30 + 5;
const int maxN = 1000 + 5;
char ans[maxL];
string x[maxN];

int main(){
		ios::sync_with_stdio(false);
#ifdef LOCAL
		freopen("UVa.1610.in", "r", stdin);
		freopen("UVa.1610.out", "w", stdout);
#endif
	int n;
	while(cin >> n && n){
		for(int i = 0; i < n; i++) cin >> x[i];
		sort(x, x+n);
		string s = x[(n>>1)-1], t = x[n>>1];
		int len = s.length(), i = 0;
		string ans = "";
		ans += "A";
		while(i < len){
			while(ans[i] < 'Z' && ans < s) ans[i]++;
			if(ans >= s && ans < t) break;
			ans[i] = s[i];
			ans += "A";
			i++;
		}
		cout << ans << endl;
	}
	return 0;
}

