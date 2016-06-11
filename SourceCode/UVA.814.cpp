#include<iostream>
#include<string>
#include<map>
#include<set>
#include<vector>
#include<algorithm>
#include<cstdio>
using namespace std;

void parse_address(const string & s, string & user, string & mta){
	int k = s.find('@');
	user = s.substr(0, k);
	mta= s.substr(k + 1);
}

int main(){
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("UVA.814.in", "r", stdin);
	freopen("UVA.814.out", "w", stdout);
#endif
	string s, t;
	int k;
	map<string, set<string> > m;
	while(cin >> s && s !="*"){
		cin >> s >> k;
		set<string> ul;
		while(k--){
			cin >> t;
			if(!ul.count(t)) ul.insert(t);
		}
		if(!m.count(s)) m[s] = ul;
	}
	
	while(cin >> s && s != "*"){
		string sender, smta;
		parse_address(s, sender, smta);
		
		set<string> s1;
		vector<string> mta;
		map<string, vector<string> > m1;
		
		while(cin >> t && t != "*"){
			string receiver, rmta;
			parse_address(t, receiver, rmta);
			if(!s1.count(rmta)) {
				s1.insert(rmta);
				mta.push_back(rmta);
			}
			if(!m1.count(rmta)){
				m1[rmta] = vector<string>();
				m1[rmta].push_back(receiver);
			}
			else{
				vector<string>::iterator r = find(m1[rmta].begin(), m1[rmta].end(), receiver);
     			if(r == m1[rmta].end()) m1[rmta].push_back(receiver);
			}
		}
		getline(cin, t);
		string data;
		while(getline(cin, t) && t[0] != '*') data += "     " + t + "\n";

		for(unsigned int i = 0; i < mta.size(); i++){
			string mta2 = mta[i];
			vector<string> users = m1[mta2];
			cout << "Connection between "<<smta<<" and "<<mta2<<"\n";
			cout << "     HELO "<<smta<<"\n"<<"     250"<<"\n";
			cout << "     MAIL FROM:<"<<s<<">\n"<<"     250"<<"\n";
			bool needsend = false;
			for(unsigned int j = 0; j < users.size(); j++){
				cout << "     RCPT TO:<"<<users[j]<<"@"<<mta2<<">\n";
				if(!m[mta2].count(users[j])) cout <<"     550"<<"\n";
				else{
					cout <<"     250"<<"\n";
					needsend = true;
				}
			}
			if(needsend){
				cout <<"     DATA"<<"\n"<<"     354"<<"\n";
				cout <<data<<"     .\n"<<"     250\n";
			}
			cout <<"     QUIT"<<"\n"<<"     221"<<"\n";
		}
	}
	return 0;
}

