//本题作者是宋鑫莹  --编者注
#include <queue>
#include <math.h>
#include<memory.h>
using namespace std;

/*
wall[1][1][0] means there is a unit wall between (1,1) and (2,1),
wall[1][1][1] means there is a unit wall between (1,1) adn (1,2),
so is door[][][].
*/
bool wall[201][201][2];
bool door[201][201][2];

//search visited flag
bool used[201][201];

//search ending flag
bool final[201][201];

//key
int bfn[201][201];

//borders of x and y
int xl, xh, yl, yh;

//priority queue
class cmp
{
public: inline bool operator()(int a, int b)
		{
			return bfn[a/300][a%300] > bfn[b/300][b%300];
		}
};
priority_queue <int, vector<int>,cmp> myque;


bool read()
{
	int m ,n, x ,y ,i ,j, d, t;
	scanf("%d %d", &m, &n);
	if(m < 0 || n < 0) return 0;
	memset(wall, 0, sizeof(wall));
	memset(door, 0, sizeof(door));	
	xh = -1, xl = 200, yh = -1, yl = 200;
	for(i = 0; i < m; ++i)
	{
		scanf("%d %d %d %d", &x, &y, &d, &t);
		if(d)
		{	
			if(xl > x) xl = x;
			if(xh < x) xh = x;
			if(yl > y) yl = y;
			if(yh < y + t) yh = y + t;
			for(j = 0; j < t; ++j)
				wall[x][y+j][1] = 1; 						
		}else
		{			
			if(xl > x) xl = x;
			if(xh < x + t) xh = x + t;
			if(yl > y) yl = y;
			if(yh < y) yh = y;
			for(j = 0; j < t; ++j)
				wall[x+j][y][0] = 1;					
		}
	}
	for(i = 0; i < n; ++i)
	{
		scanf("%d %d %d", &x, &y, &d);
		wall[x][y][d] = 0;
		door[x][y][d] = 1;
	}
	--xl;
	--yl;	
	return 1;
}

/*
here we set flag to all points that can be reach from Marlin 
with no door and no wall
*/
void setfinal(int x, int y)
{
	final[x][y] = 1;
	if(x > xl && !wall[x][y][1] && !door[x][y][1] && !final[x-1][y])
		setfinal(x-1, y);
	if(y > yl && !wall[x][y][0] && !door[x][y][0] && !final[x][y-1])
		setfinal(x, y-1);
	if(x < xh && !wall[x+1][y][1] && !wall[x+1][y][1] && !final[x+1][y])
		setfinal(x+1, y);
	if(y < yh && !wall[x][y+1][0] && !wall[x][y+1][0] && !final[x][y+1])
		setfinal(x, y+1);
}


void process()
{
	int x, y, z, ans;	
	double a, b;
	bool flag = 0;
	
	scanf("%lf %lf", &a, &b);
	x = (int)floor(a); y = (int)floor(b);
	if(x<=0 || x>=200 || y<=0 || y>=200) 
	{
		printf("0\n"); return;
	}
	
	//if there is no wall and door, xl will bigger than xh, we must modify
	if(xl > xh) 
	{
		printf("0\n"); return;
	}
	
	//initialize
	memset(final, 0, sizeof(final));
	memset(used, 0, sizeof(used));
	used[x][y] = 1;
	bfn[x][y] = 0;
	setfinal(0, 0);
	while(!myque.empty()) myque.pop();
	myque.push(x * 300 + y);

	//bfs
	while(!myque.empty())
	{
		z = myque.top(); myque.pop();
		x = z / 300; y = z % 300;
		if(x > xl && !wall[x][y][1] && !used[x-1][y])
		{
			if(door[x][y][1])
				bfn[x-1][y] = bfn[x][y] + 1;
			else bfn[x-1][y] = bfn[x][y];
			used[x-1][y] = 1;
			if(final[x-1][y])
			{
				flag = 1;
				ans = bfn[x-1][y];
				break;
			}
			myque.push((x-1)*300 + y);
		}
		if(y > yl && !wall[x][y][0] && !used[x][y-1])
		{
			if(door[x][y][0])
				bfn[x][y-1] = bfn[x][y] + 1;
			else bfn[x][y-1] = bfn[x][y];
			used[x][y-1] = 1;
			if(final[x][y-1])
			{
				flag = 1;
				ans = bfn[x][y-1];
				break;
			}
			myque.push(x*300 + y-1);
		}
		if(x < xh && !wall[x+1][y][1] && !used[x+1][y])
		{
			if(door[x+1][y][1])
				bfn[x+1][y] = bfn[x][y] + 1;
			else bfn[x+1][y] = bfn[x][y];
			used[x+1][y] = 1;
			if(final[x+1][y])
			{
				ans = bfn[x+1][y];
				flag = 1;
				break;
			}
			myque.push((x+1)*300 + y);
		}
		if(y < yh && !wall[x][y+1][0] && !used[x][y+1])
		{
			if(door[x][y+1][0])
				bfn[x][y+1] = bfn[x][y] + 1;
			else bfn[x][y+1] = bfn[x][y];
			used[x][y+1] = 1;
			if(final[x][y+1])
			{
				ans = bfn[x][y+1];
				flag = 1;
				break;
			}
			myque.push(x*300 + y+1);
		}
	}
	if(flag)
		printf("%d\n", ans);
	else printf("-1\n");
}

int main()
{
	while(read())
		process();	
	return 0;
}
