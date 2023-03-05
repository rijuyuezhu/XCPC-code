// https://www.luogu.com.cn/problem/P1005
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
const int N = 4, NN = 10000;
const int LEN = 200;
struct Bigint {
    int len;
    ll A[LEN / N + 5];
    ll& operator [] (const int &k) {return A[k];}
    ll operator [] (const int &k)const {return A[k];}
    Bigint(ll k = 0) {
        memset(A, 0x00, sizeof A); len = 0;
        if(k == 0) {len = 1; return;}
        while(k) {
            A[len++] = k % NN;
            k /= NN;
        }
    }
    Bigint operator + (const Bigint& B)const {
        Bigint C;
        C.len = max(len, B.len);
        for(int i = 0; i < C.len; i++) {
            C[i] += A[i] + B[i];
            if(C[i] >= NN) C[i] -= NN, C[i+1]++;
        }
        if(C[C.len]) C.len++;
        while(C.len > 1 && C[C.len-1] == 0) C.len--;
        return C;
    }
    Bigint operator * (const int& k)const {
        Bigint C;
        C.len = len;
        for(int i = 0; i < C.len; i++) {
            C[i] += k * A[i];
            C[i+1] += C[i] / NN;
            C[i] %= NN;
        }
        if(C[C.len]) C.len++;
        while(C.len > 1 && C[C.len-1] == 0) C.len--;
        return C;
    }
    bool operator < (const Bigint& B) const {
        if(len != B.len) return len < B.len;
        for(int i = len - 1; i >= 0; i--)
            if(A[i] != B[i]) return A[i] < B[i];
        return 0;
    }
    void print()const {
        printf("%d", A[len-1]);
        for(int i = len - 2; i >= 0; i--) {
            for(int j = NN / 10; j > A[i]; j /= 10) printf("0");
            if(A[i]) printf("%d", A[i]);
        }
    }
};
const int MAXN = 85;
int n, m, a[MAXN][MAXN];
Bigint f[MAXN][MAXN];
Bigint pow2[MAXN], t1, t2;
Bigint ans;
void work(int c) {
    for(int i = 1; i <= m; i++)
        f[i][i] = pow2[m] * a[c][i];
    for(int len = 2; len <= m; len++)
        for(int l = 1; l + len - 1 <= m; l++) {
            int r = l + len - 1;
            t1 = f[l][r-1] + pow2[m-len+1] * a[c][r];
            t2 = f[l+1][r] + pow2[m-len+1] * a[c][l];
            if(t1 < t2) f[l][r] = t2;
            else f[l][r] = t1;
        }
}
int main() {
    n = read(), m = read();
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            a[i][j] = read();
    pow2[0] = 1;
    for(int i = 1; i <= m; i++)
        pow2[i] = pow2[i-1] * 2;
    for(int i = 1; i <= n; i++) {
        work(i);
        ans = ans + f[1][m];
    }
    ans.print();
    return 0;
}