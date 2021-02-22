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

long long totN;
long long totM;
long long head[100090];
long long cnt_edges;
bool color[100090];
int block_color[100090][2];
bool den[100090];
int cnt_blocks;
int DP[2090][2090];
long long RESULT;
struct Edge
{
	long long nxt;
	long long to;
}edges[100090];
void add_edge(long long x,long long y)
{
	++cnt_edges;
	edges[cnt_edges].nxt=head[x];
	head[x]=cnt_edges;
	edges[cnt_edges].to=y;
}

void DFS(int nowX,bool col,int now_block)
{
	if (den[nowX])
	{
		return;
	} else
	{
		den[nowX] = true;
		col[nowX] = col;
		++block_color[now_block][col];
		for (int i = head[x]; i; i = edges[i].nxt)
		{
			DFS(edges[i].to, col ^ 1, now_block);
		}
	}
}

int main()
{
	totN=read();
	totM=read();
	for (int i = 1,x,y; i <= totM; ++i)
	{
		x=read();
		y=read();
		add_edge(x,y);
		add_edge(y,x);
		/*
		if ((!color[x])&&(!color[y]))
		{
			color[x]=1;
			color[y]=0;
		}
		 */
		
	}
	for (int i = 1; i <= totN; ++i)
	{
		if (!den[i])
		{
			++cnt_blocks;
			DFS(i, 1, cnt_blocks);
		}
		for (int j = totN; j >=1 ; --j)
		{
			if (j>=block_color[cnt_blocks][1]&&DP[cnt_blocks-1][block_color[cnt_blocks][1]])
			{
				DP[cnt_blocks][j]=true;
			}
			if (j>=block_color[cnt_blocks][0]&&DP[cnt_blocks-1][block_color[cnt_blocks][0]])
			{
				DP[cnt_blocks][j]=true;
			}
		}
	}
	for (int i = 1; i <= totN; ++i)
	{
		RESULT=max(RESULT,i*(totN-i)-totM);
	}
	write(RESULT);
	return 0;
}//LikiBlaze Code