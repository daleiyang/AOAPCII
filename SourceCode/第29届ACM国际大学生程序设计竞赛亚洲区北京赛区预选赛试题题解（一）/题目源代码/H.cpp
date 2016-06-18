//本题作者是刘子阳  --编者注
#include<stdio.h>
int main()
{
	int row,col,i,j,right,left,curr,sum,flag;
	char map[300][300];			//the board
	while(scanf("%d %d",&row,&col))
	{
		if(!row && !col) break;
		for(i=0;i<row;i++) scanf("%s",map[i]);
		for(i=0;i<col;i++) if(map[0][i]=='S') break; //find 'S' in the first row
		sum=1;	//sum: the total grids occupied by S
		curr=i; //the current S's position(after optimized)
		flag=0; //flag=0 means that S hasn't turned(either left or right) yet, and vice versa
		for(i=1;i<row;i++)
		{
			for(j=0;j<col;j++)
			{
				if(map[i][j]=='S') {left=j; break;}
			}//left is the position of the leftmost S in the ith line
			for(j=0;j<col;j++)
			{
				if(map[i][j]=='B') {right=j-1; break;}
			}
			if(flag==0 && left<right) 
			{
				flag=1; 
				if(left==curr) //S turns right first! So sum must minus by 1!
					sum--; 
			}//left is the position of the rightmost S in the ith line
			if(right>curr) left=curr;
			if(right<curr) right=curr;
			if(left==right) {sum++; continue;} //S goes straight
			if(right>curr) {sum+=(right-left+1); curr=right; continue;} //S turns right
			if(left<right) {left++; sum+=(right-left+1); curr=left; continue;} //S turns left
		}
		printf("%d\n",sum);
	}
	return 0;
}
