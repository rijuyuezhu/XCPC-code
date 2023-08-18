#include <iostream>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cstdlib>
#include <ctime>
using i64 = long long;
constexpr int MAXN = 1e6 + 5;
constexpr int MAXM = 5005;
constexpr int INF = 0x3f3f3f3f;
constexpr int P = (int)1e9 + 7;
int MOD(int v) {return v >= P ? v - P : v;}
namespace MINT {
  struct mint {
    int v;
    mint(int v = 0) : v(v) {}
  };
  mint operator + (mint a, mint b) {return MOD(a.v + b.v);}
  mint operator - (mint a, mint b) {return MOD(a.v - b.v + P);}
  mint operator * (mint a, mint b) {return 1LL * a.v * b.v % P;}
  mint qpow(int a0, int n = P-2) {
    mint ret = 1, a = a0;
    for (; n; n >>= 1, a = a * a)
      if(n & 1)
        ret = ret * a;
    return ret;
  }
}
using namespace MINT;

namespace Treap {
  struct Node {
    int ls, rs, s, c, k, v;
  }e[MAXN];
  std::queue<int> dustbin;
  int tot;
  int newnode() {
    if (!dustbin.empty()) {
      int x = dustbin.front(); dustbin.pop();
      return x;
    } else {
      return ++tot;
    }
  }
  void destroy(int x) {
    dustbin.push(x);
  }
  void upd(int p) {e[p].s = e[e[p].ls].s + e[e[p].rs].s + e[p].c;}
  void lturn(int &p) {int s = e[p].rs; e[p].rs = e[s].ls; upd(p); e[s].ls = p; upd(s); p = s;}
  void rturn(int &p) {int s = e[p].ls; e[p].ls = e[s].rs; upd(p); e[s].rs = p; upd(s); p = s;}
  void ins(int &p, int v) {
    if (!p) e[p = newnode()] = {0, 0, 1, 1, rand(), v};
    else if (e[p].v == v) e[p].c++, upd(p);
    else if (e[p].v > v)
      ins(e[p].ls, v), e[e[p].ls].k < e[p].k ? rturn(p) : upd(p);
    else 
      ins(e[p].rs, v), e[e[p].rs].k < e[p].k ? lturn(p) : upd(p);
  }
  void del(int &p, int v) {
    if (e[p].v > v) del(e[p].ls, v), upd(p);
    else if (e[p].v < v) del(e[p].rs, v), upd(p);
    else if (e[p].c > 1) e[p].c--, upd(p);
    else if (!e[p].ls) destroy(p), p = e[p].rs;
    else if (!e[p].rs) destroy(p), p = e[p].ls;
    else if (e[e[p].ls].k < e[e[p].rs].k)
      rturn(p), del(e[p].rs, v), upd(p);
    else 
      lturn(p), del(e[p].ls, v), upd(p);
  }
  int fd(int p, int v) {
    if (!p) return -INF;
    else if (e[p].v == v) return p;
    else if (e[p].v < v) return fd(e[p].rs, v);
    else return fd(e[p].ls, v);
  }
  int pre(int p, int v) {
    if (!p) return -INF;
    else if (e[p].v < v) return std::max(pre(e[p].rs, v), e[p].v);
    else return pre(e[p].ls, v);
  }
  int nxt(int p, int v) {
    if (!p) return INF;
    else if (e[p].v > v) return std::min(nxt(e[p].ls, v), e[p].v);
    else return nxt(e[p].rs, v);
  }
}
int rt;

int n, m, a[MAXN], B;

struct Que {
  int l, r, id, num;
}que[MAXM];

bool cmp(const Que &a, const Que &b) {
  if (a.num != b.num)
    return a.num < b.num;
  return (a.num & 1) ? a.r < b.r : a.r > b.r;
}
mint ans, qans[MAXM];

void Add(int v) {
  int p = Treap::fd(rt, v), pr = Treap::pre(rt, v), nx = Treap::nxt(rt, v);
  if (p != -INF) {
    int c = Treap::e[p].c;
    if (c >= 1)
      nx = v;
    if (c >= 2)
      pr = v;
  }
  if (pr != -INF) {
    if (nx != INF) {
      ans = ans * qpow(pr, P-1-nx);
    }
    ans = ans * qpow(pr, v);
  }
  if (nx != INF) {
    ans = ans * qpow(v, nx);
  }
  Treap::ins(rt, v);
}
void Sub(int v) {
  int p = Treap::fd(rt, v), pr = Treap::pre(rt, v), nx = Treap::nxt(rt, v);
  if (p != -INF) {
    int c = Treap::e[p].c;
    if (c >= 2)
      nx = v;
    if (c >= 3)
      pr = v;
  }
  if (pr != -INF) {
    ans = ans * qpow(pr, P-1-v);
    if (nx != INF)
      ans = ans * qpow(pr, nx);
  }
  if (nx != INF) {
    ans = ans * qpow(v, P-1-nx);
  }
  Treap::del(rt, v);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  srand(time(NULL));
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++)
    std::cin >> a[i];
  B = 1.007 * n / std::sqrt(m) + 50;
  B = std::min(B, n);
  for (int i = 1; i <= m; i++) {
    std::cin >> que[i].l >> que[i].r;
    que[i].id = i;
    que[i].num = (que[i].l-1) / B;
  }
  std::sort(que + 1, que + 1 + m, cmp);
  int L = 1, R = 0;
  ans = 1;
  for (int i = 1; i <= m; i++) {
    Que &now = que[i];
    while (now.l < L) Add(a[--L]);
    while (now.r > R) Add(a[++R]);
    while (now.l > L) Sub(a[L++]);
    while (now.r < R) Sub(a[R--]);
    qans[now.id] = ans;
  }
  for (int i = 1; i <= m; i++)
    std::cout << qans[i].v << '\n';
  return 0;
}
