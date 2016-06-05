#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn = 100+10;
int A[maxn];
int main(){
	ios::sync_with_stdio(false);
	long long a, b;
	while(cin>>a>>b){
		cout<<min(a,b)<<"\n";
	}
	return 0;
}

