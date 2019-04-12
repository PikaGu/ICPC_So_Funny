#include <bits/stdc++.h>
#define LL long long
#define INF 0x3f3f3f3f
#define debug(x) cout << #x << " = " << x << endl;
using namespace std;

const int mx = 110;
const int mod = 10000;
struct Matrix{
    LL a[mx][mx];
    Matrix(){
        memset(a, 0, sizeof a);
    }
};

Matrix mul(Matrix a, Matrix b){
    Matrix ans;
    int n = 2;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            for (int k = 1; k <= n; k++){
                ans.a[i][j] = (ans.a[i][j] + a.a[i][k]*b.a[k][j]%mod)%mod;
            }
        }
    }
    return ans;
}

Matrix qpow(Matrix x, LL n){
    Matrix c;
    c.a[1][1] = c.a[2][2] = 1;
    while (n){
        if (n & 1) c = mul(c, x);
        x = mul(x, x);
        n >>= 1;
    }
    return c;
}

int main(){
    int n;
    while (scanf("%d", &n) == 1 && n != -1){
        Matrix a;
        a.a[1][1] = 1, a.a[1][2] = 1, a.a[2][1] = 1, a.a[2][2] = 0;
        a = qpow(a, n);
        printf("%lld\n", a.a[1][2]);
    }
    return 0;
}