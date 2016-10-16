#include<cstdio>
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

const int maxN = 1000 + 5;
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
		string a = x[(n/2)-1], b = x[n/2];
		string ans = "";
		for(unsigned int i = 0; i < a.size() && i < b.size(); i++){
			if(a[i] == b[i]){
				ans += a[i];
			}
			else{
				if(i == a.size()-1){
					ans += a[i];
					break;
				}
				else if(b[i] - a[i] > 1 || i != b.size()-1){
					ans += a[i]+1;
					break;
				}else{
					ans += a[i];
					for(unsigned int j = i+1; j < a.size(); j++){
						if(j == a.size()-1){
							ans += a[j];
							break;
						}
						else if(a[j] != 'Z'){
							ans += a[j]+1;
							break;
						}
						ans += 'Z';
					}
					break;
				}
			}
		}
		cout << ans << endl;
	}
	return 0;
}

