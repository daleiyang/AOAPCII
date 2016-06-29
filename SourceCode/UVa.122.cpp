#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

const int maxn = 256 + 10;
const int root = 1;

int left[maxn], right[maxn], value[maxn], cnt;
bool have_value[maxn];

void newtree(){
	memset(left, 0, sizeof(left));
	memset(right, 0, sizeof(right));
	memset(have_value, 0, sizeof(have_value));
  	left[root] = right[root] = 0;
	have_value[root] = false;
	cnt = root;
}

int newnode(){
	int u = ++cnt; 
	left[u] = right[u] = 0; 
	have_value[u] = false;
	return u;
}

bool failed;
void addnode(int v, char * s){
	int n = strlen(s);
	int u = root;
	for(int i = 0; i < n; i++){
		if(s[i] == 'L'){
			if(left[u] == 0) left[u] = newnode();
			u = left[u];
		}
		else if(s[i] == 'R'){
			if(right[u] == 0) right[u] = newnode();
			u = right[u];
		}
	}
	if(have_value[u]) failed = true;  //test repeated assignment
	value[u] = v;
	have_value[u] = true;
}

char s[maxn];
bool read_input(){
	failed = false;
	newtree();
	for(;;){
		if(scanf("%s", s) != 1) return false;
		if(!strcmp(s, "()")) break;
		int v;
		sscanf(&s[1], "%d", &v);
		addnode(v, strchr(s, ',')+1);
	}
	return true;
}

bool bfs(vector<int> & ans){
	queue<int> q;
	ans.clear();
	q.push(root);
	while(!q.empty()){
		int u = q.front(); q.pop();
		if(!have_value[u]) return false; // test non-assignment node
		ans.push_back(value[u]);
		if(left[u] != 0) q.push(left[u]);
		if(right[u] != 0) q.push(right[u]);
	}
	return true;
}

int main(){
#ifdef LOCAL
	freopen("UVA.122.in", "r", stdin);
	freopen("UVA.122.out", "w", stdout);
#endif
	vector<int> ans;
	while(read_input()){
		if(!bfs(ans)) failed = true;
		if(failed) printf("not complete\n");
		else{
			for(unsigned int i = 0; i < ans.size(); i++){
				if(i != 0) printf(" ");
				printf("%d", ans[i]);
			}
			printf("\n");
		}
	}
	return 0;
}

