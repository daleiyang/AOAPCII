#include<iostream>
#include<cstring>
#include<sstream>
#include<cstdio>
#include<queue>
#include<vector>
using namespace std;

int q[6]; // q[0] for quantum; q[1] for assignment; q[2] for print; q[3] for lock; q[4] for unlock; q[5] for end;
queue<int> d;
deque<int> r;
vector<vector<string> > ps; 
int psidx[1000]; //command index for each program
int val[26];
bool flock;

int main(){
#ifdef LOCAL
		freopen("UVA.210.in", "r", stdin);
		freopen("UVA.210.out", "w", stdout);
#endif
	int T, n, kase = 0; string s;
	scanf("%d", &T);
	while(T--){
		if(kase++) {puts("");}
		//clean
		queue<int> e1; swap(d, e1);
		deque<int> e2; swap(r, e2);
		ps.clear();
		memset(val, 0, sizeof(val)); 
		memset(psidx, 0, sizeof(psidx));
		flock = false;
		//input
		scanf("%d%d%d%d%d%d%d", &n, &q[1], &q[2], &q[3], &q[4], &q[5], &q[0]); getline(cin, s);
		for(int i = 0; i < n; i++){
			vector<string> p;
			while(getline(cin, s) && s != "end"){p.push_back(s);}
			p.push_back(s); //for end command
			ps.push_back(p);
			psidx[i] = 0; //init command index to 0 for each program
		}
		for(unsigned int i = 0; i < ps.size(); i++){r.push_back(i);}
		//process
		string s2; int x;
		while(!r.empty()){
			int pi = r.front(), qu = q[0]; bool blocked = false; bool ended = false;
			while(qu > 0){ //within quantum in this run.
				stringstream ss(ps[pi][psidx[pi]]);
				ss >> s;
				if(s.length() == 1){
					ss >> s2 >> x;
					val[s.c_str()[0]-'a'] = x;
					qu -= q[1];
					psidx[pi]++;
					continue;
				}
				if(s == "print"){
					ss >> s2;
					printf("%d: %d\n", pi+1, val[s2.c_str()[0]-'a']);
					qu -= q[2];
					psidx[pi]++;
					continue;
				}
				if(s == "end"){
					r.pop_front();
					ended = true;
					break;
				}
				if(s == "lock"){
					if(flock){
						r.pop_front();
						d.push(pi); 
						blocked = true;
						break;
					}
					else{
						flock = true;
						qu -= q[3];
						psidx[pi]++;
						continue;
					}
				}
				if(s == "unlock"){
					if(!d.empty()){
						r.pop_front();
						r.push_front(d.front());
						r.push_front(pi);
						d.pop();
					}
					qu -= q[4];
					psidx[pi]++;
					flock = false;
					continue;
				}
			}
			if(!blocked && !ended){
				r.pop_front();
				r.push_back(pi);
			}
		}
	}
	return 0;
}

