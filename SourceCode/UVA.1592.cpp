#include<iostream>
#include<algorithm>
#include<sstream>
#include<cstdio>
#include<string>
#include<map>
using namespace std;

typedef pair<int,int> PII;
const int maxrow = 10000 + 5;
const int maxcol = 10 + 5;
int n, m, cnt, d[maxrow][maxcol];

map<string, int> id;
int ID(const string & s){
	if(!id.count(s)){
		id[s] = ++cnt;
	};
	return id[s];
}

void find(){
	for(int c1 = 0; c1 < m; c1++){
		for(int c2 = c1 + 1; c2 < m; c2++){
			map<PII, int> t;
			for(int i = 0; i < n; i++){
				PII p = make_pair(d[i][c1], d[i][c2]);
				if(t.count(p)){
					printf("NO\n");
					printf("%d %d\n", t[p]+1, i+1);
					printf("%d %d\n", c1+1, c2+1);
					return;
				}
				t[p] = i;
			}
		}
	}
	printf("YES\n");
}

int main(){
#ifdef LOCAL
	freopen("UVA.1592.in", "r", stdin);
	freopen("UVA.1592.out", "w", stdout);
#endif
	string s;
	while(getline(cin, s)){
		stringstream ss(s);
		if(!(ss >> n >> m)) break;
		cnt = 0;
		id.clear();
		for(int i = 0; i < n; i++){
			getline(cin, s);
			int lastpos = -1;
			for(int j = 0; j < m; j++){
				unsigned int p = s.find(',', lastpos + 1);
				if(p==string::npos) p = s.length();
				d[i][j] = ID(s.substr(lastpos + 1, p - lastpos - 1));
				lastpos = p;
			}
		}
		find();
	}
	return 0;
}

