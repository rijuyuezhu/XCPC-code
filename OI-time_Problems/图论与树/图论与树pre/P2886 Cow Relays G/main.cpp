//https://www.luogu.com.cn/problem/P2886
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 1e6 + 5;
const int MAXP = 205;
const int INF = 0x3f3f3f3f;
int n, N, T, S, E;
int id[1005];
int getnum(int t) {
    if(id[t]) return id[t];
    return id[t] = ++n;
}
struct Matrix {
    int a[MAXP][MAXP];
    int* operator [] (const int& k) {return a[k];}
    const int* operator [] (const int& k)const {return a[k];}
    Matrix operator * (const Matrix& b)const {
        Matrix C;
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                C[i][j] = INF;
        for(int i = 1; i <= n; i++)
            for(int k = 1; k <= n; k++)
                for(int j = 1; j <= n; j++)
                    C[i][j] = min(C[i][j], a[i][k] + b[k][j]);
        return C;
    }
}a;
Matrix ret;//init is all 0
void qpow(int n) {
    ret = a;
    n--;
    while(n) {
        if(n & 1) ret = ret * a;
        a = a * a;
        n >>= 1;
    }
}
int main() {
    N = read(), T = read(), S = getnum(read()), E = getnum(read());
    memset(a.a, 0x3f, sizeof a.a);
    for(int i = 1; i <= T; i++) {
        int w = read(), u = getnum(read()), v = getnum(read());
        a[u][v] = a[v][u] = min(w, a[u][v]);
    }
    qpow(N);
    printf("%d\n", ret[S][E]);
    return 0;
}