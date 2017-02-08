#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

const int INF = 1000000000;
const int minn = -9999, maxn = 9999;

struct State{
    char a[4][5];

    State child() const{
        State s;
        memcpy(&s, this, sizeof(s));
        return s;
    }

    bool lose(int p){
        if(p)  for(int j = 0; j < 4; j++) if(a[0][j] == 'P') return true; //'p' lose
        if(!p) for(int j = 0; j < 4; j++) if(a[3][j] == 'p') return true; //'P' lose

        bool f = false;
        if(p){//p = 1 for black 'p', go down, to bigger row number.
            for(int i = 0; i < 3; i++) for(int j = 0; j < 4; j++){
                if((a[i][j] == 'p') && ((j > 0 && a[i+1][j-1] == 'P') || (a[i+1][j] == '.') || (j < 3 && a[i+1][j+1] == 'P')))
                    f = true;
            }
        } else { //p = 0 for white 'P', go up, to smaller row number.
             for(int i = 1; i < 4; i++) for(int j = 0; j < 4; j++){
                if((a[i][j] == 'P') && ((j > 0 && a[i-1][j-1] == 'p') || (a[i-1][j] == '.') || (j < 3 && a[i-1][j+1] == 'p')))
                    f = true;
            }
        }
        if(!f) return true; //lose
        else return false; //keep moving;
    }

    void expend(int player, vector<State>& ret) const{
        char z = player ? 'p' : 'P'; 
        if(z == 'p'){
            for(int i = 0; i < 3; i++) for(int j = 0; j < 4; j++){
                if(a[i][j] != z) continue;
                if(j > 0 && a[i+1][j-1] == 'P'){
                    State s = child();
                    s.a[i][j] = '.'; 
                    s.a[i+1][j-1] = 'p';
                    ret.push_back(s);
                }
                if(a[i+1][j] == '.'){
                    State s = child();
                    s.a[i][j] = '.'; 
                    s.a[i+1][j] = 'p';
                    ret.push_back(s);
                }
                if(j < 3 && a[i+1][j+1] == 'P'){
                    State s = child();
                    s.a[i][j] = '.'; 
                    s.a[i+1][j+1] = 'p';
                    ret.push_back(s);
                }
            }
        } else {
            for(int i = 1; i < 4; i++) for(int j = 0; j < 4; j++){
                if(a[i][j] != z) continue;
                if(j > 0 && a[i-1][j-1] == 'p'){
                    State s = child();
                    s.a[i][j] = '.'; 
                    s.a[i-1][j-1] = 'P';
                    ret.push_back(s);
                }
                if(a[i-1][j] == '.'){
                    State s = child();
                    s.a[i][j] = '.'; 
                    s.a[i-1][j] = 'P';
                    ret.push_back(s);
                }
                if(j < 3 && a[i-1][j+1] == 'p'){
                    State s = child();
                    s.a[i][j] = '.'; 
                    s.a[i-1][j+1] = 'P';
                    ret.push_back(s);
                }
            }
        }
    }
};

int minimax(State& s, int player, int d){
    bool f = s.lose(player);
    if(!player && f) return minn+d; //'p' wins, the smaller (samller d), the better for 'p'
    if(player && f) return maxn-d;  //'P' wins, the greater (smaller d), the better for 'P'

    vector<State> children;
    s.expend(player, children);

    int a = -INF, b = INF;
    int n = children.size();
    for(int i = 0; i < n; i++){
        int v = minimax(children[i], player^1, d+1);
        if(!player) a = max(a, v); else b = min(b, v);
    }
    return !player ? a : b;
}

int main(){
#ifdef LOCAL
		freopen("UVa.10838.in", "r", stdin);
		freopen("UVa.10838.out", "w", stdout);
#endif
    int T;
    scanf("%d", &T);
    while(T--){
        State s;
        for(int i = 0; i < 4; i++) scanf("%s", s.a[i]);
        int score = minimax(s, 0, 0); //0 for black 'P', MAX player
        if(score > 0) printf("white (%d)\n", maxn-score);
        else if(score < 0) printf("black (%d)\n", score-minn);
    }
    return 0;
}
