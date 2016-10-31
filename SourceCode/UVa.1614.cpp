/*
Algorithm Proof

Assertion: with a list: a[1], a[2]...a[n], 1<=a[i]<=i. The summation of some of them cover all intergers in [1, sum[n]]

Proof: Mathematical induction

0. 1<=a[i]<=i, from the description
1. With only a[1] in the list, 1<=a[1]<=1; sum[1] = 1, the assertion is correct.
2. Suppose from the list: a[1], a[2]...a[k], the summation of some of them cover all intergers in [1, sum[k]]
3. We need to proof from the list: a[1], a[2]...a[k], a[k+1], the summation of some of them cover all intergers in [1, sum[k+1]]
    Notice: [1, sum[k+1]] = [1, sum[k]], sum[k]+1, sum[k]+2 ... sum[k]+a[k+1].
4. If we want to proof 3, we only need to proof: with 1<= x <=a[k+1], interger sum[k] + x -a[k+1] could be generated from a[1], a[2]...a[k]
5. 1<= a[k+1] <= k+1  (=>) 0 <= a[k+1] -1 <= k   (=>)  -k <= -(a[k+1]-1) <= 0 (=>) sum[k]-k <= sum[k]-(a[k+1]-1) <= sum[k];
    && sum[k] = a[1]+a[2]+...+a[k] >= 1+ 1 + ... +1 = k (=>)  sum[k]-k >= 0; So, we have 0 <= sum[k]-(a[k+1]-1) <= sum[k]
    
    when 1 <= sum[k]-(a[k+1]-1) <= sum[k], "sum[k]-(a[k+1]-1)" could be genareate from a[1], a[2]...a[k].
    when sum[k]-(a[k+1]-1) == 0, i think I don't need to approve it because it's 0, why I need to generate it from a[1], a[2]...a[k]? what do you say?
    So, we have prove 3.
    
Folllwing algorithm based on proved item 3.
    1. If the summmation is odd number, it will failed.
    2. The summation is even number and all the number must could be separate into two groups and summation of each group is sum = SUM/2.
        In the following steps, we need to find out a group of numbers who's summaion is sum, if we can do this, we are done.
    3. First, based on the proved item 3, the summation from a[1] to a[n] is SUM, so, we must could find some numbers and  their summation is sum. Becase sum = SUM/2 < SUM
    4. The key point is we search from right to left. If a[n] <= sum, we include a[n] in this group and sum  = sum - a[n]; 
    5. Because 3 && 4, we deduce that from a[1] to a[n-1], we still have possiblity to get the summation  =  sum = SUM/2 -a[n];
    6. The we compare a[n-1] and sum, if a[n-1] > sum, that mean a[n-1] can not be in the same group as a[n], we mark a[n-1] to another group,
        so based on 3 && 4 && 5, we still have possiblity to get the summation  =  sum = SUM/2 -a[n] from a[1] to a[n-2].

        if a[n-1] >= sum, we will include a[n-1] in this group, and sum = sum - a[n-1]. Based on 3 && 4 && 5 && 6, we still have possiblity to get the summation  =  sum = SUM/2 -a[n] - a[n-1] from a[1] to a[n-2].

     7. Repeat step 6 until we finished the classification. This group is decided when sum = 0, which mean we have found out all the number belong to this group.
*/

#include<cstdio>
using namespace std;

const int maxn = 100000 + 5;

int a[maxn], ans[maxn];

int main(){
#ifdef LOCAL
		freopen("UVa.1614.in", "r", stdin);
		freopen("UVa.1614.out", "w", stdout);
#endif
	int n;
	while(scanf("%d", &n) == 1){
		long long sum = 0;
		for(int i = 0; i < n; i++) {
			scanf("%d", &a[i]);
			sum += a[i];
		}
		if(sum%2 != 0){
			printf("No\n");
			continue;
		}
		sum /= 2;
		for(int i = n-1; i >= 0; i--){
			if(sum >= a[i]){
				sum -= a[i];
				ans[i] = -1;
			}
			else ans[i] = 1;
		}
		printf("Yes\n");
		for(int i = 0; i < n; i++){
			if(i == 0) printf("%d", ans[0]);
			else printf(" %d", ans[i]);
		}
		printf("\n");
	}
	return 0;
}

