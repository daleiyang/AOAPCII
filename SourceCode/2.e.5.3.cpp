//version 3  
#include <stdio.h>  
int main()  { 
    int a,b,c,tmp,i,t,count=1;;  
    int s[110];//用于保存小数点后的部分  
    while(scanf("%d%d%d",&a,&b,&c)!=EOF){  
        if(a==0&&b==0&&c==0)  
            break;  
        t=a/b;  
        a=a%b*10;  
        for(i=1;i<c;i++){//小数点后前c-1位保存到数组s中  
            s[i]=a/b;  
            a=a%b*10;  
        }  
        tmp=a%b*10/b;//tmp是初始a/b的小数点后第c+1位数字  
        if(tmp<5)  
            s[i]=a/b;//s[i]即s[c]  
        else  
            s[i]=a/b+1;  
        while(i>1){  
            if(s[i]==10){  
                s[i]-=10;  
                s[i-1]+=1;  
            }  
            i--;  
        }  
        if(s[1]==10){  
            s[1]-=10;  
            t++;  
        }  
        printf("Case %d:%d.",count++,t);  
        for(i=1;i<=c;i++)  
            printf("%d",s[i]);  
        printf("\n");  
    }  
    return 0;  
}  

