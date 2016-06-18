#include<iostream>
#include<sstream>
#include<cstdio>
#include<cctype>
#include<string>
#include<set>
#include<vector>
#include<set>
#include<map>
#include<algorithm>
#include<utility>
#include<ctime>
using namespace std;

vector<int> docid;
const int maxn = 100 + 5;
vector<string> docs[maxn];
typedef pair<int, int> PII;
typedef map<string, vector<PII> > MII;
MII index;
map<string, set<PII> > idxdul;
map<string, set<int> > keydoc;
int T, W;

void tokenize(string & s, int di, int li){
	for(unsigned int i = 0; i < s.length(); i++){
		if(isalpha(s[i])){s[i] = tolower(s[i]);}
		else {s[i] = ' ';}
	}
	stringstream ss(s);	
	string t; 
	while(ss >> t){
		PII p = PII(di, li);
		if(!index.count(t)){
			vector<PII> v;
			v.push_back(p);	
			index[t] = v;

			set<PII> s;
			s.insert(p);
			idxdul[t] = s;
		}
		else{
			if(!idxdul[t].count(p)){
				idxdul[t].insert(p);
				index[t].push_back(p);
			}
		}
	}
}

void processKeyDoc(){
	for(MII::iterator it = index.begin(); it != index.end(); it++){
		keydoc[it->first] = set<int>();
		int t = -1;
		for(unsigned int i = 0; i < it->second.size(); i++){
			if(it->second[i].first != t){
				t = it->second[i].first;
				keydoc[it->first].insert(t);
			}
		}
	}
}

void print(){
	for(int i = 0; i < T; i++){
		for(unsigned int j = 0; j < docs[i].size(); j++){
			cout << "Doc:" << i << " Line:" << j << " Content:" << docs[i][j] << endl;
		}
	} 
	cout<<endl;
	for(vector<int>::iterator it = docid.begin(); it != docid.end(); it++){
		cout << "DocId:" << *it << endl;
	}
	cout<<endl;
	for(MII::iterator it = index.begin(); it != index.end(); it++){
		cout << "Key:" << it->first << endl;
		for(vector<PII>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++){
			cout << "Doc id:" << (*it2).first << " Line id:" << (*it2).second << endl;
		}
	}
	cout<<endl;
	for(map<string, set<int> >::iterator it = keydoc.begin(); it != keydoc.end(); it++){
		cout << "Key:" << it->first << endl;
		for(set<int>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++){
			cout << "Doc id:" << (*it2) << endl;
		}
	}
}

void printV(vector<PII> & r){
	cout << endl << "From printV:"<<endl;
	for(unsigned int i = 0; i < r.size(); i++){
		cout<< r[i].first << " " << r[i].second << endl;
	}
}

void printS(set<int> & r){
	cout << endl << "From printS:"<<endl;
	for(set<int>::iterator it = r.begin(); it != r.end(); it++){
		cout<< *it << endl;
	}
}

int main(){
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("UVA.1597.in", "r", stdin);
	freopen("UVA.1597.out", "w", stdout);
#endif
	string s, t;
	cin >> T; getline(cin, s);
	for(int i = 0; i < T; i++){
		docid.push_back(i); 
		while(getline(cin, s) && s!= "**********"){
			docs[i].push_back(s);
			tokenize(s, i, docs[i].size()-1);
		}
	}
	processKeyDoc();
	//print();
	cin >> W; getline(cin, s);
	while(W--){
		getline(cin, s);
		stringstream ss(s);
		vector<string> v;
		while(ss >> t){v.push_back(t);}
		if(v.size() == 1){
			if(!index.count(v[0])) {cout<< "Sorry, I found nothing.\n==========\n"; continue;}
			vector<PII> r = index[v[0]]; int kase = 0, docf = -1;
			for(unsigned int i = 0; i < r.size(); i++){
				if(docf != r[i].first && kase++) cout << "----------\n";
				cout << docs[r[i].first][r[i].second] << endl;
				docf = r[i].first;
			}
		}
		if(v.size() == 2){
			vector<int> r;
			if(!keydoc.count(v[1])) {for(int i = 0; i < T; i++) r.push_back(i);}
			else if(keydoc[v[1]].size() == (unsigned int)T) {cout<< "Sorry, I found nothing.\n==========\n"; continue;}
			else { 
				for(int i = 0; i < T; i++){
					if(!keydoc[v[1]].count(i)) {
						r.push_back(i);
					}
				}
			}
			int kase = 0;
			for(unsigned int i = 0; i < r.size(); i++){
				if(kase++) cout << "----------\n";
				for(unsigned int j = 0; j < docs[r[i]].size(); j++){
					cout<< docs[r[i]][j] << endl;
				}
			}
		}
		if(v.size() == 3 && v[1] == "AND"){
			set<int> s;
			set<int> s1 = set<int>();
			set<int> s2 = set<int>();
			set<int>::iterator it;
			if(keydoc.count(v[0])) s1 = keydoc[v[0]];
			if(keydoc.count(v[2])) s2 = keydoc[v[2]];
			for(it = s1.begin(); it != s1.end(); it++){if(s2.count(*it) && !s.count(*it)) s.insert(*it);}
			for(it = s2.begin(); it != s2.end(); it++){if(s1.count(*it) && !s.count(*it)) s.insert(*it);}
			if(!s.size()){cout<< "Sorry, I found nothing.\n==========\n"; continue;}
			vector<PII> p1 = index[v[0]];
			vector<PII> p2 = index[v[2]];
			vector<PII> p(p1.size() + p2.size());
			vector<PII>::iterator vit;
			vit=std::set_union(p1.begin(), p1.end(), p2.begin(), p2.end(), p.begin());
			p.resize(vit - p.begin());
			int kase = 0, docf = -1;
			for(unsigned int i = 0; i < p.size(); i++){
				if(s.count(p[i].first)){
					if(docf != p[i].first && kase++) {cout << "----------\n";}
					cout << docs[p[i].first][p[i].second] << endl;
					docf = p[i].first;
				}
			}
		}
		if(v.size() == 3 && v[1] == "OR"){
			vector<PII> p1 = vector<PII>();
			vector<PII> p2 = vector<PII>();
			if(index.count(v[0])) p1 = index[v[0]];
			if(index.count(v[2])) p2 = index[v[2]];
			vector<PII> p(p1.size() + p2.size());
			if(!p.size()){cout<< "Sorry, I found nothing.\n==========\n"; continue;}
			vector<PII>::iterator vit;
			vit=std::set_union(p1.begin(), p1.end(), p2.begin(), p2.end(), p.begin());
			p.resize(vit - p.begin());
			int kase = 0, docf = -1;
			for(unsigned int i = 0; i < p.size(); i++){
				if(docf != p[i].first && kase++) {cout << "----------\n";}
				cout << docs[p[i].first][p[i].second] << endl;
				docf = p[i].first;
			}
		}
		cout<< "==========\n";
	}
	//printf("Time used:%.2f", (double)clock()/CLOCKS_PER_SEC);
	return 0;
}

