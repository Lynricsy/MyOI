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

long long totM;
long long totN;
long long nums[100090];

struct Node
{
	long long val;
	Node *lch, *rch;
	long long tag;
	int l, r;

	void push_up()
	{
		val = lch->val + rch->val;
	}

	void make_tag(long long w)
	{
		val += (l - r + 1) * w;
		tag += w;
	}

	void push_down()
	{
		if (!tag)
		{
			return;
		}
		lch->make_tag(tag);
		rch->make_tag(tag);
		tag = 0;
	}

	Node(int L, int R)
	{
		l = L;
		r = R;
		if (L == R)
		{
			val = nums[l];
			tag = 0;
			lch = rch = NULL;
		} else
		{
			int M = (L + R) >> 1;
			lch = new Node(L, M);
			rch = new Node(M + 1, R);
			tag = 0;
			push_up();
		}
	}

	bool out_of_range(int L, int R)
	{
		return (r < L) || (l > R);
	}

	bool in_range(int L, int R)
	{
		return (l >= L) && (r <= R);
	}

	void update(int L, int R, long long w)
	{
		if (in_range(L, R))
		{
			make_tag(w);
		} else if (!out_of_range(L, R))
		{
			push_down();
			lch->update(L, R, w);
			rch->update(L, R, w);
			push_up();
		}
	}

	long long query(int L, int R)
	{
		if (in_range(L, R))
		{
			return val;
		}
		if (out_of_range(L, R))
		{
			return 0;
		}
		push_down();
		return lch->query(L, R) + rch->query(L, R);
	}
};

int main()
{
	totN=read();
	totM=read();
	for (int i = 1; i <= totN; ++i)
	{
		nums[i]=read();
	}
	for (int i = 0; i < totM; ++i)
	{

	}
	return 0;
} //Thomitics Code