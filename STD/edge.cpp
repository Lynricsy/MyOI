struct Edge
{
    int nxt;
    int to;
}edges[100090];
int head[100090];
int cnt_edges;
void add_edges(int x,int y)
{
    ++cnt_edges;
    edges[cnt_edges].nxt=head[x];
    head[x]=cnt_edges;
    edges[cnt_edges].to=y;
}