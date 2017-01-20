#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int INF = 1000000000;
const int maxnode = 1<<17;

int op, qL, qR, p, v;

struct IntervalTree {
  int minv[maxnode];

  void update(int o, int L, int R) {
    int M = L + (R-L)/2;
    if(L == R) minv[o] = v;
    else {
      if(p <= M) update(o*2, L, M); else update(o*2+1, M+1, R);
      minv[o] = min(minv[o*2], minv[o*2+1]);
    }
  }

  int query(int o, int L, int R) {
    int M = L + (R-L)/2, ans = INF;
    if(qL <= L && R <= qR) return minv[o];
    if(qL <= M) ans = min(ans, query(o*2, L, M));
    if(M < qR) ans = min(ans, query(o*2+1, M+1, R));
    return ans;
  }
};

IntervalTree tree;

int main() {
  int n, m;
  while(scanf("%d%d", &n, &m) == 2) {
    memset(&tree, 0, sizeof(tree));
    while(m--) {
      scanf("%d", &op);
      if(op == 1) {
        scanf("%d%d", &p, &v);
        tree.update(1, 1, n);
      } else {
        scanf("%d%d", &qL, &qR);
        printf("%d\n", tree.query(1, 1, n));
      }
    }
  }
  return 0;
}
