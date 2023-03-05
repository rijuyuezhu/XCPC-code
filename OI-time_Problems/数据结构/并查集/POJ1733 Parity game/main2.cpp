// http://poj.org/problem?id=1733
/*
扩展域：把每个节点的所有可能情况拆开。
两个节点在同一个集合中相当于这两个节点代表的情况可以同时满足
*/
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
const int MAXN = 20005;
struct Que {
    int l, r, t;
}q[MAXN];
int n, lsh[MAXN], tot, upto[MAXN];
void LSH() {
    sort(lsh + 1, lsh + 1 + tot);
    tot = unique(lsh + 1, lsh + 1 + tot) - lsh - 1;
}
int LSH(int x) {
    return lower_bound(lsh + 1, lsh + 1 + tot, x) - lsh;
}
int getup(int x) {
    if(x == upto[x]) return x;
    return upto[x] = getup(upto[x]);
}
int main() {
    read(); n = read();
    for(int i = 1; i <= n; i++) {
        q[i].l = read() - 1; q[i].r = read();
        char s[10]; scanf("%s", s);
        if(s[0] == 'e') q[i].t = 0;
        else q[i].t = 1;
        lsh[++tot] = q[i].l, lsh[++tot] = q[i].r;
    }
    LSH();
    for(int i = 1; i <= tot; i++) upto[i] = i, upto[i + tot] = i + tot;
    /*
        1~tot:odd
        tot+1~2tot:even
    */
    for(int i = 1; i <= n; i++) {
        int l = LSH(q[i].l), r = LSH(q[i].r);
        if(q[i].t) {// not same
            if(getup(l) == getup(r)) {
                printf("%d\n", i-1); return 0;
            }
            upto[getup(l)] = getup(r + tot);
            upto[getup(r)] = getup(l + tot);
        } else {
            if(getup(l) == getup(r + tot)) {
                printf("%d\n", i-1); return 0;
            }
            upto[getup(l)] = getup(r);
            upto[getup(l + tot)] = getup(r + tot);
        }
    }
    printf("%d\n", n);
    return 0;
}