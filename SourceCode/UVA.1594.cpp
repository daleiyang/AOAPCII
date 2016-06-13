#include<iostream>
#include<cstdio>
#include<map>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;

typedef vector<int> VC;

bool isZero(VC & a){
	for(unsigned int i = 0; i< a.size(); i++){ 
		if(a[i] != 0) return false; 
	}
	return true;
}

void getKey(VC & a, string & s){
	char t[10];
	sprintf(t, "%d", a[0]);
	s.append(t);
	for(unsigned int i = 1; i < a.size(); i++){
		s.append("-");
		sprintf(t, "%d", a[i]);
		s.append(t);
	}
}

int main(){
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("UVA.1594.in", "r", stdin);
	freopen("UVA.1594.out", "w", stdout);
#endif
	int n, k;
	scanf("%d", &n);
	while(n--){
		scanf("%d", &k);
		VC a; int t;
		while(k--) {scanf("%d", &t); a.push_back(t);}
		unsigned int size = a.size();
		set<string> s; 
		for(int j = 0; j < 1000; j++){
			/*
			if(isZero(a)) {printf("ZERO\n"); break;}
			string k;
			getKey(a, k);
			if(s.count(k)) {printf("LOOP\n"); break;}
			else {s.insert(k);}
			*/
			int c = a[0];
			for(unsigned int i = 0; i < size; i++){
				if(i == size - 1) a[size-1] = abs(a[size-1]-c);
				else a[i] = abs(a[i]-a[i+1]);
			}
		}
		if(isZero(a)) printf("ZERO\n");
		else printf("LOOP\n");
	}
	return 0;
}

