#include<cstdio>
#include<iostream>
#include<set>
#include<cstring>
using namespace std;

set<string> s;
set<string>::iterator it;

int main(){
#ifdef LOCAL
	freopen("UVA.10391.in", "r", stdin);
	freopen("UVA.10391.out", "w", stdout);
#endif
	string a;
	while(cin >> a) s.insert(a);
	for(it = s.begin(); it != s.end(); it++){
		int len = (*it).size();
		for(int i = 0; i < len; i++){
			if(s.count((*it).substr(0, i + 1)) && s.count((*it).substr(i + 1))){
				printf("%s\n", (*it).c_str());
				break;
			}
		}
	}
	return 0;
}

