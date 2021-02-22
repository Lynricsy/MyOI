#include <bits/stdc++.h>

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

int totN;
int totM;
int mapp[59][59];
long long totR;
int maxS;
bool nowMAP[59][59];
long long Siz[2590];
long long nowS;
struct Node
{
	long long x, y;
	long long siz;
} Q[100090];
int mover[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

void BFS(int startX, int startY)
{
	long long head = 1;
	long long tail = 1;
	Q[head].siz = 1;
	Q[head].x = startX;
	Q[head].y = startY;
	++tail;
	nowMAP[startX][startY]=true;
	while (head < tail)
	{
		int x = Q[head].x;
		int y = Q[head].y;
		int s = Q[head].siz;
		for (int i = 0; i < 4; ++i)
		{
			int nowX = x + mover[i][0];
			int nowY = y + mover[i][0];
			int nowS = s + mover[i][0];
			if (nowMAP[nowX][nowY] || nowX < 1 || nowY < 1 || nowX > totM || nowY > totN)
			{
				continue;
			}
			else
			{
				Q[tail].x = nowX;
				Q[tail].y = nowY;
				Q[tail].siz = nowS;
				nowMAP[nowX][nowY]=true;
				++tail;
				maxS = max(nowS, maxS);
			}
		}
		++head;
	}
}
int main()
{
	totM=read();
	totN=read();
	for (int i = 1; i <= totM; ++i)
	{
		for (int j = 1; j <= totN; j++)
		{
			mapp[i][j] = read();
		}
	}
	for (int i = 1; i <= totM; ++i)
	{
		for (int j = 1; j <= totN; ++j)
		{
			if (!nowMAP[i][j])
			{
				++totR;
				BFS(i, j);
			}
		}
	}
	write(totR);
	putchar('\n');
	write(maxS);
	putchar('\n');
	return 0;
} //LikiBlaze Code