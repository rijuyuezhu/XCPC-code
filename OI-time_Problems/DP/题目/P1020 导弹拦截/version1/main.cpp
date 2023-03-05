// https://www.luogu.com.cn/problem/P1020
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
const int MAXN = 100005;
const int MAXV = 50005;

int n, a[MAXN];
int t[MAXV];
void add(int x, int k) {
    for(int i = x; i < MAXV; i += (i&-i)) t[i] = max(t[i], k);
}
int que(int x) {
    int ans = 0;
    for(int i = x; i; i -= (i&-i)) ans = max(ans, t[i]);
    return ans;
}
int main() {
    while(scanf("%d", &a[++n]) != EOF);
    n--;
    memset(t, 0x00, sizeof t);
    int ans = 0;
    for(int i = n; i >= 1; i--) {
        int x = que(a[i]) + 1;
        ans = max(ans, x);
        add(a[i], x);
    }
    printf("%d\n", ans);
    memset(t, 0x00, sizeof t);
    ans = 0;
    for(int i = 1; i <= n; i++) {
        int x = que(a[i]-1) + 1;
        ans = max(ans, x);
        add(a[i], x);
    }
    printf("%d\n", a// https://www.luogu.com.cn/problem/P1020
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
const int MAXN = 100005;
const int MAXV = 50005;

int n, a[MAXN];
int t[MAXV];
void add(int x, int k) {
    for(int i = x; i < MAXV; i += (i&-i)) t[i] = max(t[i], k);
}
int que(int x) {
    int ans = 0;
    for(int i = x; i; i -= (i&-i)) ans = max(ans, t[i]);
    return ans;
}
int main() {
    while(scanf("%d", &a[++n]) != EOF);
    n--;
    memset(t, 0x00, sizeof t);
    int ans = 0;
    for(int i = n; i >= 1; i--) {
        int x = que(a[i]) + 1;
        ans = max(ans, x);
        add(a[i], x);
    }
    printf("%d\n", ans);
    memset(t, 0x00, sizeof t);
    ans = 0;
    for(int i = 1; i <= n; i++) {
        int x = que(a[i]-1) + 1;
        ans = max(ans, x);
        add(a[i], x);
    }
    printf("%d\n", ans);
    return 0;
}ns);
    return 0;
}