#include<iostream>
#include<cstdio>
#include<string>
#include<sstream>
#include<vector>
#include<map>
#include<set>
using namespace std;

vector<string> commands;
vector<vector<int> > depend, depend2;
vector<int> status; //0 for not installed, 1 for explicitly installed, 2 for implicitly installed
map<string, int> mapping;
vector<int> orderV;
map<int, int> orderM;

int ID(string s){
	if(mapping.count(s)>0) {return mapping[s];}
	commands.push_back(s);
	int id = commands.size()-1;
	depend.push_back(vector<int>());
	depend2.push_back(vector<int>());
	status.push_back(0);
	mapping[s] = id;
	return id;
}

void OrderId(int i){
	if(orderM.count(i)>0 && orderV[orderM[i]] != -1) {return;}
	orderV.push_back(i);
	int id = orderV.size()-1;
	orderM[i] = id;
}

void installDep(int id, int step){
	for(unsigned int i = 0; i < depend[id].size(); i++){
			if(status[depend[id][i]] == 0){
				installDep(depend[id][i], step+1);
			}
	}
	status[id] = step == 1?1:2;
	cout << "   Installing " << commands[id] << endl;
	OrderId(id);
}

void removeDep(int id, int step){
	bool flag = true;
	for(unsigned int i = 0; i < depend2[id].size(); i++){
		if(status[depend2[id][i]] != 0) flag = false;
	}
	if(flag){
		if((status[id] == 1 && step == 1) || (status[id] == 2 && step > 1)) {
				status[id] = 0;
				cout << "   Removing " << commands[id] << endl;
				orderV[orderM[id]] = -1;
		}
		for(unsigned int i = 0; i < depend[id].size(); i++){
			removeDep(depend[id][i], step+1);
		}
	}
	else if(!flag && step == 1){
		cout << "   " << commands[id] << " is still needed.\n";
	}
}

void list(){
	for(unsigned int i = 0; i < orderV.size(); i++){
		if(orderV[i] != -1 && status[orderV[i]] != 0) cout << "   " << commands[orderV[i]] << endl;
 	}
}

int main(){
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("UVa.506.in", "r", stdin);
	freopen("UVa.506.out", "w", stdout);
#endif
	string s, t;
	while(getline(cin, s)){
		cout << s <<endl;
		stringstream ss(s);
		ss >> t;
		if(t == "END") break;
		if(t == "LIST") {list();}
		else if(t == "DEPEND"){
			ss >> t;
			int ida = ID(t);
			while(ss >> t){
				int idb = ID(t);
				depend[ida].push_back(idb);
				depend2[idb].push_back(ida);
			}
		}
		else if(t == "INSTALL"){
			ss >> t;
			int id = ID(t);
			if(status[id] != 0){cout << "   " << t << " is already installed.\n"; continue;}
			installDep(id, 1);
		}else if(t == "REMOVE"){
			ss >> t;
			int id  = ID(t);
			if(status[id] == 0){cout << "   " << t << " is not installed.\n"; continue;}
			removeDep(id, 1);
		}
	}
	return 0;
}

