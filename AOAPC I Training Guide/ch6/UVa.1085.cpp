#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

const int UP = 0, FLOOR = 1, DOWN = 2;
const int maxn = 20;

int n, deck[maxn*2];

struct State{
    int card[8], type[8], hold[2], pos, score;

    State child() const{
        State s;
        memcpy(&s, this, sizeof(s));
        s.pos = pos+1;
        return s;
    }

    State(){
        for(int i = 0; i < 8; i++){
            card[i] = deck[i];
            type[i] = i%2==0 ? UP : DOWN;
        }
        hold[0] = hold[1] = score = 0;
        pos = 8;
    }

    bool isFinal(){
        if(pos == 2*n){
            score += hold[0] + hold[1];
            hold[0] = hold[1] = 0;
            return true;
        }
        return false;
    }

    int getScore(int c1, int c2, int c3) const{
        int S = abs(c1)+abs(c2)+abs(c3);
        int cnt = 0;
        if(c1 > 0) cnt++; if(c2 > 0) cnt++; if(c3 > 0) cnt++;
        return cnt >= 2 ? S : -S;
    }

    void expend(int player, vector<State>& ret) const{
        int cur = deck[pos];

        if(hold[player] == 0){
            State s = child();
            s.hold[player] = cur;
            ret.push_back(s);
        }

        for(int i = 0; i < 7; i++) if(type[i] == DOWN && type[i+1] == UP){
            State s = child();
            s.score += getScore(card[i], card[i+1], cur);
            s.type[i] = s.type[i+1] = FLOOR;
            s.card[i] = s.card[i+1] = cur;
            ret.push_back(s);

            if(hold[player] != 0){
                State s =child();
                s.score += getScore(card[i], card[i+1], hold[player]);
                s.type[i] = s.type[i+1] = FLOOR;
                s.card[i] = s.card[i+1] = hold[player];
                s.hold[player] = cur;
                ret.push_back(s);
            }
        }

        if(hold[player] != 0)
            for(int i = 0; i < 7; i++) if(type[i] == FLOOR && type[i+1] == FLOOR && card[i] == card[i+1]){
                State s = child();
                s.score += getScore(card[i], hold[player], cur);
                s.type[i] = UP; s.type[i+1] = DOWN;
                s.card[i] = cur; s.card[i+1] = hold[player]; s.hold[player] = 0;
                ret.push_back(s);

                swap(s.card[i], s.card[i+1]);
                ret.push_back(s);
            }
    }
};

int alphabeta(State& s, int player, int alpha, int beta){
    if(s.isFinal()) return s.score;
    
    vector<State> children;
    s.expend(player, children);

    int n = children.size();
    for(int i = 0; i < n; i++){
        int v = alphabeta(children[i], player^1, alpha, beta);
        if(!player) alpha = max(alpha, v); else beta = min(beta, v);
        if(beta <= alpha) break;
    }
    return !player ? alpha : beta;
}

const int INF = 1000000000;

int main(){
#ifdef LOCAL
	freopen("UVa.1085.in", "r", stdin);
	freopen("UVa.1085.out", "w", stdout);
#endif
    int kase = 0;
    char P[10];
    while(scanf("%s", P) == 1 && P[0] != 'E'){
        scanf("%d", &n);
        for(int i = 0; i < n*2; i++){
            char ch;
            scanf("%d%c", &deck[i], &ch);
            if(ch == 'B') deck[i] = -deck[i];
        }
        State initial;
        int first_player = deck[0] > 0 ? 0 : 1;
        int score = alphabeta(initial, first_player, -INF, INF);

        if(P[0] == 'B') score = -score;
        printf("Case %d: ", ++kase);
        if(score == 0) printf("Axel and Birgit tie\n");
        else if(score > 0) printf("%s wins %d\n", P, score);
        else printf("%s loses %d\n", P, -score);
    }
    return 0;
}