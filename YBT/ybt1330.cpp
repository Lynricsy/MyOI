#include <bits/stdc++.h>

using namespace std;

inline long long read()
{
    long long x = 0;
    int f = 1;
    char ch = getchar();
    while (ch < '0' || ch>'9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
void write(const long long& x)
{
    if (!x)
    {
        putchar('0');
        return;
    }
    char f[100];
    long long tmp = x;
    if (tmp < 0)
    {
        tmp = -tmp;
        putchar('-');
    }
    long long s = 0;
    while (tmp > 0)
    {
        f[s++] = tmp % 10 + '0';
        tmp /= 10;
    }
    while (s > 0)
    {
        putchar(f[--s]);
    }
}
inline double dread()
{
    double r;
    double x=0,t=0;
    int s=0,f=1;
    char c=getchar();
    for (;!isdigit(c);c=getchar())
    {
        if (c=='-')
        {
            f=-1;
        }
        if (c=='.')
        {
            goto readt;
        }
    }
    for (;isdigit(c)&&c!='.';c=getchar())
    {
        x=x*10+c-'0';
    }
    readt:
    for (;c=='.';c=getchar());
    for (;isdigit(c);c=getchar())
    {
        t=t*10+c-'0';
        ++s;
    }
    r=(x+t/pow(10,s))*f;
    return r;
}

inline void dwrite(long long x)
{
    if (x == 0)
    {
        putchar(48);
        return;
    }
    int bit[20], p = 0, i;
    for (; x; x /= 10) 
        bit[++p] = x % 10;
    for (i = p; i > 0; --i) 
        putchar(bit[i] + 48);
}
inline void write(double x,int k)
{
    static int n = pow(10, k);
    if (x == 0)
    {
        putchar('0');
        putchar('.');
        for (int i = 1; i <= k; ++i) 
            putchar('0');
        return;
    }
    if (x < 0) putchar('-'), x = -x;
    long long y = (long long) (x * n) % n;
    x = (long long) x;
    dwrite(x), putchar('.');
    int bit[10], p = 0, i;
    for (; p < k; y /= 10) 
        bit[++p] = y % 10;
    for (i = p; i > 0; i--) 
        putchar(bit[i] + 48);
}

long long startX,startY;
long long endX,endY;
struct Node
{
	long long x,y;
	long long step;
}Q[100090];
bool vis[109][109];
short mx[12]={2,-2,-2,2,1,2,2,1,-1,-2,-2,-1};
short my[12]={2,-2,-2,2,2,1,-1,-2,-2,-1,1,2};

void BFS1()
{
    memset(vis,0,sizeof(vis));
	long long head=1;
    long long tail=1;
	Q[head].x=startX;
	Q[head].y=startY;
	Q[head].step=0;
	++tail;
    vis[startX][startY]=true;
    while(head<tail)
    {
        long long x=Q[head].x;
        long long y=Q[head].y;
        long long s=Q[head].step;
        if(x==1&&y==1)
        {
            write(s);
            putchar('\n');
            return;
        }
        for(int i=0;i<12;++i)
        {
            long long nowX=x+mx[i];
            long long nowY=y+my[i];
            long long nowS=s+1;
            if(nowX>100||nowY>100||nowX<1||nowY<1||vis[nowX][nowY])
            {
                continue;
            }
            else
            {
                vis[nowX][nowY]=true;
                Q[tail].x=nowX;
                Q[tail].y=nowY;
                Q[tail].step=nowS;
                ++tail;
            }
        }
        ++head;
    }
}
void BFS2()
{
    memset(vis,0,sizeof(vis));
	long long head=1;
    long long tail=1;
	Q[head].x=endX;
	Q[head].y=endY;
	Q[head].step=0;
	++tail;
    vis[startX][startY]=true;
    while(head<tail)
    {
        long long x=Q[head].x;
        long long y=Q[head].y;
        long long s=Q[head].step;
        if(x==1&&y==1)
        {
            write(s);
            putchar('\n');
            return;
        }
        for(int i=0;i<12;++i)
        {
            long long nowX=x+mx[i];
            long long nowY=y+my[i];
            long long nowS=s+1;
            if(nowX>100||nowY>100||nowX<1||nowY<1||vis[nowX][nowY])
            {
                continue;
            }
            else
            {
                vis[nowX][nowY]=true;
                Q[tail].x=nowX;
                Q[tail].y=nowY;
                Q[tail].step=nowS;
                ++tail;
            }
        }
        ++head;
    }
}

int main()
{
	startX=read();
	startY=read();
	endX=read();
	endY=read();
	BFS1();
    BFS2();
    return 0;
}//LikiBlaze Code
