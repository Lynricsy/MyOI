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

struct Node
{
	Node *lch, *rch;
	int val, size;
	Node(int key)
    {
	    lch=rch=NULL;
	    size=1;
	    val=key;
    }
}rot(0);

void L_rotate(Node *x)
{
	Node *y = x->lch;
	x->rch = y->lch;
	y->lch = x;
	y->size = x->size;
	x->size = x->lch->size + x->rch->size + 1;
	x = y;
}

void R_rotate(Node *x)
{
	Node *y = x->lch;
	x->lch = y->rch;
	y->rch = x;
	y->size = x->size;
	x->size = x->lch->size + x->rch->size + 1;
	x = y;
}

void maintain(Node *x,bool flag)
{
    if (flag== false)
    {
        if (x->lch->lch->size>x->rch->size)
        {
            R_rotate(x);
        } else if (x->lch->rch->size>x->rch->size)
        {
            R_rotate(x->lch);
            R_rotate(x);
        } else
        {
            return;
        }
    } else
    {
        if (x->rch->rch->size>x->lch->size)
        {
            L_rotate(x);
        } else if (x->rch->lch->size>x->lch->size)
        {
            R_rotate(x->rch);
            R_rotate(x);
        } else
        {
            return;
        }
    }
    maintain(x->lch, false);
    maintain(x->rch, true);
    maintain(x, true);
    maintain(x, false);
}

void insert(Node *x,int keys)
{
	if (x == NULL)
	{
		x = new Node(keys);
	} else
	{
		x->size++;
		if (keys < x->val)
		{
			insert(x->lch, keys);
		} else
		{
			insert(x->rch, keys);
		}
		maintain(x, keys >= x->val);
	}
}

int remove(Node *x,int keys)
{
	int dekey;
	--x->size;
	if ((keys==x->val)||(keys<x->val&&x->lch==NULL)||(keys>x->val&&x->rch==NULL))
	{
		dekey=x->val;
		if (x->lch&&x->rch)
		{
			x->val=remove(x->lch,x->val+1);
		} else
		{
			if (x->lch==NULL)
			{
				x=x->rch;
			} else if (x->rch==NULL)
			{
				x=x->lch;
			} else
			{
				x=NULL;
			}
		}
	} else if (keys>x->val)
	{
		dekey=remove(x->rch,keys);
	} else if (keys<x->val)
	{
		dekey=remove(x->rch,keys);
	}
	return dekey;
}


int get_min()
{
	Node *x;
	for (x = &rot; x->lch; x=x->lch);
	return x->val;
}
int get_max()
{
	Node *x;
	for (x = &rot; x->rch; x=x->rch);
	return x->val;
}
int find_Kth(Node *x,int K)
{
	int tr=x->lch->size+1;
	if (tr==K)
	{
		return x->val;
	} else if (tr<K)
	{
		return find_Kth(x->rch,K-tr);
	} else
	{
		return find_Kth(x->lch,K);
	}
}

int main()
{
	return 0;
} // LikiBlaze Code