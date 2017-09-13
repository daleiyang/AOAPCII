#include<cstdio>
#include<iostream>
#include<string>
#include<set>
using namespace std;
set<string> dict;
int main(){
#ifdef LOCAL
		freopen("UVA.10815.in", "r", stdin);
		freopen("UVA.10815.out", "w", stdout);
#endif
	string s;
	char c;
	while((c=getchar()) != EOF){
		if(!isalpha(c)){
			if(s.size()){dict.insert(s); s.erase();}
		}
		else s.push_back(tolower(c));
	}
	for(set<string>::iterator it = dict.begin(); it != dict.end(); ++it)
		cout<<*it<<"\n";
	return  0;
}

