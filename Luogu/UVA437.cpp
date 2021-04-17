#include <bits/stdc++.h>
#define INF 999999999

using namespace std;

inline long long read()
{
	long long x = 0;
	int f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
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
void write(const long long &x)
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
	double x = 0, t = 0;
	int s = 0, f = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar())
	{
		if (c == '-')
		{
			f = -1;
		}
		if (c == '.')
		{
			goto readt;
		}
	}
	for (; isdigit(c) && c != '.'; c = getchar())
	{
		x = x * 10 + c - '0';
	}
readt:
	for (; c == '.'; c = getchar())
		;
	for (; isdigit(c); c = getchar())
	{
		t = t * 10 + c - '0';
		++s;
	}
	r = (x + t / pow(10, s)) * f;
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
inline void write(double x, int k)
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
	if (x < 0)
		putchar('-'), x = -x;
	long long y = (long long)(x * n) % n;
	x = (long long)x;
	dwrite(x), putchar('.');
	int bit[10], p = 0, i;
	for (; p < k; y /= 10)
		bit[++p] = y % 10;
	for (i = p; i > 0; i--)
		putchar(bit[i] + 48);
}

struct Block
{
	int x, y, z;
} blocks[109];
long long totB;
int totT;
struct PartedBlock
{
	int x, y, h, val;
} pblocks[109][4];
struct Edge
{
	int nxt, to;
} edges[100090];

long long DFS(int nowX, int rot, )
{
	if(pblocks[nowX][rot].val!=-1)
	{
		
	}
	int basex, basey;
	basex=pblocks[nowX][rot].x;
	basex=pblocks[nowX][rot].y;

}

int main()
{
	totT = read();
	for (int i = 1; i <= totT; i++)
	{
		totB = read();
		for (int i = 1, x, y, z; i <= totB; i++)
		{
			blocks[i].x = read();
			blocks[i].y = read();
			blocks[i].z = read();
		}
		for (int i = 1; i <= totB; ++i)
		{
			pblocks[i][1].x = blocks[i].x;
			pblocks[i][1].y = blocks[i].y;
			pblocks[i][1].h = blocks[i].z;
			pblocks[i][2].x = blocks[i].x;
			pblocks[i][2].y = blocks[i].z;
			pblocks[i][2].h = blocks[i].y;
			pblocks[i][3].x = blocks[i].z;
			pblocks[i][3].y = blocks[i].y;
			pblocks[i][3].h = blocks[i].x;
		}
	}

	return 0;
} //Thomitics Code