#include<bits/stdc++.h>

using namespace std;

long long read()
{
	long long x=0;
	int f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0')
	{
		if(ch=='-')
		{
			f=-1;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
/*
void write(long long x)
{
	if(!x)
	{
		putchar('0');
		return;
	}
	char f[109];
	long long tmp=x;
	if(x<0)
	{
		x=-x;
		putchar('-');
	}
	int c=0;
	long long a=x-(x/10)*10;s
	while(x)
	{
		f[c]=x%10;
		x/=10;
	}
}
*/

int totQ;
long long r;
int mdays[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};

struct Times
{
	int day;
	int month;
	long long year;
	bool NA;
};
void print_time(Times printing)
{
	printf("%d",printing.day);
	putchar(' ');
	printf("%d",printing.month);
	putchar(' ');
	printf("%lld",printing.year);
	if(printing.NA)
	{
		putchar(' ');
		putchar('B');
		putchar('C');
	}
}

int date_dfter_get_month;

int get_month(int num,bool ruin)
{
	if(num<=31)
	{
		date_dfter_get_month=num+1;
		return 1;
	}
	num-=31;
	if(ruin)
	{
		if(num<=29)
		{
			date_dfter_get_month=num;
			return 2;
		}
		num-=29;
	}
	else
	{
		if(num<=28)
		{
			date_dfter_get_month=num;
			return 2;
		}
		num-=28;
	}
	if(num<=31)
	{
		date_dfter_get_month=num;
		return 3;
	}
	num-=31;
	if(num<=30)
	{
		date_dfter_get_month=num;
		return 4;
	}
	num-=30;
	if(num<=31)
	{
		date_dfter_get_month=num;
		return 5;
	}
	num-=31;
	if(num<=30)
	{
		date_dfter_get_month=num;
		return 6;
	}
	num-=30;
	if(num<=31)
	{
		date_dfter_get_month=num;
		return 7;
	}
	num-=31;
	if(num<=31)
	{
		date_dfter_get_month=num;
		return 8;
	}
	num-=31;
	if(num<=30)
	{
		date_dfter_get_month=num;
		return 9;
	}
	num-=30;
	if(num<=31)
	{
		date_dfter_get_month=num;
		return 10;
	}
	num-=31;
	if(num<=30)
	{
		date_dfter_get_month=num;
		return 11;
	}
	num-=30;
	if(num<=31)
	{
		date_dfter_get_month=num;
		return 12;
	}
	num-=31;
	return 1;
}

Times calctime(long long calcing)
{
	Times RESULT;
	long long tmp=0;
	tmp=calcing/1461;
	bool final_year_class=0;
	if(tmp<1178)
	{
		RESULT.NA=true;
		calcing-=tmp*1461;
		int tmp_978df98e48;
		tmp_978df98e48=calcing/365;
		RESULT.year=4713-tmp*4-tmp_978df98e48;
		if(calcing<365)
		{
			final_year_class=true;
		}
		RESULT.month=get_month(calcing-tmp_978df98e48*365,final_year_class);
		RESULT.day=date_dfter_get_month;
		return RESULT;
	}
	else
	{
		calcing-=1178*1461;
		if(calcing<365)
		{
			RESULT.NA=true;
			RESULT.year=1;
			RESULT.month=get_month(calcing,true);
			RESULT.day=date_dfter_get_month;
			return RESULT;
		}//1580:395//4:1461  ancient//577095//577825
		else//+274
		{
			if(578102>calcing)
			{
				tmp=calcing/1461;
				RESULT.NA=false;
				calcing-=tmp*1461;
				int tmp_978df98e48;
				tmp_978df98e48=calcing/365;
				RESULT.year=tmp*4+tmp_978df98e48;
				if(1095<calcing)
				{
					final_year_class=true;
				}
				RESULT.month=get_month(calcing-tmp_978df98e48*365,final_year_class);
				RESULT.day=date_dfter_get_month;
				return RESULT;
			}
			else
			{
				calcing-=578112;
				if(calcing<78)
				{
					RESULT.year=1582;
					if(calcing<=16)
					{
						RESULT.month=10;
						RESULT.day=calcing;
					}
					else if(calcing<=46)
					{
						RESULT.month=11;
						RESULT.day=calcing-16;
					}
					else
					{
						RESULT.month=12;
						RESULT.day=calcing-46;
					}
				}
				else
				{
					calcing-=77;
					if(calcing<731)
					{
						if(calcing<365)
						{
							RESULT.year=1583;
							RESULT.month=get_month(calcing,true);
							RESULT.day=date_dfter_get_month;
						}
						else
						{
							calcing-=365;
							RESULT.year=1584;
							RESULT.month=get_month(calcing,true);
							RESULT.day=date_dfter_get_month;
						}
					}
					else
					{
						calcing-=731;
						int tmp4=calcing/1461;
						if(tmp4<=3)
						{
							calcing-=tmp4*1461;
							if(calcing<1095)
							{
								int aaayear=calcing/365;
								calcing-=aaayear*365;
								RESULT.year=aaayear+1584+tmp4*4;
								RESULT.month=get_month(calcing,false);
								RESULT.day=date_dfter_get_month;
							}
							else
							{
								calcing-=1095;
								RESULT.year=1+1584+tmp4*4;
								RESULT.month=get_month(calcing,true);
								RESULT.day=date_dfter_get_month;
							}
						}
						else
						{
							calcing-=1461*4;
							int tmp100=calcing/36503;
							RESULT.year=1584+tmp100*100;
							calcing-=36503*tmp100;
							bool ___100=0;
							if(36503*(tmp100)+1-calcing<365)
							{
								___100=1;
							}
							tmp4=calcing/1461;
							if(calcing<1095)
							{
								int aaayear=calcing/365;
								calcing-=aaayear*365;
								RESULT.year=aaayear+1584+tmp100*100+tmp4*4;
								RESULT.month=get_month(calcing,false);
								RESULT.day=date_dfter_get_month;
							}
							else
							{
								calcing-=1095;
								RESULT.year+=tmp4*4;
								if(___100)
								{
									RESULT.month=get_month(calcing,false);
								}
								else
								{
									RESULT.month=get_month(calcing,true);
								}
								RESULT.day=date_dfter_get_month;
							}
						}
					}
				}
			}
		}
	}
	return RESULT;
}

int main()
{
	//freopen("jilian.in","r",stdin);
	//freopen("jilian.out","w",stdout);
	totQ=read();
	for(register int i=1;i<=totQ;++i)
	{
		r=read();
		print_time(calctime(r));
		putchar('\n');
	}
	return 0;
}
