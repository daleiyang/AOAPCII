#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<sstream>
#include<vector>
#include<map>
#include<set>
#include<algorithm>
using namespace std;

const int maxn = 10000;

int cnt = 0;
map<string, int> mapping;
string commands[maxn];

vector<int> depend[maxn], depend2[maxn];
int status[maxn]; //0 for not installed, 1 for explicitly installed, 2 for implicitly installed
vector<int> installed;

int ID(string s){
	if(!mapping.count(s)){
		commands[cnt] = s;
		mapping[s] = cnt++;
	}
	return mapping[s];
}

void install(int id, bool toplevel){
	for(unsigned int i = 0; i < depend[id].size(); i++){
			if(status[depend[id][i]] == 0){
				install(depend[id][i], false);
			}
	}
	status[id] = toplevel ? 1 : 2;
	cout << "   Installing " << commands[id] << endl;
	installed.push_back(id);
}

bool needed(int id){
	for(unsigned int i = 0; i < depend2[id].size(); i++){
		if(status[depend2[id][i]]) return true;
	}
	return false;
}

void remove(int id, bool toplevel){
	if(!needed(id) && ((status[id] == 1 && toplevel) || (status[id] == 2 && !toplevel))) {
		status[id] = 0;
		cout << "   Removing " << commands[id] << endl;
		installed.erase(remove(installed.begin(), installed.end(), id), installed.end());
	}
	for(unsigned int i = 0; i < depend[id].size(); i++){
		remove(depend[id][i], false);
	}
}

void list(){
	for(unsigned int i = 0; i < installed.size(); i++){
		cout << "   " << commands[installed[i]] << endl;
 	}
}

int main(){
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("UVa.506.in", "r", stdin);
	freopen("UVa.506.out", "w", stdout);
#endif
	string s, t, t2;
	memset(status, 0, sizeof(status));
	while(getline(cin, s)){
		cout << s <<endl;
		stringstream ss(s);
		ss >> t;
		if(t[0] == 'E') break;
		if(t[0] == 'L') list();
		else{
			ss >> t2;
			int ida = ID(t2);
			if(t[0] == 'D'){
				while(ss >> t2){
					int idb = ID(t2);
					depend[ida].push_back(idb);
					depend2[idb].push_back(ida);
				}
			}
			else if(t[0] == 'I'){
				if(status[ida] != 0){cout << "   " << t2 << " is already installed.\n"; continue;}
				install(ida, true);
			}else if(t[0] == 'R'){
				if(!status[ida]){cout << "   " << t2 << " is not installed.\n";}
				else if(needed(ida)){cout << "   " << t2 << " is still needed.\n";}
				else remove(ida, true);
			}
		}
	}
	return 0;
}

