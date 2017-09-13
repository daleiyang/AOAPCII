//https://github.com/morris821028/UVa/blob/master/temp/10366%20-%20Faucet%20Flow.cpp
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 1000+5;

int h[maxn];

int main(){
#ifdef LOCAL
		freopen("UVA.10366.in", "r", stdin);
		freopen("UVA.10366.out", "w", stdout);
#endif
	int LX, RX, N;
	while(scanf("%d%d", &LX, &RX) == 2 && LX){
		N = (RX-LX)/2+1; //dividers number
		int LH = 0, RH = 0, LHidx = -1, RHidx = 0;//highest on left and right side
		int l = (-1-LX)/2, r =(-1-LX)/2+1; //'l' is the "-1" divider's idx, 'r' is the '1' divider's idx
		for(int i = 0; i < N; i++){
			scanf("%d", &h[i]);
			if(i <= l && LH <= h[i]){//highest one, closest to l, so '<='
				LH = h[i];
				LHidx = i;
			}
			if(i >= r && RH < h[i]){//highest one, closest to r, so '>'
				RH = h[i];
				RHidx = i;
			}
		}
		int ret = 0;
		if(LH == RH){
			int lcost = 0, rcost = 0;
			//calculate size on the left side. between 0 and LHidx
			for(int i = 0, j = 0; i < LHidx; i++){
				j = max(j, h[i]); 
				lcost += j;
			}
			//calculate size on the right side. between 0 and LHidx
			for(int i = N-1, j = 0; i > RHidx; i--){
				j = max(j, h[i]);
				rcost += j;
			}
			//the space between LH and RH will be filled and choice one side with smaller size.
			ret = (RHidx - LHidx) * RH * 2 + min(lcost, rcost) * 2 * 2;
			printf("%d\n", ret);
		}
		else{
			int v = min(LH, RH);
			int lcost = 0, rcost = 0;
			//find the idx which h[idx] >= v on both sides and closest to l and r.
			while(h[l] < v) l--;
			while(h[r] < v) r++;
			if(RH > LH){
				//magic here! calculate the size start from hight same as LH until RH
				for(int i = r, j = h[i]; h[i] <= LH; i++){
					rcost += j;
					j = max(j, h[j+1]);
				}
				//calculate the left size
				for(int i = 0, j = h[0]; i < l; i++){
					lcost += j;
					j = max(j, h[i+1]);
				}
			}
			else{
				//magic here! calculate the size start from hight same as RH until LH
				for(int i = l, j = h[i]; h[i] <= RH; i--){
					//we calculate lcost, but use rcost to make the final ret calculate easier.
					rcost += j;
					j = max(j, h[i-1]);
				}
				for(int i = N-1, j = h[N-1]; i > r; i--){
					//we calculate rcost, but use lcost to make the final ret calculate easier.
					lcost += j;
					j = max(j, h[i-1]);
				}
			}
			//magic logci here, draw on paper, you will understand
			ret = (lcost > rcost ? lcost + rcost : 2 * lcost) * 2;
			ret += (r-l)*v*2;
			printf("%d\n", ret);
		}
	}
	return 0;
}

