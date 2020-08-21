#include <cstdio>
using namespace std;
const int N=100005;
int sm[N],q[N];
char s[N];
 
int sol(int x1,int x2,int x3,int x4)  {
	int sol = (sm[x2]-sm[x1])*(x4-x3)-(sm[x4]-sm[x3])*(x2-x1);
	return sol;
}

int main() {
#ifdef LOCAL
	freopen("UVa.1451.in", "r", stdin);
	freopen("UVa.1451.out", "w", stdout);
#endif
	int n,l,T;
 
	scanf("%d",&T);
	while (T--) {
		scanf("%d %d %s",&n,&l,s+1);
		sm[0]=0;
		for (int i=1;i<=n;i++) sm[i]=sm[i-1]+s[i]-'0';
		int tl=0,tr=l;
 
		int i=0,j=0;
		for (int t=l;t<=n;t++) {
			while(i<j-1&&sol(q[j-1],t-l,q[j-2],t-l)<0) j--;
			q[j++]=t-l;
			while(i<j-1&&sol(q[i+1],t,q[i],t)>=0) i++;
 
			int tt=sol(q[i],t,tl,tr);
			if (tt>0||tt==0&&(t-q[i]<tr-tl)) tr=t,tl=q[i];
		}
		printf("%d %d\n",tl+1,tr);
	}
}
