/**************************************************************
 * Problem: Luogu P4777
 * Author: 芊枫
 * Date: 2021 July 07
 * Algorithm: 莫队
**************************************************************/
#include <bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define IINF 0x3f3f3f3f

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

const long long maxN = 1000090;
long long totN;
long long totM;
long long totZ;
long long A[maxN];
long long B[maxN];
long long totQ;
long long MAX[maxN];
long long SIZE;
long long ANS[maxN];
long long inB(long long nowX)
{
	return ceil(nowX / SIZE);
}
struct Quest
{
	long long l, r;
	long long ID;
} query[maxN];
bool operator<(const Quest &a, const Quest &b)
{
	if (inB(a.l) == inB(b.l))
	{
		return a.r < b.r;
	}
	else
	{
		return a.l < b.l;
	}
}
struct Node
{
	long long l;
	long long r;
	Node *lch, *rch;
	long long val;
	long long tag;
	inline void pushup()
	{
		val = min(lch->val, rch->val);
	}
	Node(long long L, long long R)
	{
		l = L;
		r = R;
		tag = 0;
		if (l == r)
		{
			val = l;
			lch = rch = NULL;
			return;
		}
		long long Mid = (L + R) >> 1;
		lch = new Node(L, Mid);
		rch = new Node(Mid + 1, R);
		pushup();
	}
	void maketag(long long w)
	{
		val += w;
		tag += w;
	}
	void pushdown()
	{
		if (!tag)
		{
			return;
		}
		lch->maketag(tag);
		rch->maketag(tag);
		tag = 0;
	}
	inline bool INrange(long long L, long long R)
	{
		return (L <= l) && (r <= R);
	}
	inline bool OUTrange(long long L, long long R)
	{
		return (L > r) || (l > R);
	}
	void update(long long L, long long R, long long w)
	{
		if (INrange(L, R))
		{
			maketag(w);
		}
		else if (!OUTrange(L, R))
		{
			pushdown();
			lch->update(L, R, w);
			rch->update(L, R, w);
			pushup();
		}
	}
	long long query(long long L, long long R)
	{
		if (INrange(L, R))
		{
			return val;
		}
		else if (OUTrange(L, R))
		{
			return INF;
		}
		pushdown();
		return min(lch->query(L, R), rch->query(L, R));
	}
};

Node *rot;

void add(long long nowX)
{
	rot->update(1, MAX[nowX], 1);
}
void del(long long nowX)
{
	rot->update(1, MAX[nowX], -1);
}

int main()
{
	totN = read();
	totM = read();
	totZ = read();
	SIZE = (long long)(totN + 1.0) / sqrt(totM * 2 / 3.0);
	for (int i = 1; i <= totN; ++i)
	{
		A[i] = read();
	}
	sort(A + 1, A + totN + 1);
	for (int i = 1; i <= totM; ++i)
	{
		B[i] = read();
	}
	totQ = read();
	for (int i = 1; i <= totQ; ++i)
	{
		query[i].l = read();
		query[i].r = read();
		query[i].ID = i;
	}
	sort(query + 1, query + totQ + 1);
	for (int i = 1; i <= totM; ++i)
	{
		MAX[i] = upper_bound(A + 1, A + totN + 1, totZ - B[i]) - A - 1;
	}
	rot = new Node(1, totM);
	for (int i = 1, l = 1, r = 0; i <= totQ; ++i)
	{
		while (l > query[i].l)
		{
			add(--l);
		}
		while (r < query[i].r)
		{
			add(++r);
		}
		while (l < query[i].l)
		{
			del(l++);
		}
		while (r > query[i].r)
		{
			del(r--);
		}
		ANS[query[i].ID] = rot->query(1, totM) - 1;
	}
	for (int i = 1; i <= totQ; ++i)
	{
		write(ANS[i]);
		putchar('\n');
	}
	return 0;
} //Thomitics Code