#include<cstdio>
using namespace std;

const int maxn = 200000+5;
const int INF = 0x3f3f3f3f;

int min(int a, int b) { return a < b ? a : b; }
void swap(int &a, int &b) { int t = a; a = b; b = t; } 

struct Node{
    int v, add, mi, flip, s;
    Node* ch[2];
    void maintain(){
        mi = min(v, min(ch[0]->mi, ch[1]->mi));
        s = ch[0]->s + ch[1]->s + 1;
    }
    void modify(int s){
        add += s; v += s; mi += s;
    }
    void pushdown(){
        if(flip){
            flip = 0;
            Node *t = ch[0];
            ch[0] = ch[1];
            ch[1] = t;
            ch[0]->flip ^= 1;
            ch[1]->flip ^= 1;
        }
        if(add){
            if(ch[0]->mi != INF) ch[0]->modify(add);
            if(ch[1]->mi != INF) ch[1]->modify(add);
            add = 0;
        }
    }
    int cmp(int k){
        int d = k-ch[0]->s;
        if(d == 1) return -1;
        return d <= 0 ? 0 : 1;
    }
} *root, *null, newnode[maxn];

int a[maxn], idx;

Node* build(int L, int R){
    if(L >= R) return null;
    int M = L + (R-L)/2;
    Node* p = &newnode[++idx];
    p->v = a[M];
    p->add = p->flip = 0;
    p->ch[0] = build(L, M);
    p->ch[1] = build(M+1, R);
    p->maintain();
    return p;
}

void rotate(Node* &o, int d){
	Node* k = o->ch[d^1]; o->ch[d^1] = k->ch[d]; k->ch[d] = o;
	o->maintain(); k->maintain(); o = k;
}

void splay(Node* &o, int k){
	o->pushdown();
	int d = o->cmp(k);
	if(d == 1) k -= o->ch[0]->s+1;
	if(d != -1){
		Node* p = o->ch[d];
		p->pushdown();
		int d2 = p->cmp(k);
		int k2 = (d2 == 0 ? k : k-p->ch[0]->s-1);
		if(d2 != -1){
			splay(p->ch[d2], k2);
			if(d == d2) rotate(o, d^1); else rotate(o->ch[d], d);
		}
		rotate(o, d^1);
	}
}

void split(Node* o, int k, Node* &left, Node* &right){
    splay(o, k);
    left = o;
    right = o->ch[1];
    o->ch[1] = null;
    left->maintain();
}

Node* merge(Node* left, Node* right){
    splay(left, left->s);
    left->ch[1] = right;
    left->maintain();
    return left;
}

void print(Node* o){
    if(o == null) return;
    o->pushdown();
    print(o->ch[0]);
    printf("%d ", o->v);
    print(o->ch[1]);
}

int main(){
#ifdef LOCAL
	freopen("poj.3580.in", "r", stdin);
	freopen("poj.3580.out", "w", stdout);
#endif
    int n, m, x, y, d;
    char op[10];
    null = new Node();
    null->s = null->add = null->flip = 0;
    null->mi = INF;
    Node *o, *left, *mid, *right, *tmp, *p;
    while(scanf("%d", &n) == 1){
        for(int i = 0; i < n; i++) scanf("%d", &a[i]);
        idx = 0;
        root = build(0, n);
        scanf("%d", &m);
        while(m--){
            scanf("%s", op);
            if(op[0] == 'A'){ //ADD
                scanf("%d%d%d", &x, &y, &d);
                if(x > y) swap(x, y);
                if(x == 1){
                    split(root, y-x+1, left, o);
                    left->modify(d);
                    root = merge(left, o);
                }
                else{
                    split(root, x-1, left, o);
                    split(o, y-x+1, mid, right);
                    mid->modify(d);
                    root = merge(merge(left, mid), right);
                }
            }
            else if(op[0] == 'R'){
                if(op[3] == 'E'){ //REVERSE
                    scanf("%d%d", &x, &y);
                    if(x > y) swap(x, y);
                    if(x == 1){
                        split(root, y-x+1, left, o);
                        left->flip ^= 1;
                        root= merge(left, o);
                    }
                    else {
                        split(root, x-1, left, o);
                        split(o, y-x+1, mid, right);
                        mid->flip ^= 1;
                        root = merge(merge(left, mid), right);
                    }
                }
                else{ //REVOLVE
                    scanf("%d%d%d", &x, &y, &d);
                    if(x > y) swap(x, y);
                    d %= (y-x+1);
                    d = (d+y-x+1)%(y-x+1);
                    if(d == 0) continue;
                    int len = y-x+1-d;
                    if(x == 1){
                        split(root, y-x+1, o, right);
                        split(o, len, left, mid);
                        root = merge(merge(mid, left), right);
                    }
                    else{
                        split(root, x-1, left, o);
                        split(o, y-x+1, tmp, right);
                        split(tmp, len, p, mid);
                        root = merge(merge(merge(left, mid), p), right);
                    }
                }
            }
            else if(op[0] == 'I'){ //INSERT
                scanf("%d%d", &x, &d);
                o = &newnode[++idx];
                o->add = o->flip = 0;
                o->s = 1;
                o->v = o->mi = d;
                o->ch[0] = o->ch[1] = null;
                if(!x){
                    root = merge(o, root);
                    //print(root);
                }
                else{
                    split(root, x, left, right);
                    root = merge(merge(left, o), right);
                }
            }
            else if(op[0] == 'D'){ //DELETE
                scanf("%d", &x);
                if(x == 1){
                    split(root, 1, left, o);
                    root = o;
                }
                else{
                    split(root, x-1, left, o);
                    split(o, 1, mid, right);
                    root = merge(left, right);
                }
            }
            else{ //MIN
                scanf("%d%d", &x, &y);
                if(x > y) swap(x, y);
                int ans;
                if(x == 1){
                    split(root, y-x+1, left, right);
                    ans = left->mi;
                    root = merge(left, right);
                }
                else{
                    split(root, x-1, left, o);
                    split(o, y-x+1, mid, right);
                    ans = mid->mi;
                    root = merge(merge(left, mid), right);
                }
                printf("%d\n", ans);
            }
        }
    }
    return 0;
}
