#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

const int maxn = 30;
int n;
vector<int> pile[maxn];

void find_block(int a, int & p, unsigned int & h){
	for(p=0; p<n; p++)
		for(h=0; h<pile[p].size(); h++)
			if(pile[p][h]==a) return;
}

void clear_above(int p, int h){
	for(unsigned int i=h+1; i<pile[p].size(); i++){
		int b=pile[p][i];
		pile[b].push_back(b);
	}
	pile[p].resize(h+1);
}

void pile_onto(int p, int h, int p2){
	for(unsigned int i=h; i<pile[p].size(); i++)
		pile[p2].push_back(pile[p][i]);
	pile[p].resize(h);
}

void print(){
	for(int i=0; i<n; i++){
		printf("%d:", i);
		for(unsigned int j=0; j<pile[i].size(); j++)
			printf(" %d", pile[i][j]);
		printf("\n");
	}
}

int main(){
#ifdef LOCAL
	freopen("UVA.101.in", "r", stdin);
	freopen("UVA.101.out", "w", stdout);
#endif
	int a, b;
	string x, y;
	cin>>n;
	for(int i=0; i<n; i++) pile[i].push_back(i);
	while(cin>>x>>a>>y>>b){
		int pa, pb;
		unsigned int ha, hb;
		find_block(a, pa, ha);
		find_block(b, pb, hb);
		if(pa==pb) continue;
		if(x=="move") clear_above(pa, ha);
		if(y=="onto") clear_above(pb, hb);
		pile_onto(pa, ha, pb);
	}
	print();
	return 0;
}

