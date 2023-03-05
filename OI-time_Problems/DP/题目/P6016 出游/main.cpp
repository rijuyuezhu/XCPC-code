// https://www.luogu.com.cn/problem/P6016
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<bitset>
#include<vector>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 501;
const int P = 998244353;
int n, T, p[MAXN];
struct Matrix {
    bitset<MAXN> A[MAXN];
    bitset<MAXN>& operator[] (const int& k) {return A[k];}
    const bitset<MAXN>& operator[] (const int& k)const {return A[k];}
    Matrix operator * (const Matrix& B)const {
        Matrix res;
        for(int k = 1; k <= n; k++)
            for(int i = 1; i <= n; i++)
                if(A[i][k])
                    res[i] |= B[k];
        return res;
    }
}e, res;
void qpow(int n) {
    for(int i = 1; i <= ::n; i++) res[i][i] = 1;
    while(n) {
        if(n & 1) res = res * e;
        e = e * e;
        n >>= 1;
    }
}
int ans;
int main() {
    n = read(), T = read();
    for(int i = 1; i <= n; i++) {
        p[i] = 1 - read() + P; int c = read();
        for(int j = 1; j <= c; j++) {
            int v = read();
            e[i][v] = 1;
        }
    }
    qpow(T);
    for(int i = 1; i <= n; i++) {
        int k = 1;
        for(int j = 1; j <= n; j++)
            if(res[i][j]) k = 1ll * k * p[j] % P;
        ans = (ans + 1 - k + P) % P;
    }
    printf("%d\n", ans);
    return 0;
}
