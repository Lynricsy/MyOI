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

const long long maxN = 100090;
long long totN;
long long X[maxN << 1];
long long totT;
long long totANS;
struct Line
{
	long long l, r, h;
	long long mark;
} lines[maxN << 1];
bool operator<(Line a, Line b)
{
	return a.h < b.h;
}
struct Node
{
	Node *lch, *rch;
	long long l, r, sum;
	long long len;

	// Node(long long L, long long R)
	// {
	// 	l = L;
	// 	r = R;
	// 	len = 0;
	// 	sum = 0;
	// 	if (L == R)
	// 		return;
	// 	long long Mid = (l + r) >> 1;
	// 	lch = new Node(L, Mid);
	// 	rch = new Node(Mid + 1, R);
	// }

	void push_up()
	{
		if (sum)
		{
			len = X[r + 1] - X[l];
		}
		else
		{
			len = lch->len + rch->len;
		}
	}

	void update(long long L, long long R, long long c)
	{
		if (X[l] >= R || X[r + 1] <= L)
		{
			return;
		}
		if (X[l] >= L && X[r + 1] <= R)
		{
			sum += c;
			push_up();
			return;
		}
		lch->update(L, R, c);
		rch->update(L, R, c);
		push_up();
	}
};
Node Mem[(maxN << 1) + 20];
Node *nowMEM = Mem;

Node *New(long long L, long long R)
{
	Node *anewd = ++nowMEM;
	anewd->l = L;
	anewd->r = R;
	anewd->len = 0;
	anewd->sum = 0;
	if (L == R)
	{
		return anewd;
	}
	long long Mid = (L + R) >> 1;
	anewd->lch = New(L, Mid);
	anewd->rch = New(Mid + 1, R);
    return anewd;
}

int main()
{
	totN = read();
	for (int i = 1, Xa, Ya, Xb, Yb; i <= totN; i++)
	{
		Xa = read();
		Ya = read();
		Xb = read();
		Yb = read();
		X[2 * i - 1] = Xa;
		X[2 * i] = Xb;
		lines[2 * i - 1] = {Xa, Xb, Ya, 1};
		lines[2 * i] = {Xa, Xb, Yb, -1};
	}
	totN <<= 1;
	sort(lines + 1, lines + totN + 1);
	sort(X + 1, X + totN + 1);
	totT = unique(X + 1, X + totN + 1) - (X + 1);
	Node *rot = New(1, totT - 1);
	for (int i = 1; i < totN; i++)
	{
		rot->update(lines[i].l, lines[i].r, lines[i].mark);
		totANS += rot->len * (lines[i + 1].h - lines[i].h);
	}
	write(totANS);
	return 0;
} //Thomitics Code