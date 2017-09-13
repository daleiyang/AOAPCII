#include<cstdio>
#include<iostream>
#include<sstream>
#include<map>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

map<int, vector<int> > tasks;
map<int, int> tasktime;
struct P{
	int start, end;
	P(int start = 0, int end = 0):start(start), end(end){}
};
map<int, P> person;
struct PersonPri{
	int pid, pri;
	PersonPri(int pid = 0, int pri = 0):pid(pid), pri(pri) {}
	bool operator < (const PersonPri & b) const{
		return (person[b.pid].end < person[pid].end) 
				|| ((person[b.pid].end == person[pid].end) && ((b.pri < pri) 
					||( (b.pri == pri) &&((person[b.pid].start < person[pid].start) 
						|| ((person[b.pid].start == person[pid].start) && (b.pid < pid))
				))));
	}
};
typedef priority_queue<PersonPri> pp; //input is pid
map<int, pp> pq; //key is tid

int main(){
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("UVA.822.in", "r", stdin);
	freopen("UVA.822.out", "w", stdout);
#endif
	int n, m, kase = 1; string s;
	while(cin >> n && n){
		tasks.clear(); tasktime.clear(); person.clear(); pq.clear();
		getline(cin, s);
		int tid, num, t0, t, dt, t2;
		while(n--){
			getline(cin, s);
			stringstream ss(s);
			ss >> tid >> num >> t0 >> t >> dt;
			for(int i = 0; i < num; i++){
				t2 = t0 + i * dt;
				if(!tasks.count(t2)){
					vector<int> v;
					v.push_back(tid);
					tasks[t2] = v;
				}
				else{
					tasks[t2].push_back(tid);
				}
				tasktime[tid] = t;
			}
		}//input tasks.
		cin >> m; getline(cin, s);
		int pid, k;
		while(m--){
			cin >> pid >> k;
			person[pid] = P(-1, -1);
			for(int i = 0; i < k; i++){
				cin >> tid;
				if(!pq.count(tid)){
					pp p; 
					p.push(PersonPri(pid, i));
					pq[tid] = p;
				}
				else{
					pq[tid].push(PersonPri(pid, i));
				}
			}
			getline(cin, s);
		}//input person, pq for each task;.

		int ts; PersonPri p;
		for(map<int, vector<int> >::iterator it = tasks.begin(); it != tasks.end(); it++){
			ts = it->first;
			for(unsigned int i = 0; i < it->second.size(); i++){
				tid =it->second[i];
				p  = pq[tid].top();
				
				if(ts < person[p.pid].end){person[p.pid].start = person[p.pid].end;}
				else{person[p.pid].start = ts;}
				person[p.pid].end = person[p.pid].start + tasktime[tid];	
				
				pq[tid].pop();
				pq[tid].push(p);
			}
		}
		int maxt = -1;
		for(map<int, P>::iterator it = person.begin(); it != person.end(); it++){
			maxt = max(maxt, it->second.end);
		}
		cout << "Scenario " << kase++ <<  ": All requests are serviced within " << maxt << " minutes." << endl;
	}
	return 0;
}

