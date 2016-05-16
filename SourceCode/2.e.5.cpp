//version 1 未考虑double型数据的有效数字只有15-16位  
#include <stdio.h>  
int main()  {  
    int a,b,c,count=1;  
    while(scanf("%d%d%d",&a,&b,&c)!=EOF){  
        if(a==0&&b==0&&c==0)  
            break;  
        printf("Case %d:%.*lf\n",count++,c,(double)(a)/b);  
        //printf("%*.*lf", 4, 5, 1.234567);   
        //意思是输出带宽为x，小数点后y为的double型数据z  
    }  
    return 0;  
}  

