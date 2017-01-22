//本题作者是肖颖  --编者注
#include "stdio.h" 
#include <algorithm> 
using namespace std; 

int K;    // 0<K<= 10000 
int Q,P;  // 0<Q<=3000 , 0<P<=3000 
int N;    // N <=1000 
struct in {int q, p;}; 

in input[1010]; 

bool cmp(in a,in b) 
{ 
return a.q < b.q;       
} 


int main(void) 
{ 
char tmp[1000]; 
char useless[100]; 


// freopen("c.in","r",stdin); 
  
while(gets(tmp)) 
{ 
   if(tmp[0] == '#') { scanf("%d",&K);  break; } 
   sscanf(tmp,"%s%d%d",useless,&input[N].q,&input[N].p); 
    N++;          
} 
sort(input,input + N,cmp); 
  
int already = 0; 
for(int t = 1; ; t++) 
{ 
        for(int i =0;i<N;i++) 
   if( t        % input[i].p ==0) 
    { 
        printf("%d\n",input[i].q); 
        already ++; 
        if(already == K) goto END; 
    } 
} 
  
END:  
return 0; 
}
