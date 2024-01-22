#include <iostream>
#include <algorithm>
using i64 = long long;

struct Pnt {
  i64 x, y;
  Pnt(i64 x = 0, i64 y = 0) : x(x), y(y) {}
};

using Vec = Pnt;

i64 Dot(const Vec &a, const Vec &b) {return a.x * b.x + a.y * b.y;}
i64 Cro(const Vec &a, const Vec &b) {return a.x * b.y - a.y * b.x;}
Vec operator + (const Vec &a, const Vec &b) {return Vec(a.x + b.x, a.y + b.y);}
Vec operator - (const Vec &a, const Vec &b) {return Vec(a.x - b.x, a.y - b.y);}
Vec operator * (const Vec &a, i64 b) {return Vec(a.x * b, a.y * b);}

using Line = std::pair<Pnt, Pnt>;
using Seg = std::pair<Pnt, Pnt>;

bool samesign(i64 a, i64 b) {
  return a != 0 && b != 0 && (a ^ b) >= 0;
}

bool isCrossSegSeg(const Pnt &a, const Pnt &b, const Pnt &c, const Pnt &d) {
  if (std::max(a.x, b.x) < std::min(c.x, d.x) || 
      std::max(c.x, d.x) < std::min(a.x, b.x) || 
      std::max(a.y, b.y) < std::min(c.y, d.y) ||
      std::max(c.y, d.y) < std::min(a.y, b.y)
    )
    return 0;
  if (samesign(Cro(c-b, a-b), Cro(d-b, a-b)) || samesign(Cro(a-c, d-c), Cro(b-c, d-c)))
    return 0;
  return 1;
}
bool isPointonLine(const Pnt &p, const Pnt &a, const Pnt &b) {
  return Cro(p-a, b-a) == 0;
}
bool isInside(const Pnt &p, const Pnt &a, const Pnt &b, const Pnt &c, const Pnt &d) {
  if (isPointonLine(p, a, b) || isPointonLine(p, c, d)) 
    return 0;
  i64 side1 = Cro(b-a, p-a);
  i64 side2 = Cro(c-b, p-b);
  i64 side3 = Cro(d-c, p-c);
  return samesign(side1, side3) && (side2 == 0 || samesign(side1, side2));
}
Pnt a, b, c, d, e, f;
int getfield(const Pnt &p) {
  int field = -1;
  if (isInside(p, c, d, e, f))
    field = 0;
  else if (isInside(p, f, e, c, d))
    field = 2;
  else if (isInside(p, d, c, f, e))
    field = 1;
  else if (isInside(p, e, f, d, c))
    field = 3;
  return field;
}

void work() {
  std::cin >> a.x >> a.y;
  std::cin >> b.x >> b.y;
  std::cin >> c.x >> c.y;
  std::cin >> d.x >> d.y;
  std::cin >> e.x >> e.y;
  std::cin >> f.x >> f.y;
  int c1 = isCrossSegSeg(a, b, c, d);
  int c2 = isCrossSegSeg(a, b, e, f);
  if (!c1 && !c2) {
    std::cout << 0 << '\n';
    return;
  }
  if (c1 && c2) { //try find 
    if (isCrossSegSeg(c, d, e, f) == 0)
      goto CASE1;
    int fa = getfield(a);
    int fb = getfield(b);
    if (fa == -1 || fb == -1)
      goto CASE1;
    if ((fa ^ fb) == 1) {
      std::cout << 2 << '\n';
      return ;
    }
  }

  CASE1:
  std::cout << 1 << '\n';
  return ;
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int T;
  std::cin >> T;
  while (T--)
    work();
  return 0;
}
