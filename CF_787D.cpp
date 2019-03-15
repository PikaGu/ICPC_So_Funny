#include <bits/stdc++.h>
#define LL long long
#define INF 0x3f3f3f3f3f3f3f3f
#define debug(x) cout << #x << " = " << x << endl;
#define lid id << 1
#define rid id << 1 | 1
using namespace std;

const int mx = 1e5+7;
struct edge{
    int v; LL w;
    edge(int v=0, LL w=0): v(v), w(w){}
    bool operator < (const edge& a) const { return w > a.w;}
};
LL d[mx*10];
vector<edge> G[mx*10];
int treeIn[mx<<2], treeOut[mx<<2];
int cnt = 0;

void build(int l, int r, int id){
    if (l == r){
        treeIn[id] = treeOut[id] = l;
        return;
    }
    int mid = (l+r)>>1;
    build(l, mid, lid);
    build(mid+1, r, rid);
    treeOut[id] = ++cnt;
    treeIn[id] = ++cnt;
    G[treeOut[lid]].push_back(edge(treeOut[id], 0));
    G[treeOut[rid]].push_back(edge(treeOut[id], 0));
    G[treeIn[id]].push_back(edge(treeIn[lid], 0));
    G[treeIn[id]].push_back(edge(treeIn[rid], 0));
}

void updIn(int l, int r, int id, int x, int y, int v, int w){
    //cout << l << " l, r " << r << endl;
    if (x <= l && r <= y){
        G[v].push_back(edge(treeIn[id], w));
        return;
    }
    int mid = (l+r)>>1;
    if (x <= mid) updIn(l, mid, lid, x, y, v, w);
    if (mid < y) updIn(mid+1, r, rid, x, y, v, w);
}

void updOut(int l, int r, int id, int x, int y, int v, int w){
    if (x <= l && r <= y){
        G[treeOut[id]].push_back(edge(v, w));
        return;
    }
    int mid = (l+r)>>1;
    if (x <= mid) updOut(l, mid, lid, x, y, v, w);
    if (mid < y) updOut(mid+1, r, rid, x, y, v, w);
}

void dij(int s){
    priority_queue<edge> q;
    memset(d, INF, sizeof d);
    d[s] = 0;
    q.push(edge(s, d[s]));
    while (!q.empty()){
        int u = q.top().v; q.pop();
        for (int i = 0; i < G[u].size(); i++){
            int v = G[u][i].v;
            LL w = G[u][i].w;
            if (d[v] > d[u] + w){
                d[v] = d[u] + w;
                q.push(edge(v, d[v]));
            }
        }
    }
}

int main(){
    int n, q, s;
    scanf("%d%d%d", &n, &q, &s);
    cnt = n;
    build(1, n, 1);
    int op, u, v, w;
    while (q--){
        scanf("%d", &op);
        if (op == 1){
            scanf("%d%d%d", &u, &v, &w);
            G[u].push_back(edge(v, w));
        }
        else {
            int l, r;
            scanf("%d%d%d%d", &v, &l, &r, &w);
            if (op == 2) updIn(1, n, 1, l, r, v, w);
            else updOut(1, n, 1, l, r, v, w);
        }
    }
    dij(s);
    for (int i = 1; i <= n; i++)
        printf("%lld%c", d[i] == INF ? -1 : d[i], i == n ? '\n' : ' ');
    return 0;
}