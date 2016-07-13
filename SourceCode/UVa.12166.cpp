#include<iostream>
#include<cstdio>
#include<cctype>
#include<climits>
#include<map>
#include<algorithm>
using namespace std;

int idx;
map<long long, int> m;
char s[1024000];

void dfs(int depth){
	if(isdigit(s[idx])){
		long long a = 0;
		while(isdigit(s[idx])){
			a = a * 10 + s[idx++] - '0';
		}
		m[a<<depth]++;
	}
	else{
		idx++; dfs(depth+1); //ignore [ go deeper for left subtree
		idx++; dfs(depth+1); //ignore , process right subtree
		idx++; 				 //ignore ]
	}
}

int main(){
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("UVa.12166.in", "r", stdin);
	freopen("UVa.12166.out", "w", stdout);
#endif
	int T;
	cin >> T;
	while(T--){
		idx = 0, m.clear();
		cin >> s;
		dfs(0);
		
		int mx = INT_MIN, sum = 0;
		for(auto it = m.begin(); it != m.end(); it++){
			sum += it->second; mx = max(mx, it->second);
		}
		cout << sum - mx << endl;
	}
	return 0;
}

