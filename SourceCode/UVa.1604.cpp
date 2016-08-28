#include<cstdio>
#include<cstring>
#include<set>
#include<queue>
using namespace std;

typedef long long LL;

struct state{
	char cell[9][3]; //B=1; W=2; R=3; E=4
	int d;
};

int r, c;
int dr[] = {0,  0, 1, -1};
int dc[] = {1, -1, 0,  0};

int lookup(char c){
	if(c == 'B') return 1;
	else if(c == 'W') return 2;
	else if(c == 'R') return 3;
	return 4;
}

int check(state node){
	int v = 0;
	for(int i = 0; i < 9; i++){
		v = v * 10 + node.cell[i][0] - '0';
	}
	return v;
}

LL hashcode(state node){
	LL v = 0;
	for(int i = 0; i < 9; i++){
		v = v * 10 + node.cell[i][0] - '0';
		v = v * 10 + node.cell[i][1] - '0';
	}
	return v;
}

int solve(){
	//start state
	state s;
	for(int i = 0; i < 9 ; i++){s.cell[i][0] = '2'; s.cell[i][1] = '3'; s.cell[i][2] = '1'; } // idx = 0 means up and down sides; idx = 1 meas front and back sides; idx = 2 means left and right sides.
	int z = (r-1)*3 + (c-1);
	s.cell[z][0] = '4'; s.cell[z][1] = '4'; s.cell[z][2] = '4';
	s.d = 0;

	//target state
	int t = 0; char cc[10];
	fgets(cc, 10, stdin); //remove the \n in the previous line
	for(int i = 0; i < 3; i++){
		fgets(cc, 10, stdin);
		t = t * 10 + lookup(cc[0]);
		t = t * 10 + lookup(cc[2]);
		t = t * 10 + lookup(cc[4]);
	}

	set<LL> se;
	se.insert(hashcode(s));
	queue<state> q;
	q.push(s);

	while(!q.empty()){
		state node = q.front(); q.pop();
		if(check(node) == t) return node.d; // find the target.
		int z;
		for(z = 0; z < 9; z++) if(node.cell[z][0] == '4') break; //find the empyt cell
		int r = z / 3;
		int c = z % 3;
		for(int i = 0; i < 4; i++){
			int nr = r + dr[i];
			int nc = c + dc[i];
			if(nr < 0 || nr > 2 || nc < 0 || nc > 2) continue;
			int nz = nr * 3 + nc;
			state nnode = node;
			//memcpy(nnode, node, sizeof(struct state));
			memcpy(nnode.cell[z], nnode.cell[nz], sizeof(nnode.cell[nz]));
			nnode.cell[nz][0] = '4'; nnode.cell[nz][1] = '4'; nnode.cell[nz][2] = '4'; 
			if(i == 2 || i == 3){ //up and down  idx[0] <->idx[1]
				char t = nnode.cell[z][0];
				nnode.cell[z][0] = nnode.cell[z][1];
				nnode.cell[z][1] = t;
			}else if(i == 0 || i == 1){ //left and right idx[0] <->idx[2]
				char t = nnode.cell[z][0];
				nnode.cell[z][0] = nnode.cell[z][2];
				nnode.cell[z][2] = t;
			}
			nnode.d = node.d + 1;
			if(node.d > 30) return -1;
			int cc = hashcode(nnode);
			if(!se.count(cc)) {
				se.insert(cc);
				q.push(nnode);
			}
		}
	}
	return -1;
}

int main(){
#ifdef LOCAL
	freopen("UVa.1604.in", "r", stdin);
	freopen("UVa.1604.out", "w", stdout);
#endif
	while(scanf("%d%d", &c, &r) == 2 && c){
		printf("%d\n", solve());
	}
	return 0;
}

