#include<cstdio>
#include<iostream>
#include<string>
#include<set>
#include<sstream>
using namespace std;

set<string> dict;

int main(){
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("UVA.10815.in", "r", stdin);
	freopen("UVA.10815.out", "w", stdout);
#endif
	string s, buf;
	while(cin>>s){
		for(unsigned int i=0; i<s.length(); i++)
			if(isalpha(s[i])) s[i]=tolower(s[i]);
			else s[i]=' ';
		stringstream ss(s);
		while(ss>>buf) dict.insert(buf);
	}
	for(set<string>::iterator it = dict.begin(); it != dict.end(); ++it)
		cout<<*it<<"\n";
	return  0;
}

