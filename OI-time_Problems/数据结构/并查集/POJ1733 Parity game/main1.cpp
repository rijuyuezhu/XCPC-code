// http://poj.org/problem?id=1733
/*
边带权：
维护一种集合，它有多种传递性，**但是这些传递性可以相互导出**
这样的话，我们可以把它们扔到一个集合中，并且加上一个类似权值的东西加以标识
还是以根作为代表元素，这样可以快速导出

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
const int MAXN = 10005;
struct Que {
    int l, r, t;
}q[MAXN];
int n, lsh[MAXN], tot, upto[MAXN], d[MAXN];
void LSH() {
    sort(lsh + 1, lsh + 1 + tot);
    tot = unique(lsh + 1, lsh + 1 + tot) - lsh - 1;
}
int LSH(int x) {
    return lower_bound(lsh + 1, lsh + 1 + tot, x) - lsh;
}
int getup(int x) {
    if(x == upto[x]) return x;
    int rt = getup(upto[x]);
    d[x] ^= d[upto[x]];
    return upto[x] = rt;
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
    for(int i = 1; i <= tot; i++) upto[i] = i;
    for(int i = 1; i <= n; i++) {
        int l = LSH(q[i].l), r = LSH(q[i].r);
        int ul = getup(l), ur = getup(r);
        if(ul == ur) {
            if((d[l] ^ d[r]) != q[i].t) {
                printf("%d\n", i-1);
                return 0;
            }
        } else upto[ul] = ur, d[ul] = d[l] ^ d[r] ^ q[i].t;
    }
    printf("%d\n", n);
    return 0;
}