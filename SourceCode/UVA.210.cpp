#include<cstring>
#include<cctype>
#include<cstdio>
#include<queue>
#include<vector>
using namespace std;

const int maxn = 1000;

char prog[maxn][10];
int q[5]; // q[0] for assignment; q[1] for print; q[2] for lock; q[3] for unlock; q[4] for end;
int val[26], quantum, pidx[maxn]; //command index for each program
queue<int> d;
deque<int> r;
bool locked;

void run(int pid){
	int qu = quantum;
	while(qu > 0){ //within quantum in this run.
		char * p = prog[pidx[pid]];
		switch(p[2]){
			case '=':{
				val[p[0] - 'a'] = isdigit(p[5]) ? (p[4] - '0') * 10 + p[5] - '0' : p[4] - '0';
				qu -= q[0];
				break;
			}
			case 'i':{
				printf("%d: %d\n", pid+1, val[p[6]-'a']);
				qu -= q[1];
				break;
			}
			case 'c':{
				if(locked){d.push(pid); return;}
				locked = true;
				qu -= q[2];
				break;
			}
			case 'l':{
				locked = false;
				if(!d.empty()){
					r.push_front(d.front());
					d.pop();
				}
				qu -= q[3];
				break;
			}
			case 'd':{
				return;
			}
		}
		pidx[pid]++;
	}
	r.push_back(pid);
}

int main(){
#ifdef LOCAL
	freopen("UVA.210.in", "r", stdin);
	freopen("UVA.210.out", "w", stdout);
#endif
	int T, n;
	scanf("%d", &T);
	while(T--){
		//clean
		//queue<int> e1; swap(d, e1);
		//deque<int> e2; swap(r, e2);
		memset(val, 0, sizeof(val)); 
		//memset(pidx, 0, sizeof(pidx));
		//input
		scanf("%d%d%d%d%d%d%d", &n, &q[0], &q[1], &q[2], &q[3], &q[4], &quantum);
		int line = 0;
		for(int i = 0; i < n; i++){
			fgets(prog[line++], maxn, stdin);
			pidx[i] = line-1;
			while(prog[line-1][2] != 'd')
				fgets(prog[line++], maxn, stdin);
			r.push_back(i);
		}
		locked = false;
		while(!r.empty()){
			int pid = r.front();
			r.pop_front();
			run(pid);
		}
		if(T) printf("\n");
	}
	return 0;
}

