//http://blog.csdn.net/playwfun/article/details/51125144
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

typedef long long ll;
#define rep( i , n) for(int i = 0 ; i<(int)n;i++)
#define rep1(i ,x , y) for(int i = (int)x ; i<=(int)y;i++)
const int N = 5050;

int max_[N][20],min_[N][20],lg2[N]; //
void ST(int *a,int n)
{
    lg2[0]=-1;
    for(int i=1; i<=n; i++)
        lg2[i]=lg2[i-1]+(i&(i-1)?0:1);
    for(int i=0; i<n; i++) max_[i][0]=a[i]; //a
    for(int j=1; j<=lg2[n]; j++)
        for(int i=0; lg2[n-i]>=j; i++)
            max_[i][j]=max(max_[i][j-1],max_[i+(1<<(j-1))][j-1]);
}
int RMQ_Max(int x,int y)
{
    int k=lg2[y-x+1];
    return max(max_[x][k],max_[y-(1<<k)+1][k]);
}
void ST2(int *a,int n)
{
    lg2[0]=-1;
    for(int i=1; i<=n; i++)
        lg2[i]=lg2[i-1]+(i&(i-1)?0:1);
    for(int i=0; i<n; i++) min_[i][0]=a[i]; //a
    for(int j=1; j<=lg2[n]; j++)
        for(int i=0; lg2[n-i]>=j; i++)
            min_[i][j]=min(min_[i][j-1],min_[i+(1<<(j-1))][j-1]);
}
int RMQ_Min(int x,int y)
{
    int k=lg2[y-x+1];
    return min(min_[x][k],min_[y-(1<<k)+1][k]);
}

struct San :vector<int>
{
    void prepare()
    {
        sort(begin(),end());
        erase(unique(begin(),end()),end());
    }
    int get(int x)
    {
        return (int)(lower_bound(begin(),end(),x)-begin())+1;
    }
} rank2;
int n,a[N],pos[N];
bool cal()
{
    ST2(a , n);
    ST(pos , n);

    int ok = 0;
    for(int i = 1 ; i<=n ; i++)
    {
        for(int j = i + 1 ; j<=n ; j++) if(a[j] > a[i])
            {
                int L = a[i] + 1;
                int R = a[j] - 1;
                if(L > R) continue;
                int max_pos = RMQ_Max(L , R);
                R = (--max_pos);
                L = j + 1;
                if(L > R) continue;
                int min_val = RMQ_Min(L , R);
                if(min_val < a[i]){
                    ok = 1;
                    break;
                }
            }
        if(ok) break;
    }
    return ok;
}
int main()
{
#ifdef LOCAL
			freopen("UVa.1618.in", "r", stdin);
			freopen("UVa.1618.out", "w", stdout);
#endif
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        rank2.clear();
        rep1(i , 1 , n) scanf("%d",&a[i]),rank2.push_back(a[i]);
        rank2.prepare();
        for(int i = 1 ; i<=n ; i++)
        {
            a[i] = rank2.get(a[i]);
            pos[a[i]] = i;
        }
        if(cal())
        {
            printf("YES\n");
            continue;
        }
        for(int i = 1 ; i<=n ; i++)
        {
            a[i] = n + 1 - a[i];
            pos[a[i]] = i;
        }
        if(cal())
        {
            printf("YES\n");
            continue;
        }
        printf("%s\n","NO");
    }
    return 0;
}

