#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
#define debug(x) cout << #x << " = " << x << endl;
#define lid id << 1
#define rid id << 1 | 1
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;

const int mx = 2010;
int dfn[mx], scc[mx];
stack<int> st;
struct edge{
    int v, nxt;
}e[20010];
int head[mx], n;
int tot = 0, cnt = 0, num = 0;
void add(int u, int v){
    e[tot].v = v;
    e[tot].nxt = head[u];
    head[u] = tot++;
}

int tarjan(int u){
    int lowu = dfn[u] = ++cnt;
    st.push(u);
    for (int i = head[u]; ~i; i = e[i].nxt){
        int v = e[i].v;
        if (!dfn[v]){
            int lowv = tarjan(v);
            lowu = min(lowu, lowv);
        }
        else if (!scc[v]){
            lowu = min(lowu, dfn[v]);
        }
    }
    if (dfn[u] == lowu){
        num++;
        while (1){
            int x = st.top(); st.pop();
            scc[x] = num;
            if (x == u) break;
        }
    }
    return lowu;
}

void init(){
    tot = cnt = num = 0;
    for (int i = 0; i <= n*2; i++){
        head[i] = -1;
        dfn[i] = scc[i] = 0;
    }
    while (!st.empty()) st.pop();
}

int main(){
    int T, m;
    scanf("%d", &T);
    while (T--){
        scanf("%d%d", &n, &m);
        init();
        char s[7], t[7];
        for (int i = 1; i <= m; i++){
            scanf("%s%s", s, t);
            int a = 0, b = 0;
            for (int j = 1; j < strlen(s); j++) a = a*10+(s[j]-'0');
            for (int j = 1; j < strlen(t); j++) b = b*10+(t[j]-'0');
            a = 2*(a-1), b = 2*(b-1);
            if (s[0] == 'h' && t[0] == 'h') {
                add(a^1, b);
                add(b^1, a);
            }
            if (s[0] == 'h' && t[0] == 'm') {
                add(a^1, b^1);
                add(b, a);
            }
            if (s[0] == 'm' && t[0] == 'h') {
                add(a, b);
                add(b^1, a^1);
            }
            if (s[0] == 'm' && t[0] == 'm') {
                add(a, b^1);
                add(b, a^1);
            }
        }
        for (int i = 0; i <= (n-1)*2; i++)
            if (!dfn[i]) tarjan(i);
        bool ok = 1;
        for (int i = 0; i <= (n-1)*2; i += 2){
            if (scc[i] == scc[i^1]){
                ok = 0;
                break;
            }
        }
        printf("%s\n", ok ? "GOOD" : "BAD");
    }
    return 0;
}