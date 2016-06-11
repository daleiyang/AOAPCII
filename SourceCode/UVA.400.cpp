#include<iostream>
#include<string>
#include<algorithm>
#include<cstdio>
using namespace std;

const int maxcol = 60;
const int maxn = 100;
string filenames[maxn];

void print(const string & s, int len, char extra){
	cout<<s;
	for(unsigned int i=0; i<len-s.length(); i++){cout<<extra;}
}

int main(){
#ifdef LOCAL
	freopen("UVA.400.in", "r", stdin);
	freopen("UVA.400.out", "w", stdout);
#endif
	int n;
	while(cin>>n){
		int M=0;
		for(int i=0; i<n; i++){
			cin>>filenames[i];
			M= max(M, (int)filenames[i].length());
		}
		sort(filenames, filenames+n);
		int c=(60+2)/(M+2);
		int r=(n-1)/c + 1; 
		print("", 60, '-');
		cout<<"\n"; 
		int idx;
		for(int i=0; i<r; i++){
			for(int j=0; j<c; j++){
				idx=j*r+i;
				if(idx<n) print(filenames[idx], j==c-1?M:M+2, ' ');
			}
			cout<<'\n';
		}
	}
	return 0;
}

