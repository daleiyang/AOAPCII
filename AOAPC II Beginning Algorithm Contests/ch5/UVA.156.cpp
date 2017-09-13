#include<cstdio>
#include<iostream>
#include<map>
#include<string>
#include<cctype>
#include<vector>
#include<algorithm>
using namespace std;
map<string,int> cnt;
vector<string> words;

string repr(const string & s){
	string ans=s;
	for(unsigned int i=0; i<s.length(); i++){
		ans[i]=tolower(ans[i]);
	}
	sort(ans.begin(), ans.end());
	return ans;
}

int main(){
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("UVA.156.in", "r", stdin);
	freopen("UVA.156.out", "w", stdout);
#endif
	string s;
	while(cin>>s){
		if(s[0]=='#') break;
		words.push_back(s);
		string r=repr(s);
		if(!cnt.count(r)) cnt[r]=0;
		cnt[r]++;
	}
	vector<string> ans;
	for(unsigned int i=0; i<words.size(); i++){
		if(cnt[repr(words[i])]==1) ans.push_back(words[i]);
	}
	sort(ans.begin(), ans.end());
	for(unsigned int i=0; i<ans.size(); i++){
		cout<<ans[i]<<"\n";
	}
	return 0;
}

