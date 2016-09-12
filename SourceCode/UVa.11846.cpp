#include<cstdio>
#include<cctype>

#define REP(i, b, n) for(int i = b; i < n; i++)
#define rep(i, n) REP(i, 0, n)

using namespace std;

const int N = 20;

char t[N][N], ans[N][N];
int n;

bool dfs(char c, int pos){
  while(pos != n * n && ans[pos/n][pos%n] != '.')pos++;
  if(pos == n*n)return true;
  int bx = pos%n, by = pos/n;
  REP(h, by, n){
    REP(w, bx, n){
      int cnt = 0, area = (h - by + 1) * (w - bx + 1);
      if( area > 9)break;
      if(ans[h][w] != '.')break;
      int now = -1;
      bool out = false;
      REP(y, by, h+1){
        REP(x, bx, w+1){
          if(isdigit(t[y][x])){
            cnt++;
            now = (t[y][x] - '0');
          }
          if(ans[y][x] != '.'){
            out = true;
            break;
          }
        }
        if(out || cnt > 1 || (now != -1 && now != area))break;
      }
      if(cnt > 1 || (now != -1 && (area > now || now % (h-by+1) != 0 ) ) || out)break;
      if(cnt == 0 || now > area)continue;
      REP(y, by, h+1){
        REP(x, bx, w+1){
          ans[y][x] = c;
        }
      }
      if(dfs(c+1, pos+(w-bx+1)))return true;
      REP(y, by, h+1){
        REP(x, bx, w+1){
          ans[y][x] = '.';
        }
      }
    }
  }
  return false;
}

int main(){
#ifdef LOCAL
	freopen("UVa.11846.in", "r", stdin);
	freopen("UVa.11846.out", "w", stdout);
#endif
  int tmp ;
  while(scanf("%d%d", &n, &tmp)){
    if( n == 0 && tmp == 0)break;
    rep(i, n){
      rep(j, n){
        scanf(" %c ",&t[i][j]);
        ans[i][j] = '.';
      }
    }
    dfs('A', 0);
    rep(i, n){
      rep(j, n){
        putchar(ans[i][j]);
      }
      putchar('\n');
    }
  }
  return 0;
}

