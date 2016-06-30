#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 1000 + 5;

int sum[maxn];

void build(int pos){
	int v; cin >> v;
	if(v == -1) return;
	sum[pos] += v;
	build(pos-1); build(pos+1);
}

bool init(){
	memset(sum, 0 ,sizeof(sum));
	int v;
	cin >> v;
	if(v == -1){ return false;}
	int pos = maxn/2;
	sum[pos] = v;
	build(pos - 1); build(pos + 1);
	return true;
}

int main(){
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("UVa.699.in", "r", stdin);
	freopen("UVa.699.out", "w", stdout);
#endif
	int kase = 0;
	while(init()){
		int p = 0;
		while(sum[p] == 0 ) p++;
		cout << "Case " << ++kase << ":\n" << sum[p++];
		while(sum[p] != 0){cout << " " << sum[p++];}
		cout << "\n\n";
	}
	return 0;
}

