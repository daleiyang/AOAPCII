#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long ll;
ll x, y, kase;

ll solve(ll x, ll y, ll N, ll S, ll W, ll E){
	ll sum = 0;

	//make the following logic easier
	if(S > N) swap(S, N);
	if(E > W) swap(E, W);
	
	//go 'N' first
	if(N){
		sum += x*y; //the first move with all robots
		y--;//go N one step; 
		N -= S;
		if(N){
			//(N, S): (3,1)N->(2,1)S->(2,0)N->(1,0)
			//(N, S): (3,2)N->(2,2)S -> (2,1)N ->(1,1) S->(1,0) N->(0.0)
			sum += x*y*S*2; //move from S->N, S*2 times
			N--;
		}
		else{ 
			//(N, S): (3, 3)N -> (2, 3)S -> (2,2)N -> (1,2)S->(1,1)N -> (0.1)S -> (0,0)
			sum += x*y*(S*2-1);
			//N == 0;
		}
		S = 0;
	}
	
	//go 'W' second
	if(W){
		W -= E;
		if(W){
			//(W, E): (3,1)W->(2,1)E->(2,0)W->(1,0)
			//(W, E): (3,2)W->(2,2)E->(2,1)W ->(1,1) E->(1,0) W->(0.0)
			E *= 2;
			W--;
		}
		else{
			// (W, E): (3, 3)W -> (2, 3)E -> (2,2)W -> (1,2)E->(1,1)W -> (0,1)E -> (0,0)
			E = E*2-1;
			//E == 0;
		}
		/*
		There we need to figure out which way to go:
		1. One step to N first, then W,  E->W (E times)  --->  x*y + x*(y-1) + (x-1)*(y-1)*E
		2. One step to W, then E->W (E times), one step to N ---> x*y  + (x-1)*y + (x-1)*y*E
		if we go one step N: x*y + x*(y-1) + (x-1)*(y-1)*E >= x*y  + (x-1)*y + (x-1)*y*E  ====> (1-x)*E >= x-y
		*/
		while(((1-x)*E >= x-y) && N){
			sum += x*y;
			N--; //one step to 'N'
			y--; //x robots killed
		}
		
		sum += x*y; //one step to ''W'
		x--; //y robots killed
		sum += x*y*E; //W->E->W->E...E times
		E = 0; //clean E and W >=0;
	}
	
	//Has 'N' and 'W' only
	while((x*y)>0 && (N+W)>0){ //has robots alive and N or E step to go
		sum += x*y; //one step
		if((y > x && N) || !W){//N > 0 and go N kill less robot  or  W == 0, we go N
 			N--;
			y--;
		}
		else{
			W--;
			x--;
		}
	}
	return sum;
}

int main(){
#ifdef LOCAL
		freopen("UVa.1622.in", "r", stdin);
		freopen("UVa.1622.out", "w", stdout);
#endif
	kase = 0;
	while(1){
		cin >> y >> x;
		if(!x && !y) break;
		ll N, S, W, E;
		cin >> N >> S >> W >> E;
		//we need to try N first and W fisrt to find a max value. the trick is to switch parameters' order.
		ll sum = max(solve(x, y, N, S, W, E), solve(y, x, E, W, N, S));
		cout << "Case " << ++kase << ": " << sum << endl;
	}
	return 0;
}

