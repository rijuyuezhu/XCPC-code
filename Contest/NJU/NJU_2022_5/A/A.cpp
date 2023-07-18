#include <cstdio>
#include <algorithm>
using namespace std;
using ll = long long;

constexpr int MAXN = 5e6 + 5;
int n, p, q, m; 
unsigned int SA, SB, SC; 
unsigned int rng61() {
    SA ^= SA << 16;
    SA ^= SA >> 5;
    SA ^= SA << 1;
    unsigned int t = SA;
    SA = SB; 
    SB = SC;
    SC ^= t ^ SA;
    return SC;
}

int st[MAXN], _st, num[MAXN];
ll ans;
void PUSH(int v) {
    if(_st == 0 || v > st[_st])
        st[++_st] = v, num[_st] = 1;
    else
        num[_st]++;
}
void POP() {
    if(_st == 0) return ;
    --num[_st];
    if(num[_st] == 0) --_st;
}
int getmax() {
    if(_st == 0) return 0;
    return st[_st];
}
void gen(int te) {
    ans = 0; _st = 0;
    scanf("%d%d%d%d%u%u%u", &n, &p, &q, &m, &SA, &SB, &SC);
    for(int i = 1; i <= n; i++) {
        if(rng61() % (p + q) < p)
            PUSH(rng61() % m + 1);
        else
            POP();
        ans ^= 1ll * i * getmax();
    }
    printf("Case #%d: %lld\n", te, ans);
}
int main() {
    int T; scanf("%d", &T);
    for(int i = 1; i <= T; i++)
        gen(i);
    return 0;
}