#include <cstdio>

const int maxn = 100005;

typedef long long int ll;

int n, q;
ll a[maxn];

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

struct Node
{
	ll tag, v;
	int l, r;
	Node *ls, *rs;
	int xorsums;
	inline void maketag(const ll w)
	{
		v += (r - l + 1) * w;
		tag += w;
	}
	inline void pushup()
	{
		v = ls->v ^ rs->v;
	}
	inline void pushdown()
	{
		if (tag == 0)
			return;
		ls->maketag(tag);
		rs->maketag(tag);
		tag = 0;
	}
	Node(const int L, const int R)
	{
		l = L;
		r = R;
		if (l == r)
		{
			tag = 0;
			v = a[l];
			ls = rs = NULL;
		}
		else
		{
			tag = 0;
			int M = (L + R) >> 1;
			ls = new Node(L, M);
			rs = new Node(M + 1, R);
			pushup();
		}
	}
	inline bool InRange(const int L, const int R)
	{
		return (L <= l) && (r <= R);
	}
	inline bool OutofRange(const int L, const int R)
	{
		return (l > R) || (r < L);
	}
	void upd(const int L, const int R, const ll w)
	{
		if (InRange(L, R))
		{
			maketag(w);
		}
		else if (!OutofRange(L, R))
		{
			pushdown();
			ls->upd(L, R, w);
			rs->upd(L, R, w);
			pushup();
		}
	}
	ll qry(const int L, const int R)
	{
		if (InRange(L, R))
			return v;
		if (OutofRange(L, R))
			return 0;
		pushdown();
		return ls->qry(L, R) + rs->qry(L, R);
	}
};

int main()
{
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; ++i)
		scanf("%lld", a + i);
	Node *rot = new Node(1, n);
	for (int i = 1; i <= q; i++)
	{
		int p = read();
		int x = read();
	}
	return 0;
}
