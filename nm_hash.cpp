#include <bits/stdc++.h>
#include <unordered_map>
#define LL long long
#define uLL unsigned long long
#define INF 0x3f3f3f3f
#define debug(x) cout << #x << " = " << x << endl;
using namespace std;

const int mx = 1010;
const int base1 = 131;
const int base2 = 233;
char s[mx][mx], t[55][55];
uLL hs[mx][mx], ht[55][55];
uLL p1[55], p2[55];

void init(){
    p1[0] = p2[0] = 1;
    for (int i = 1; i <= 50; i++) {
        p1[i] = p1[i-1]*base1;
        p2[i] = p2[i-1]*base2;
    }
}

int main(){
    int n, m, T, x, y, kase = 0;
    init();
    while (scanf("%d%d%d%d%d", &n, &m, &T, &x, &y) == 5){
        for (int i = 1; i <= n; i++){
            scanf("%s", s[i]+1);
            for (int j = 1; j <= m; j++)
                hs[i][j] = hs[i][j-1]*base1+s[i][j]-'a';
        }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                hs[i][j] += hs[i-1][j]*base2;
        unordered_map<uLL, int> mp;
        for (int i = x; i <= n; i++){
            for (int j = y; j <= m; j++){
                uLL k = hs[i][j]-hs[i-x][j]*p2[x]-hs[i][j-y]*p1[y]
                        +hs[i-x][j-y]*p2[x]*p1[y];
                mp[k] = 1;
            }
        }
        int ans = 0;
        while (T--){
            for (int i = 1; i <= x; i++){
                scanf("%s", t[i]+1);
                for (int j = 1; j <= y; j++)
                    ht[i][j] = ht[i][j-1]*base1+t[i][j]-'a';
            }
            for (int i = 1; i <= x; i++)
                for (int j = 1; j <= y; j++)
                    ht[i][j] += ht[i-1][j]*base2;
            if (mp[ht[x][y]]) ans++;
        }
        printf("Case %d: %d\n", ++kase, ans);
    }
    return 0;
}