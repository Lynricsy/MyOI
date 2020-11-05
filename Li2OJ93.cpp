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
char nums[2][100090];
char lies[100090];

char findnum(int x,int y,int z)
{
	if(x==0&&y==1&&z==2)
	{
		return 3;
	}
	if(x==0&&y==0&&z==2)
	{
		return 2;
	}
	if(x==1&&y==1&&z==3)
	{
		return 3;
	}
	if(x==0&&y==0&&z==1)
	{
		return 1;
	}
	if(x==2&&y==2&&z==3)
	{
		return 3;
	}
	if(x==0&&y==0&&z==0)
	{
		return 3;
	}
	if(x==1&&y==1&&z==1)
	{
		return 2;
	}
	if(x==2&&y==2&&z==2)
	{
		return 1;
	}
	if(x==3&&y==3&&z==3)
	{
		return 0;
	}
	swap(x,y);
	if(x==0&&y==1&&z==2)
	{
		return 3;
	}
	if(x==0&&y==0&&z==2)
	{
		return 2;
	}
	if(x==1&&y==1&&z==3)
	{
		return 3;
	}
	if(x==0&&y==0&&z==1)
	{
		return 1;
	}
	if(x==2&&y==2&&z==3)
	{
		return 3;
	}
	if(x==0&&y==0&&z==0)
	{
		return 3;
	}
	if(x==1&&y==1&&z==1)
	{
		return 2;
	}
	if(x==2&&y==2&&z==2)
	{
		return 1;
	}
	if(x==3&&y==3&&z==3)
	{
		return 0;
	}
	swap(y,z);
	if(x==0&&y==1&&z==2)
	{
		return 3;
	}
	if(x==0&&y==0&&z==2)
	{
		return 2;
	}
	if(x==1&&y==1&&z==3)
	{
		return 3;
	}
	if(x==0&&y==0&&z==1)
	{
		return 1;
	}
	if(x==2&&y==2&&z==3)
	{
		return 3;
	}
	if(x==0&&y==0&&z==0)
	{
		return 3;
	}
	if(x==1&&y==1&&z==1)
	{
		return 2;
	}
	if(x==2&&y==2&&z==2)
	{
		return 1;
	}
	if(x==3&&y==3&&z==3)
	{
		return 0;
	}
	swap(x,y);
	if(x==0&&y==1&&z==2)
	{
		return 3;
	}
	if(x==0&&y==0&&z==2)
	{
		return 2;
	}
	if(x==1&&y==1&&z==3)
	{
		return 3;
	}
	if(x==0&&y==0&&z==1)
	{
		return 1;
	}
	if(x==2&&y==2&&z==3)
	{
		return 3;
	}
	if(x==0&&y==0&&z==0)
	{
		return 3;
	}
	if(x==1&&y==1&&z==1)
	{
		return 2;
	}
	if(x==2&&y==2&&z==2)
	{
		return 1;
	}
	if(x==3&&y==3&&z==3)
	{
		return 0;
	}
	swap(x,z);
	if(x==0&&y==1&&z==2)
	{
		return 3;
	}
	if(x==0&&y==0&&z==2)
	{
		return 2;
	}
	if(x==1&&y==1&&z==3)
	{
		return 3;
	}
	if(x==0&&y==0&&z==1)
	{
		return 1;
	}
	if(x==2&&y==2&&z==3)
	{
		return 3;
	}
	if(x==0&&y==0&&z==0)
	{
		return 3;
	}
	if(x==1&&y==1&&z==1)
	{
		return 2;
	}
	if(x==2&&y==2&&z==2)
	{
		return 1;
	}
	if(x==3&&y==3&&z==3)
	{
		return 0;
	}
	cout<<"aaaaaaaaaaaaaaaaa"<<endl;
	return rand()%3+1;
}

bool flag[10];

int change(int a, int b, int c)
{
    for (int i = 0; i < 4; i++)
        flag[i] = 0;
    flag[a]++;
    flag[b]++;
    flag[c]++;
    for (int i = 0; i < 4; i++)
    {
        if (flag[i] == 3)
        {
            return 3 - i;
        }
        if (flag[i] == 2)
        {
            for (int j = 0; j < 4; j++)
            {
                if (flag[j] == 1)
                {
                    if (1 + j == 3)
                       return i;
                    else
                        return j;
                }
            }
        }
    }
}



bool nowpos;

int main()
{
	totN=read();
	totM=read();
	for(int i=1;i<=totM;++i)
	{
		nums[0][i]=read();
	}
	lies[1]=nums[0][1];
	for(int i=2;i<=totN;++i)
	{
		lies[i]=read();
	}
	for(int i=2;i<=totN;++i)
	{
		nums[nowpos^1][1]=lies[i];
		for(int j=2;j<=totM;++j)
		{
			nums[nowpos^1][j]=change(nums[nowpos][j-1],nums[nowpos][j],nums[nowpos^1][j-1]);
		}
		nowpos^=1;
	}
	if(nums[nowpos][totM]==0)
	{
		putchar('H');
		putchar('S');
	}
	if(nums[nowpos][totM]==1)
	{
		putchar('T');
		putchar('S');
	}
	if(nums[nowpos][totM]==2)
	{
		putchar('H');
		putchar('P');
	}
	if(nums[nowpos][totM]==3)
	{
		putchar('T');
		putchar('P');
	}
    return 0;
} //ROSMONTIS Code

