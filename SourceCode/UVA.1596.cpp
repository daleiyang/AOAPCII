#include<cstdio>
#include<iostream>
#include<map>
#include<set>
#include<stack>
#include<string>
#include<utility>
using namespace std;

typedef pair<char, int> PII;
map<char, int> md;
map<PII, int> ma;

void defination(const string & s){
	int n = 0, idx = 2; char c;
	while((c = s.c_str()[idx++]) != ']'){
		n = n * 10 + c - '0';
	}
	md[s.c_str()[0]] = n;
}

bool validateIdx(char k, int idx){
	return idx + 1 <= md[k];
}

bool validateRef(char k, int idx){
	return ma.count(PII(k, idx)) > 0;
}

bool validateLExp(const string & s, char & a, int & n){
	stack<char> st; int idx = 0, si; n = 0;
	while((a = s.c_str()[idx++]) != ']'){
		if(isdigit(a)){n = n * 10 + a - '0';}
		else if (a != '['){st.push(a);}
	}
	while((si = st.size()) > 0){
		a = st.top();
		if(!validateIdx(a, n)) return false;
		if(si > 1){
			if(!validateRef(a, n)) return false;
			n = ma[PII(a, n)];
		}
		st.pop();
	}
	return true;
}

bool validateRExp(const string & s, int & n){
	stack<char> st; unsigned int idx = 0; char a; n = 0;
	while(idx < s.length() && (a = s.c_str()[idx++]) != ']'){
		if(isdigit(a)){n = n * 10 + a - '0';}
		else if (a != '['){st.push(a);}
	}
	while(st.size() > 0){
		a = st.top();
		if(!validateIdx(a, n)) return false;
		if(!validateRef(a, n)) return false;
		n = ma[PII(a, n)];
		st.pop();
	}
	return true;
}

int main(){
#ifdef LOCAL
	freopen("UVA.1596.in", "r", stdin);
	freopen("UVA.1596.out", "w", stdout);
#endif
	string s; size_t p; 
	while(cin >> s && s != "."){
		md.clear(); ma.clear();
		int n = 0; bool f = true;
		do{
			n++;
			p = s.find("=");
			if(p==string::npos) defination(s);
			else{
				char a; int idx, rv; 
				if(validateLExp(s.substr(0, p), a, idx) && validateRExp(s.substr(p + 1), rv)){
					ma[PII(a, idx)] = rv;
				}
				else{cout << n << endl; f = false; break;}
			}
		}while(cin >> s && s !=".");
		if(!f){while(cin >> s && s !=".");}
		if(f){cout << 0 << endl; }
	}
	return 0;
}

