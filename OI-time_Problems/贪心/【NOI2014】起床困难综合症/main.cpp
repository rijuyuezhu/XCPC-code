//http://uoj.ac/problem/2
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 2e5 + 5;
int n, m;
int op[MAXN], t[MAXN];
int Gt() {
    char s[10];
    scanf("%s", s);
    switch(s[0]) {
        case 'A': return 1;
        case 'O': return 2;
        case 'X': return 3;
    }
    return 0;
}
int now, ans;
int calc(int v, int j) {
    int ans = v;
    for(int i = 1; i <= n; i++) {
        int vt = (t[i] >> j) & 1;
        if(op[i] == 1) ans &= vt;
        else if(op[i] == 2) ans |= vt;
        else ans ^= vt;
    }
    return ans;
}
int main() {
    //freopen("sleep.in", "r", stdin);
    n = read(), m = read();    
    for(int i = 1; i <= n; i++) op[i] = Gt(), t[i] = read();
    for(int j = 30; j >= 0; j--) {
        int a1 = calc(1, j) << j;
        int a0 = calc(0, j) << j;
        if(a1 > a0 && now + (1 << j) <= m) {now += 1 << j; ans += a1;}
        else ans += a0;
    }
    printf("%lld\n", ans);
    return 0;
}