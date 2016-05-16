//version 2 未考虑小数部分第c位是9，即四舍五入后还需进位  
#include <stdio.h>  
int main()  {  
    int a,b,c,tmp,count=1;  
    while(scanf("%d%d%d",&a,&b,&c)!=EOF){  
        if(a==0&&b==0&&c==0)  
            break;  
        printf("Case %d:%d.",count++,a/b);//整数部分  
        a=a%b*10;  
        while(c-->1){//小数点后前c-1位  
            printf("%d",a/b);  
            a=a%b*10;  
        }  
        tmp=a%b*10/b;//tmp是初始a/b的小数点后第c+1位数字  
        if(tmp<5)  
            printf("%d\n",a/b);  
        else  
            printf("%d\n",a/b+1);  
    }  
    return 0;  
}  

