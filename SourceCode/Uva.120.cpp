#include<cstdio>
#include<iostream>
#include<sstream>
#include<algorithm>
using namespace std;

const int maxn = 30 + 5;

int n, a[maxn];

void flip(int p){
	for(int i = 0; i < p-i; i++){
		swap(a[i], a[p-i]);
	}
	cout << n-p << " ";
}

int main(){
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("UVa.120.in", "r", stdin);
	freopen("UVa.120.out", "w", stdout);
#endif
	string s;
	while(getline(cin, s)){
		cout << s << endl;;
		stringstream ss(s);
		n = 0;
		while(ss >> a[n]) n++;
		for(int i = n-1; i > 0; i--){
			int p = max_element(a, a+i+1)-a;
			if(p == i) continue;
			if(p > 0) flip(p);
			flip(i);
		}
		cout << "0" << endl;
	}
	return 0;
}

