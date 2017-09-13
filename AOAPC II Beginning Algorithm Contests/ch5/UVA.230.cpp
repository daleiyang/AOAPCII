#include<cstdio>
#include<utility>
#include<cstring>
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<map>
#include<utility>
using namespace std;

struct Book{
	string title;
	string author;
	int status; /* 1 = inlab; 2 = borrow; 3 = return */
}; 
vector<Book> v;
map<string, int> m;
bool comp(const Book & b1, const Book & b2){
	return (b1.author < b2.author) || (b1.author == b2.author && b1.title < b2.title); 
}

int main(){
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("UVA.230.in", "r", stdin);
	freopen("UVA.230.out", "w", stdout);
#endif
	string s, op; int p, p1, p2, idx, size;
	while(getline(cin, s) && s != "END"){  /*  for some reason, i need "END\r" in my local envrionment. It must be  "END" to get a AC.*/
		p = s.find_last_of("\"");
		Book b;
		b.title = s.substr(0, p + 1);
		b.author = s.substr(p + 5);
		b.status = 1;
		v.push_back(b);
	}
	sort(v.begin(), v.end(), comp);
	int n = 0;
	for(unsigned int i = 0; i < v.size(); i++){
		m.insert(pair<string, int>(v[i].title, n++));
	}
	while(cin >> op && op != "END"){
		if(op == "BORROW" || op == "RETURN"){
			getline(cin, s);
			p1 = s.find("\"");
			p2 = s.find_last_of("\"");
			idx = m[s.substr(p1, p2-p1+1)];
			op == "BORROW" ? v[idx].status = 2 :v[idx].status = 3;
		}
		else if(op == "SHELVE"){
			size = v.size();
			for(int i = 0; i < size; i++){
				if(v[i].status == 3){
					int f = -1;
					for(int j = i-1; j >= 0; j--){
						if(v[j].status == 1) {f = j; break;}
					}
					if(f == -1) cout <<"Put "<<v[i].title<<" first"<<endl;
					else cout <<"Put "<<v[i].title<<" after "<< v[f].title <<endl;
					v[i].status = 1;
				}
			}
			getline(cin, s);
			cout<<"END"<<endl;
		}
	}
	return 0;
}

