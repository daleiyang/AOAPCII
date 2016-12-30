#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 400000 + 10;
unsigned powers[maxn];

struct Node *null, *pit;
struct Node{
	Node *ch[2];
	int s;
	int v;
	int flip;
	unsigned h1, h2;

	Node(){}
	Node(int v):v(v), h1(v), h2(v){ch[0] = ch[1] = null; flip = 0; s = 1;}
	void * operator new(size_t){return pit++;}
		
	//rank tree
	int cmp(int k) const{
		int d = k - ch[0]->s;
		if(d == 1) return -1;
		return d <= 0 ? 0:1;
	}
	void maintain(){
		s = ch[0]->s + ch[1]->s + 1;
		h1 = ch[0]->h1*powers[ch[1]->s+1] + v*powers[ch[1]->s] + ch[1]->h1;
		h2 = ch[1]->h2*powers[ch[0]->s+1] + v*powers[ch[0]->s] + ch[0]->h2;
	}
	void reverse(){
		flip ^= 1;
		swap(ch[0], ch[1]);
		swap(h1, h2);
	}
	void pushdown(){
		if(flip){
			flip = 0;
			ch[0]->reverse();
			ch[1]->reverse();
		}
	}
}pool[maxn];

void init_null(){
	null = new Node();
	null->s = 0;
}

void rotate(Node* &o, int d){
	Node* k = o->ch[d^1]; o->ch[d^1] = k->ch[d]; k->ch[d] = o;
	o->maintain(); k->maintain(); o = k;
}

void splay(Node* &o, int k){
	o->pushdown();
	int d = o->cmp(k);
	if(d == 1) k -= o->ch[0]->s + 1;
	if(d != -1){
		Node* p = o->ch[d];
		p->pushdown();
		int d2 = p->cmp(k);
		int k2 = (d2 == 0 ? k : k - p->ch[0]->s - 1);
		if(d2 != -1){
			splay(p->ch[d2], k2);
			if(d == d2) rotate(o, d^1); else rotate(o->ch[d], d);
		}
		rotate(o, d^1);
	}
}

#include<cstring>
struct SplaySequence{
	char *s;
	Node *root;

	Node* build(int L, int R){
		int M = L + (R-L)/2;
		Node* o = new Node(s[M]);
		if(L<M) o->ch[0] = build(L, M);
		if(M+1 < R) o->ch[1] = build(M+1, R);
		o->maintain();
		return o;
	}

	void update_dummy(){
		root->ch[1]->maintain();
		root->maintain();
	}

	Node* last() const{
		return root->ch[1]->ch[0];
	}

	Node* build(char* s){
		this->s = s;
		root = new Node('[');
		root->ch[1] = new Node(']');
		root->ch[1]->ch[0] = build(0, strlen(s));
		update_dummy();
		return root;
	}

	Node*& range(int L, int R){
		splay(root, L);
		splay(root->ch[1], R-L+1);
		return root->ch[1]->ch[0];
	}
};

int main(){
#ifdef LOCAL
	freopen("UVA.11996.in", "r", stdin);
	freopen("UVA.11996.out", "w", stdout);
#endif
	int n, m;
	char s[maxn];
	powers[0] = 1;
	for(int i = 1; i < maxn; i++) powers[i] = powers[i-1]*3137;

	while(scanf("%d%d%s", &n, &m, s) == 3){
		SplaySequence ss;
		pit = pool;
		init_null();
		ss.build(s);

		while(m--){
			int op, x, y;
			scanf("%d%d", &op, &x);
			if(op == 1){
				scanf("%d", &y);
				ss.range(x+1, x+1) = new Node(y+'0');
				ss.update_dummy();
			}
			else if(op == 2){
				ss.range(x, x+1) = null;
				ss.update_dummy();
			}
			else if(op == 3){
				scanf("%d", &y);
				ss.range(x, y+1)->reverse();
				ss.update_dummy();
			}
			else{
				scanf("%d", &y);
				int L = 0, R = ss.root->s-y;
				while(L < R-1){
					int M = L+(R-L)/2;
					unsigned h1 = ss.range(x, x+M)->h1;
					unsigned h2 = ss.last()->h2;
					h1 -= ss.range(y, y+M)->h1;
					h2 -= ss.last()->h2;
					if(!h1 && !h2) L = M; else R = M;
				}
				printf("%d\n", L);
			}
		}
	}
	return 0;
}

