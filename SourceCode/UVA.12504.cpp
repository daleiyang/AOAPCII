#include<iostream>
#include<cstdio>
#include<sstream>
#include<string>
#include<map>
#include<vector>
#include<cctype>
#include<algorithm>
using namespace std;

typedef map<int, int> D;
D oldD, newD;
D::iterator it;
typedef unsigned int UI;
vector<string> L;
map<string, int> M;
vector<string> addN, miss, change;

int ID(const string & s){
	if(M.count(s)) return M[s];
	L.push_back(s);
	return M[s] = L.size() - 1;
}

void build(string & s, D & dic){
	for(UI i = 0; i < s.length(); i++){
		if(!isdigit(s[i])&& !isalpha(s[i])){s[i] = ' ';}
	}
	stringstream ss(s); string k, v;
	while(ss >> k >> v){dic[ID(k)] = ID(v);}
}

void print(vector<string> & v){
	for(UI i = 0; i < v.size(); i++){
		if(i > 0) {cout << ",";}
		cout << v[i];
	}
	cout << endl;
}

void printM(D & r){
	cout << endl << "From printM:"<<endl;
	for(it = r.begin(); it != r.end(); it++){
		cout << "Key:" << it->first << " Value:" << it->second <<endl;
	}
}

void printV(vector<string> & r){
	cout << endl << "From printV:"<<endl;
	for(unsigned int i = 0; i < r.size(); i++){
			cout << "Id:" << i << " Key:" << r[i] <<endl;
	}
}

int main(){
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("UVA.12504.in", "r", stdin);
	freopen("UVA.12504.out", "w", stdout);
#endif
	int T; string s;
	cin >> T; getline(cin, s);
	while(T--){
 		oldD.clear(); newD.clear(); L.clear();M.clear();
		addN.clear(); miss.clear(); change.clear();
		getline(cin, s);
		build(s, oldD);
		//printM(oldD);
		getline(cin, s);
		build(s, newD);
		//printM(newD);
		//printV(L);
		for(it = oldD.begin(); it != oldD.end(); it++){
			if(!newD.count(it->first)) {miss.push_back(L[it->first]);}
			if(newD.count(it->first) && it->second != newD[it->first]) {change.push_back(L[it->first]);}
		}
		//printV(miss);
		//printV(change);
		for(it = newD.begin(); it != newD.end(); it++){
			if(!oldD.count(it->first)) {addN.push_back(L[it->first]);}
		}
		//printV(addN);
		if(addN.size()==0 && miss.size()==0 && change.size()==0){
			cout << "No changes" << endl <<endl;
			continue;
		}
		if(addN.size()){
			sort(addN.begin(), addN.end());
			cout << "+";
			print(addN);
		}
		if(miss.size()){
			sort(miss.begin(), miss.end());
			cout << "-";
			print(miss);
		}
		if(change.size()){
			sort(change.begin(), change.end());
			cout << "*";
			print(change);
		}
		cout << endl;
	}
	return 0;
}

