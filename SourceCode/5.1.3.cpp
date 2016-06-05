#include<cstdio>
#include<iostream>
#include<string>
#include<sstream>
#include<ctime>
using namespace std;

int main(){
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("5.1.3.in", "r", stdin);
	freopen("5.1.3.out", "w", stdout);
#endif
	string line;
	while(getline(cin, line)){
		int x;
		stringstream ss(line);
		while(ss>>x);
	}
	printf("Time used = %.5f\n", (double)clock()/CLOCKS_PER_SEC);
	return 0;
}

