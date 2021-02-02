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
const double Alpha=0.7;


struct Node
{
	Node *lch,*rch;
	long long val;
	long long size;
	long long cnt;
	bool deled;
	bool is_bad()
	{
		return (lch->cnt>Alpha*cnt+5)||(rch->cnt>Alpha*cnt+5);
	}
	void maintain()
	{
		size=!deled+lch->size+rch->size;
		cnt=lch->cnt+rch->cnt+1;
	}
	Node ()
	{
		val=0;
		size=0;
		cnt=0;
		deled=0;
		lch=rch=NULL;
	}
};

Node *null;

void DFS(Node* &o,vector<Node*> tempV)
{
	if(o==null)
	{
		return;
	}
	DFS(o->lch,tempV);
	if(!o->deled)
	{
		tempV.push_back(o);
	}
	DFS(o->rch,tempV);
	if(o->deled)
	{
		delete o;
	}
}

Node *build(vector<Node*> tempV,long long L,long long R)
{
	if(L>=R)
	{
		return null;
	}
	long long Mid=(L+R)>>1;
	Node *o=tempV[Mid];
	o->lch=build(tempV,L,Mid);
	o->rch=build(tempV,Mid+1,R);
	o->maintain();
	return o;
}

void rebuild(Node *o)
{
	vector<Node*> tempV;
	DFS(o,tempV);
	build(tempV,0,tempV.size());
}

void insert(long long x,Node* &o)
{
	if(o==null)
	{
		o=new Node;
		o->lch=o->rch=null;
		o->cnt=o->size=1;
		o->val=x;
		o->deled=false;
		return;
	}
	else
	{
		++o->size;
		++o->cnt;
		if(x>=o->val)
		{
			insert(x,o->rch);
		}
		else
		{
			insert(x,o->lch);
		}
		if(o->is_bad())
		{
			rebuild(o);
		}
	}
}
long long Rank(Node *o,long long x)
{
	int ans=1;
	while (o!=null)
	{
		if (o->val>=x)
		{
			o=o->lch;
		}
		else
		{
			ans+=o->lch->size+!o->deled;
			o=o->rch;
		}
	}
	return ans;
}
long long Kth(Node *o,long long k)
{
	while(o!=null)
	{
		if(!o->deled&&o->lch->size+1==k)
		{
			return o->val;
		}
		if(o->lch->size>=k)
		{
			o=o->lch;
		}
		else
		{
			k-=o->lch->size+!o->deled;
			o=o->rch;
		}
	}
}
void erase(Node *o,long long rank)
{
	if (!o->deled&&rank==o->lch->size+1)
	{
		o->deled=1;
		--o->size;
		return;
	}
	--o->size;
	if (rank<=o->lch->size+!o->deled)
	{
		erase(o->lch,rank);
	}
	else
	{
		erase(o->rch,rank-o->lch->size-!o->deled);
	}
}

Node *rot;

int main()
{
	null=new Node;
	totN=read();
	rot=null;
	for(long long i=1;i<=totN;++i)
	{
		char opt;
		long long x;
		opt=getchar();
		x=read();
		if(opt=='1')
		{
			insert(x,rot);
		}
		else if (opt=='2')
		{
			erase(rot,Rank(rot,x));
		}
		else if(opt=='3')
		{
			write(Rank(rot,x));
			putchar('\n');
		}
		else if (opt=='4')
		{
			write(Kth(rot,x));
			putchar('\n');
		}
		else if (opt=='5')
		{
			write(Kth(rot,Rank(rot,x))-1);
			putchar('\n');
		}
		else if (opt=='6')
		{
			write(Kth(rot,Rank(rot,x)+1));
			putchar('\n');
		}
	}
    return 0;
}//LikiBlaze Code
