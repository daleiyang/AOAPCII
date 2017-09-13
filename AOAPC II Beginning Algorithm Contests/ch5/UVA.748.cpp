#include<algorithm> //max
#include<cassert>	//assert
#include<cstdio>	//printf, sprintf
#include<cstring>	//strlen
#include<iostream>	//cin,cout
#include<string>	//string
#include<vector> 	//vector
#include<sstream>
using namespace std;

struct BigInteger{
	typedef unsigned long long LL;
	static const int BASE=100000000;
	static const int WIDTH=8;
	vector<int> s;

	BigInteger& clean(){
		while(!s.back() && s.size()>1)
			s.pop_back();
		return *this;
	}

	BigInteger(LL num=0){*this=num;}
	BigInteger(string s){*this=s;}
	BigInteger & operator = (LL num){
		s.clear();
		do{
			s.push_back(num%BASE);
			num/=BASE;
		}while(num>0);
		return *this;
	}
	BigInteger & operator = (const string & str){
		s.clear();
		int x, len=(str.length()-1)/WIDTH + 1;
		for(int i=0; i<len; i++){
			int end=str.length()-i*WIDTH;
			int start=max(0, end-WIDTH);
			sscanf(str.substr(start, end-start).c_str(), "%d", &x);
			s.push_back(x);
		}
		return (*this).clean();
	}
	BigInteger operator + (const BigInteger & b) const{
		BigInteger c; c.s.clear();
		for(unsigned int i=0,g=0;;i++){
			if(g==0 && i>=s.size() && i>=b.s.size()) break;
			int x=g;
			if(i<s.size()) x+=s[i];
			if(i<b.s.size()) x+=b.s[i];
			c.s.push_back(x%BASE);
			g=x/BASE;
		}
		return c;
	}
	BigInteger operator - (const BigInteger & b) const{
		assert(b<=*this);
		BigInteger c; c.s.clear();
		for(unsigned int i=0, g=0;; i++){
			if(g==0 && i>=s.size() && i>=b.s.size()) break;
			int x=s[i]+g;
			if(i<b.s.size()) x-=b.s[i];
			if(x<0){g=-1; x+=BASE;} else g=0;
			c.s.push_back(x);
		}
		return c.clean();
	}
	BigInteger operator * (const BigInteger & b) const{
		unsigned int i, j; LL g;
		vector<LL> v(s.size()+b.s.size(), 0);
		BigInteger c; c.s.clear();
		for(i=0; i<s.size();i++) for(j=0; j<b.s.size(); j++) v[i+j]+=LL(s[i])*b.s[j];
		for(i=0,g=0;;i++){
			if(g==0 && i>=v.size()) break;
			LL x=v[i]+g;
			c.s.push_back(x%BASE);
			g=x/BASE;
		}
		return c.clean();
	}
	BigInteger operator / (const BigInteger & b) const{
		assert(b>0);
		BigInteger c=*this;
		BigInteger m;
		for(int i=s.size()-1; i>=0; i--){
			m=m*BASE+s[i];
			c.s[i]=bsearch(b,m);
			m-=b*c.s[i];
		}
		return c.clean();
	}
	BigInteger operator % (const BigInteger & b) const{
		BigInteger c=*this;
		BigInteger m;
		for(int i=s.size()-1; i>=0; i--){
			m=m*BASE+s[i];
			c.s[i]=bsearch(b,m);
			m-=b*c.s[i];
		}
		return m;
	}
	int bsearch(const BigInteger & b, const BigInteger & m) const{
		int L=0, R=BASE-1, x;
		while(1){
			x=(L+R)>>1;
			if((b*x)<=m){if((b*(x+1))>m) return x; else L=x;}
			else R=x;
		}
	}
	BigInteger & operator += (const BigInteger & b){*this=*this+b; return *this;}
	BigInteger & operator -= (const BigInteger & b){*this=*this-b; return *this;}
	BigInteger & operator *=(const BigInteger & b){*this=*this*b; return *this;}
	BigInteger & operator /=(const BigInteger & b){*this=*this/b; return *this;}
	BigInteger & operator %= (const BigInteger & b){*this=*this%b; return *this;}	

	bool operator < (const BigInteger & b) const{
		if(s.size()!=b.s.size()) return s.size()<b.s.size();
		for(int i=s.size()-1; i>=0; i--){
			if(s[i]!=b.s[i]) return s[i]<b.s[i];
		}
		return false;
	}

	bool operator > (const BigInteger & b) const{return b<*this;}
	bool operator <= (const BigInteger & b) const{return !(b<*this);}
	bool operator >= (const BigInteger & b) const{return !(*this<b);}
	bool operator != (const BigInteger & b) const{return b<*this || *this<b;}
	bool operator == (const BigInteger & b) const{return !(b<*this)&&!(*this<b);}
};

ostream & operator << (ostream & out, const BigInteger & x){
	out<< x.s.back();
	for(int i=x.s.size()-2; i>=0; i--){
		char buf[20];
		sprintf(buf, "%08d", x.s[i]);
		for(unsigned int j=0; j<strlen(buf); j++) out<<buf[j];
	}
	return out;
}

istream & operator >>(istream & in, BigInteger & x){
	string s;
	if(!(in>>s)) return in;
	x=s;
	return in;
}

const char * c;
bool test(int j, int len){
	if(c[j]=='0'){
		bool f=false;
		for(int k=j+1; k<len; k++){
			if(c[k] != '0') f=true;
		}
		if(f) printf("%c", c[j]);
		else return false;
	}else{
		printf("%c", c[j]);
	}
	return true;
}

int main(){
#ifdef LOCAL
	freopen("UVA.748.in", "r", stdin);
	freopen("UVA.748.out", "w", stdout);
#endif
	char a[7]; int n;
	while(scanf("%s%d", a, &n)==2){
		int i, x;
		for(i=0; i<6; i++) {if(a[i]=='.') break;}
		if(i==6) {x=0;} else {x=(6-1-i)*n;} 
		
		string s;
		for(int j=0; j<6; j++){if(j!=i) s.push_back(a[j]);}
		
		BigInteger t=s;
		BigInteger r=1;
		for(int k=0; k<n; k++) r *= t;
		
		stringstream stream;
		stream<<r;
		string s2=stream.str();
		int len=s2.length();
		c=s2.c_str();

		if(x==0) {
			for(int j=0; j<len; j++) printf("%c", c[j]);
		}
		else if(x>=len) {
			printf(".");
			for(int j=0; j<x-len; j++) printf("0");
			for(int j=0; j<len; j++) {if(!test(j, len)) break;}
		}
		else if(x<len){
			for(int j=0; j<len-x; j++) printf("%c", c[j]);
			printf(".");
			for(int j=len-x; j<len; j++){if(!test(j, len)) break;}
		}
		printf("\n");
	}
	return 0;
}

