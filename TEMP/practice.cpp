#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <queue>
#include <string>
#include <stack>
#include <ctime>
using namespace std;
int money=100;
int t=0;
int tt=-1;
int v;
int d;
void borrow()
{
    if(tt!=-1)
    {
        cout<<"你现在不能借钱"<<endl;
        return;
    }
    cout<<"你要借多少钱？"<<endl;
    cin>>v;
    if (d==1||d==2)
    {
        if (v>1000) cout<<"你不能借这么多钱！"<<endl,cout<<"你要借多少钱？"<<endl,cin>>v;
        if (v<=1000) money+=v,cout<<"10天以后你要还"<<2*v<<"美元"<<endl;
        return;
    }
    else
    {
        if (v>100) cout<<"你不能借这么多钱！"<<endl,cout<<"你要借多少钱？"<<endl,cin>>v;
        if (v<=100) money+=v,cout<<"10天以后你要还"<<2*v<<"美元"<<endl;
        return;
    }
}
bool pay()
{
    cout<<"你现在要还 "<<2*v<<endl;
    money-=2*v;
    tt=-1;
    v=0;
    if(money<=0) return false;
    else return true;
}
int main(int argc, char *argv[])
{
    cout<<"欢迎来到彩票游戏！"<<endl<<endl<<"温馨提示：在游戏内请勿使用小数、负数、英文字母、特殊字符（游戏中另说明除外），"<<endl<<"否则后果自负。"<<endl<<endl;
    cout<<"请选择难度(输入序号即可):"<<endl<<"1:入门"<<" "<<"2:简单"<<" "<<"3:普通"<<" "<<"4:中等"<<" "<<"5:困难"<<endl;
    cin>>d;
    if (d==1) cout<<"已选择难度:入门"<<endl<<endl;
    if (d==2) cout<<"已选择难度:简单"<<endl<<endl;
    if (d==3) cout<<"已选择难度:普通"<<endl<<endl;
    if (d==4) cout<<"已选择难度:中等"<<endl<<endl;
    if (d==5) cout<<"已选择难度:困难"<<endl<<endl;
    while(1)
    {
        if (d<1) cout<<"没有这个选项"<<endl<<"请选择难度(输入序号即可):"<<endl<<"1:入门"<<" "<<"2:简单"<<" "<<"3:普通"<<" "<<"4:中等"<<" "<<"5:困难"<<endl,cin>>d;
        if (d>5) cout<<"没有这个选项"<<endl<<"请选择难度(输入序号即可):"<<endl<<"1:入门"<<" "<<"2:简单"<<" "<<"3:普通"<<" "<<"4:中等"<<" "<<"5:困难"<<endl,cin>>d;
        if (d==1 || d==2 || d==3 || d==4 || d==5) break;
    }
    bool flag=true;
    srand(time(0));
    int a[10000];
    int n,p;
    char c[4];
    if (d==1)
    {
        cout<<"每张彩票 购入价为1美元，出售价为5美元，有五个奖项"<<endl<<"小奖：10美元"<<endl<<"中奖：20美元"<<endl<<"大奖：100美元"<<endl<<"巨额奖金：1,000美元"<<endl<<"杰克壶：10,000美元"<<endl;
        cout<<"你有100美元，当你赚了超过10,000美元，你就发财了。"<<endl<<"但如果你失去了所有的钱，你破产了。"<<endl;
        cout<<"你可能想借钱（最多1,000美元），如果你想，按0。"<<endl<<"请记住，当你借了十天以后。你必须偿还两倍，"<<endl;
        cout<<"你想买彩票还是卖彩票？（buy/sell）"<<endl;
    }
    if (d==2)
    {
        cout<<"每张彩票 购入价为2美元，出售价为3美元，有五个奖项"<<endl<<"小奖：5美元"<<endl<<"中奖：20美元"<<endl<<"大奖：100美元"<<endl<<"巨额奖金：1,000美元"<<endl<<"杰克壶：10,000美元"<<endl;
        cout<<"你有100美元，当你赚了超过10,000美元，你就发财了。"<<endl<<"但如果你失去了所有的钱，你破产了。"<<endl;
        cout<<"你可能想借钱（最多1,000美元），如果你想，请按0。"<<endl<<"请记住，当你借了十天以后。你必须偿还两倍，"<<endl;
        cout<<"你想买彩票还是卖彩票？（buy/sell）"<<endl;
    }
    if (d==3)
    {
        cout<<"每张彩票 售价2美元，有五个奖项"<<endl<<"小奖：5美元"<<endl<<"中奖：20美元"<<endl<<"大奖：100美元"<<endl<<"巨额奖金：1,000美元"<<endl<<"杰克壶：10,000美元"<<endl;
        cout<<"你有100美元，当你赚了超过10,000美元，你就发财了。"<<endl<<"但如果你失去了所有的钱，你破产了。"<<endl;
        cout<<"你可能想借钱（最多100美元），如果你想，请按0。"<<endl<<"请记住，当你借了十天以后。你必须偿还两倍，"<<endl;
        cout<<"你想买彩票还是卖彩票？（buy/sell）"<<endl;
    }
    if (d==4)
    {
        cout<<"每张彩票 售价3美元，有五个奖项"<<endl<<"小奖：5美元"<<endl<<"中奖：20美元"<<endl<<"大奖：100美元"<<endl<<"巨额奖金：1,000美元"<<endl<<"杰克壶：10,000美元"<<endl;
        cout<<"你有100美元，当你赚了超过100,000美元，你就发财了。"<<endl<<"但如果你失去了所有的钱，你破产了。"<<endl;
        cout<<"你可能想借钱（最多100美元），如果你想，请按0。"<<endl<<"请记住，当你借了七天以后。你必须偿还两倍，"<<endl;
        cout<<"你想买彩票还是卖彩票？（buy/sell）"<<endl;
    }
    if (d==5)
    {
        cout<<"每张彩票 购入价为5美元，出售价为2美元，有五个奖项"<<endl<<"小奖：5美元"<<endl<<"中奖：20美元"<<endl<<"大奖：100美元"<<endl<<"巨额奖金：1,000美元"<<endl<<"杰克壶：5,000美元"<<endl;
        cout<<"你有100美元，当你赚了超过100,000美元，你就发财了。"<<endl<<"但如果你失去了所有的钱，你就破产了。"<<endl;
        cout<<"你可能想借钱（最多100美元），如果你想，请按0。"<<endl<<"请记住，当你借了五天以后。你必须偿还两倍，"<<endl;
        cout<<"你想买彩票还是卖彩票？（buy/sell）"<<endl;
    }
    cin>>c;
    if(c[0]=='b'||c[0]=='B')
    {
        while(money>0)
        {
            if (d==1||d==2||d==3) if(money>=10000)
                {
                    cout<<"你发财了! "<<endl;
                    cout<<"你花了 "<<t<<"天"<<endl;
                    system("pause");
                    return 0;
                }
            if (d==4||d==5) if(money>=100000)
                {
                    cout<<"你发财了! "<<endl;
                    cout<<"你花了 "<<t<<"天"<<endl;
                    system("pause");
                    return 0;
                }
            t++;
            cout<<"你要买几张票？"<<" "<<"你有$"<<money<<endl;
            cin>>n;
            if(n==0)
            {
                if (d=4)
                {
                    borrow();
                    tt=t+7;
                }
                if (d=5)
                {
                    borrow();
                    tt=t+5;
                }
                else
                {
                    borrow();
                    tt=t+10;
                }
            }
            if(t==tt)
            {
                flag=pay();
            }
            if(t==tt-1) cout<<"[警告]你必须在明天还钱！"<<endl;
            if(flag==false)
            {
                cout<<"你不能偿还你借的钱！"<<endl;
                cout<<"你破产了。"<<endl;
                cout<<"你生存了"<<t<<"天。"<<endl;
                system("pause");
                return 0;
            }
            flag=true;
            if(n<0)
            {
                cout<<"因为你违反规则，所以系统强制停止了你的游戏"<<endl;
                system("pause");
            }
            if (d==1) money=money-n;
            if (d==2||d==3) money=money-n*2;
            if (d==4) money=money-n*3;
            if (d==5) money=money-n*5;
            if(money<0)
            {
                cout<<"你破产了。"<<endl;
                cout<<"你生存了"<<t<<"天"<<endl;
                system("pause");
                return 0;
            }
            for(int i=0; i<n; i++)
            {
                p=rand()%12000;
                if(p==0)
                {
                    int q=0;
                    q=rand()%4;
                    if(q==1)
                    {
                        cout<<"你获得了杰克壶！"<<endl;
                        if (d==5) money+=5000;
                        else money+=10000;
                    }
                }
                else if(p>=1&&p<=8)
                {
                    int g=0;
                    g=rand()%2;
                    if(g==0)
                    {
                        cout<<"你获得了巨额奖金！ "<<endl;
                        money+=1000;
                    }
                }
                else if(p>=9&&p<=99)
                {
                    cout<<"你获得了大奖！"<<endl;
                    money+=100;
                }
                else if((p>=100&&p<=399)||(p>1500&&p<=1600))
                {
                    cout<<"你获得了中间奖！"<<endl;
                    money+=20;
                }
                else if(p>=400&&p<=1500)
                {
                    cout<<"你获得了小奖！"<<endl;
                    if (d==1) money+=10;
                    else money+=5;
                }
            }
            if(money<=0)
            {
                cout<<"你破产了。"<<endl;
                cout<<"你生存了"<<t<<"天。"<<endl;
                system("pause");
                return 0;
            }
        }
    }
    if(c[0]=='s'||c[0]=='S')
    {
        if (d==1)
        {
            cout<<"你有$"<<money<<endl;
            cout<<"你必须付25美元买一个商店。 "<<endl;
            cout<<"你只能卖同样数量的票作为你的钱。 "<<endl;
            money-=25;
        }
        if (d==2)
        {
            cout<<"你有$"<<money<<endl;
            cout<<"你必须付35美元买一个商店。 "<<endl;
            cout<<"你只能卖同样数量的票作为你的钱。 "<<endl;
            money-=35;
        }
        if (d==3||d==4)
        {
            cout<<"你有$"<<money<<endl;
            cout<<"你必须付50美元买一个商店。 "<<endl;
            cout<<"你只能卖同样数量的票作为你的钱。 "<<endl;
            money-=50;
        }
        if (d==5)
        {
            cout<<"你有$"<<money<<endl;
            cout<<"你必须付60美元买一个商店。 "<<endl;
            cout<<"你只能卖同样数量的票作为你的钱。 "<<endl;
            money-=60;
        }
        cout<<"你有$"<<money<<endl;
        while(money>0)
        {
            if (d==1||d==2||d==3) if(money>=10000)
                    if (d==4||d==5) if(money>=100000)
                        {
                            cout<<"你发财了!"<<endl;
                            cout<<"你花了"<<t<<"天。"<<endl;
                            system("pause");
                            return 0;
                        }
            t++;
            cout<<"你要卖几张票？ "<<" "<<"你有$"<<money<<endl;
            cin>>n;
            if(n==0)
            {
                borrow();
                tt=t+10;
            }
            if(t==tt) bool flag=pay();
            if(flag==false)
            {
                cout<<"你不能偿还你借的钱。"<<endl;
                cout<<"你破产了！"<<endl;
                cout<<"你生存了"<<t<<" 天。"<<endl;
                system("pause");
                return 0;
            }
            if(n<0 || n>money)
            {
                cout<<"注意"<<endl;
                cout<<"你破产了！"<<endl;
                cout<<"你生存了"<<t<<" 天"<<endl;
                system("pause");
                return 0;
            }
            if (d=1) money=money+n*5;
            if (d=2) money=money+n*3;
            else money=money+n*2;
            if(money<0)
            {
                cout<<"你破产了！"<<endl;
                cout<<"你生存了"<<t<<" 天"<<endl;
                system("pause");
                return 0;
            }
            for(int i=0; i<n; i++)
            {
                p=rand()%12000;
                if(p==0)
                {
                    int y;
                    y=rand()%4;
                    if(y==1)
                    {
                        cout<<"你失去了杰克壶！"<<endl;
                        if (d==5) money-=5000;
                        else money-=10000;
                    }
                }
                else if(p>=1&&p<=8)
                {
                    cout<<"你失去了巨额奖金！"<<endl;
                    money-=1000;
                }
                else if(p>=15&&p<=50)
                {
                    cout<<"你失去了大奖！"<<endl;
                    money-=100;
                }
                else if(p>=61&&p<=360)
                {
                    cout<<"你失去了中奖！"<<endl;
                    money-=20;
                }
                else if(p>=401&&p<=1500)
                {
                    cout<<"你失去了小奖！"<<endl;
                    money-=5;
                }
            }
        }
    }
    if(money<=0)
    {
        cout<<"你破产了。"<<endl;
        cout<<"你生存了"<<t<<"天。"<<endl;
        system("pause");
        return 0;
    }
}