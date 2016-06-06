#include<cstdio>
#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<stack>
#include<string>
#include<algorithm>
using namespace std;

#define ALL(x) x.begin(), x.end()
#define INS(x) inserter(x, x.begin())

typedef set<int> Set;
map<Set,int> IDcache;
vector<Set> Setcache;
stack<int> s;

int ID(Set s){
	if(IDcache.count(s)) return IDcache[s];
	Setcache.push_back(s);
	return IDcache[s]=Setcache.size()-1;
}

int main(){
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("UVA.12096.in", "r", stdin);
	freopen("UVA.12096.out", "w", stdout);
#endif
	int kase;
	cin>>kase;
	while(kase--){
		int n;
		cin>>n;
		while(n--){
			string op;
			cin>>op;
			if(op[0]=='P'){s.push(ID(Set()));}
			else if(op[0]=='D'){s.push(s.top());}
			else{
				Set x1=Setcache[s.top()]; s.pop();
				Set x2=Setcache[s.top()]; s.pop();
				Set x;
				if(op[0]=='U'){set_union(ALL(x1), ALL(x2), INS(x));}
				if(op[0]=='I'){set_intersection(ALL(x1), ALL(x2), INS(x));}
				if(op[0]=='A'){x=x2; x.insert(ID(x1));}
				s.push(ID(x));
			}
			cout<<Setcache[s.top()].size()<<endl;
		}
		cout<<"***"<<endl;
	}
	return 0;
}

