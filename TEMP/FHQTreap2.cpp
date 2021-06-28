#include <bits/stdc++.h>
#define INF 999999999
#define arand() rand() % 114514

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

long long totN;

const long long maxN = 100090;
struct Node
{
	long long lch, rch;
	long long siz, val;
	long long rnd;
} nodes[maxN];

long long X, Y, Z;
long long rot;

void split(long long splitX, long long K, long long &Xtree, long long &Ytree)
{
	if (!splitX)
	{
		Xtree = Ytree = 0;
	}
	else
	{
		if (nodes[splitX].val <= K)
		{
			Xtree = splitX;
			split(nodes[splitX].rch, K, nodes[splitX].lch, Ytree);
		}
		else
		{
			Ytree = splitX;
			split(nodes[splitX].lch, K, Xtree, nodes[splitX].lch);
		}
	}
}

void update(long long updX)
{
	nodes[updX].siz = nodes[nodes[updX].lch].siz + nodes[nodes[updX].rch].siz + 1;
}
long long merge(long long Xtree, long long Ytree)
{
	if (!Xtree || !Ytree)
	{
		return Xtree + Ytree;
	}
	else if (nodes[Xtree].rnd <= nodes[Ytree].rnd)
	{
		nodes[Xtree].rch = merge(nodes[Xtree].rch, Ytree);
		update(Xtree);
		return Xtree;
	}
	else
	{
		nodes[Ytree].lch = merge(Xtree, nodes[Xtree].lch);
		update(Ytree);
		return Ytree;
	}
}

long long Kth(long long nowX, long long K)
{
	while (1)
	{
		if (nodes[nodes[nowX].lch].siz + 1 == K)
		{
			return nowX;
		}
		else if (K > nodes[nodes[nowX].lch].siz)
		{
			K -= nodes[nodes[nowX].lch].siz + 1;
			nowX = nodes[nowX].rch;
		}
		else
		{
			nowX = nodes[nowX].lch;
		}
	}
}

void del(long long nowX)
{
	split(rot, nowX, X, Z);
	split(X, nowX - 1, X, Y);
	Y = merge(nodes[nowX].lch, nodes[nowX].rch);
	merge(merge(X, Y), Z);
}


int main()
{

	return 0;
} //Thomitics Code