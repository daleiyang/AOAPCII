#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;
const int MAX = 32;
int n;
int A[MAX][MAX];
int st;

void print()
{
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            printf("%3d", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void dfs(int x, int y, int w)
{
    if(w == 1) {
        return;
    }
    int i, j;
    int found = 0;
    for(i=x; i<x+w; i++) {
        for(j=y; j<y+w; j++) {
            if(A[i][j] != 0) {
                found = 1;
                break;
            }
        }
        if(found) break;
    }
    int mx = x+w/2, my = y+w/2;
    int bx = i < mx;
    int by = j < my;
    if(bx) {
        A[mx][my-1] = A[mx][my] = st;
        if(by) A[mx-1][my] = st;
        else A[mx-1][my-1] = st;
    } else {
        A[mx-1][my] = A[mx-1][my-1] = st;
        if(by) A[mx][my] = st;
        else A[mx][my-1] = st;
    }
    print();
    st++;
    int tw = w/2;
    dfs(mx-tw, my-tw, tw);
    dfs(mx-tw, my, tw);
    dfs(mx, my-tw, tw);
    dfs(mx, my, tw);
}

int main(){
#ifdef LOCAL
	freopen("8.3.1.in", "r", stdin);
	freopen("8.3.1.out", "w", stdout);
#endif
    int k;
    int gx, gy;
    while(scanf("%d%d%d", &k, &gx, &gy) == 3) {
        memset(A, 0, sizeof(A));
        st = 1;
        n = 1 << k;
        A[gx][gy] = -1;
        print();
        dfs(0, 0, n);
        print();
    }
    return 0;
}

