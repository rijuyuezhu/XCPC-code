# 计算几何模板大全

<https://www.cnblogs.com/Xing-Ling/p/12102489.html>

# PART 1 点与向量

## 基础板子（点和向量）

```cpp
const db eps = 1e-8, inf = 1e10;
int dcmp(db x) {return x < -eps ? -1 : (x > eps ? 1 : 0);}
db Abs(db x) {return x * dcmp(x);}
struct Pnt {
	db x, y;
	Pnt(db x = 0, db y = 0) : x(x), y(y) {}
};
typedef Pnt Vec;
db Dot(const Vec& a, const Vec& b) {return a.x * b.x + a.y * b.y;}
db Cro(const Vec& a, const Vec& b) {return a.x * b.y - a.y * b.x;}
db Len(const Vec& a) {return sqrt(Dot(a, a));}
Vec operator + (const Vec& a, const Vec& b) {return Vec(a.x + b.x, a.y + b.y);}
Vec operator - (const Vec& a, const Vec& b) {return Vec(a.x - b.x, a.y - b.y);}
Vec operator * (const Vec& a, const db& b) {return Vec(a.x * b, a.y * b);}
bool operator == (const Pnt& a, const Pnt& b) {return !dcmp(a.x - b.x) && !dcmp(a.y - b.y);}
db Angle(const Vec& a, const Vec& b) {return acos(Dot(a, b) / Len(a) / Len(b));}
```

## 位置变换

向量 $\bm a$ 逆时针转 $\theta$ 弧度。

$$
\begin{bmatrix}
    x'
    \\
    y'
\end{bmatrix}
=
\begin{bmatrix}
    \cos \theta & -\sin \theta
    \\
    \sin \theta & \cos \theta
\end{bmatrix}
\begin{bmatrix}
    x
    \\
    y
\end{bmatrix}
$$
```cpp
Pnt Turn(const Pnt& p, const db& rad) {return Pnt(p.x * cos(rad) - p.y * sin(rad), p.x * sin(rad) + p.y * cos(rad));}
```

# PART 2 点、直线、线段

```cpp
typedef pair<Pnt, Pnt> Line;
typedef pair<Pnt, Pnt> Seg;
```

一般写函数时，直线先用两个参数（两个 `Pnt`）表示；为了方便，再重载一下。接下来的部分仅使用前者。

## 点和直线

(1) 点在直线上？

```cpp
bool isPointonLine(const Pnt& p, const Pnt& a, const Pnt& b) {
    return !dcmp(Cro(p-a, b-a));
}
```
(2) 点到直线的投影（垂足）

```cpp
Pnt FootPoint(const Pnt& p, const Pnt& a, const Pnt& b) {
    Vec ab = b-a, ap = p-a;
    return a + ab * (Dot(ap, ab) / Dot(ab, ab));
}
```

(3) 点到直线的距离


```cpp
db DistPointLine(const Pnt& p, const Pnt& a, const Pnt& b) {
    return Cro(p-a, p-b) / Len(b-a);
}
```

(4) 点关于直线的对称点

```cpp 
Pnt Reflect(const Pnt& p, const Pnt& a, const Pnt& b) {
    return p + (FootPoint(p, a, b)-p) * 2;
}
```

## 点和线段

(1) 点在线段上？

```cpp
bool isPointonSeg(const Pnt& p, const Pnt& a, const Pnt& b) {
    return !dcmp(Cro(p-a, b-a)) && dcmp(Dot(p-a,p-b)) <= 0;
}
```

(2) 点到线段的距离

```cpp
db DistPointSeg(const Pnt& a, const Pnt& b) {
    if(a == b) return a;
    Vec ap = p-a, bp = p-b, ab = b-a;
    if(dcmp(Dot(ap, ab)) <= 0) return Len(ap);
    if(dcmp(Dot(bp, ab)) >= 0) return Len(bp);
    return Abs(Cro(ap, bp) / Len(ab));
}
```

## 线与线

(1) 两直线交点

```cpp
Pnt CrossPoint(const Pnt& a, const Pnt& b, const Pnt& c, const Pnt& d) {
    Vec ab = b-a, cd = d-c, ca = a-c;
    return a + ab * (Cro(cd, ca) / Cro(ab, cd));
}
```

(2) 直线和线段是否相交

```cpp
bool isCrossLineSeg(const Pnt& a, const Pnt& b, const Pnt& c, const Pnt& d) {
    Pnt p = CrossPoint(a, b, c, d);
    return isPointonSeg(p, c, d);
}
```
(3) 线段和线段是否相交

分为两步：快速排斥实验和跨立实验

```cpp
bool isCrossSegSeg(const Pnt& a, const Pnt& b, const Pnt& c, const Pnt& d) {
    if(max(a.x, b.x) < min(c.x, d.x) || max(c.x, d.x) < min(a.x, b.x) || max(a.y, b.y) < min(c.y, d.y) || max(c.y, d.y) < min(a.y, b.y)) return 0;
    if(dcmp(Cro(c-b, a-b)) * dcmp(Cro(d-b, a-b)) > 0 || dcmp(Cro(a-c, d-c) * dcmp(b-c, d-c)) > 0) return 0;
    return 1;
}
```

# PART 3 点、线 与 多边形，多边形 与 多边形

## 点与多边形

多边形的表示方法：
```cpp
typedef vector<Pnt> Poly;
```

涉及到多边形（或者说凸包）时，相当重要的一点是点的顺序。一般我会在下面的算法标上 顺/逆 表示点的顺序。（其实顺逆都差不多qwq）

(1) 判断点在任意多边形内？

射线法，时间复杂度 $O(n)$。

```cpp
int PIP(const Pnt& p, const Poly& G) {
	int cnt = 0;
    int n = G.size();
    int n = G.size();
	if(n == 1) return p == G[0] ? 2 : 0;
	else if(n == 2) return isPointonSeg(p, G[0], G[1]) ? 2 : 0;
	for(int i = 0; i < n; i++) {
		int j = (i+1) % n;
		if(isPointonSeg(p, G[i], G[j])) return 2;
		if(p.y >= min(G[i].y, G[j].y) && p.y < max(G[i].y, G[j].y)) {
			db tmp = G[i].x + (p.y - G[i].y) / (G[j].y - G[i].y) * (G[j].x - G[i].x);
			if(dcmp(tmp - p.x) > 0) cnt++;
		}
	}
	return cnt & 1;
}
/*
返回 1：在多边形内
返回 2：在多边形上
返回 3：在多边形外。
*/
```

(2) 判断点在凸多边形内？

二分法，时间复杂度 $O(\log n)$

```cpp
int PIP(const Pnt& p, const Poly& G) {//顺
	int n = G.size();
	if(n == 1) return p == G[0] ? 2 : 0;
	else if(n == 2) return isPointonSeg(p, G[0], G[1]) ? 2 : 0;
	if(Cro(p-G[0], G[1]-G[0]) < 0 || Cro(p-G[0], G[n-1]-G[0]) > 0) return 0;
	if(isPointonSeg(p, G[0], G[1]) || isPointonSeg(p, G[0], G[n-1])) return 2;
	int l = 1, r = n-2, t = -1;
	while(l <= r) {
		int m = (l + r) >> 1;
		if(Cro(p-G[0], G[m]-G[0]) > 0) t = m, l = m + 1;
		else r = m - 1;
	}
	if(t == -1) return 0;
	if(Cro(p-G[t], G[t+1]-G[t]) < 0) return 0;
	if(isPointonSeg(p, G[t], G[t+1])) return 2;
	return 1;
}
```

## 线与多边形

简单判断即可。

## 多边形与多边形

判断两个多边形的关系：相交/包含/相离。

首先，判断任意分别来自两个多边形的两边是否相交，判断多边形相交；

然后，若不相交，判断一个多边形是否有一点在另一个多边形内（相互要判断），判断是否包含；

最后，不相交也不包含则为相离。

## 多边形周长

有手就行。

```cpp
db Circum(const Poly& G) {
	db ans = 0;
	int n = G.size();
	for(int i = 0; i < n; i++) {
		int j = (i+1) % n;
		ans += Len(G[j]-G[i]);
	}
	return ans;
}
```

## 多边形面积

用叉积求任意多边形面积：

```cpp
db PolyArea(const Poly& G) {
    db ans = 0;
    int n = G.size();
    for(int i = 0; i < n; i++) {
        int j = (i+1) % n;
        ans += Cro(G[i], G[j]);
    }
    return Abs(ans / 2);
}
```

# PART 4 凸包

Graham 扫描法
```cpp
bool cmp(const Pnt& a, const Pnt& b) {return dcmp(a.x - b.x) == 0 ? a.y < b.y : a.x < b.x;}
Poly ConvexHull(Poly G) {//顺
	static int st[MAXN];
	int _st = 0;
	sort(G.begin(), G.end(), cmp);
	unique(G.begin(), G.end());
	if(G.size() <= 2) return G;
	int n = G.size();
	st[++_st] = 0; st[++_st] = 1;
	for(int i = 2; i < n; i++) {
		while(_st > 1 && Cro(G[st[_st]]-G[st[_st-1]], G[i]-G[st[_st]]) >= 0) _st--;
		st[++_st] = i;
	}
	int t = _st; st[++_st] = n-2;
	for(int i = n-3; i >= 0; i--) {
		while(_st > t && Cro(G[st[_st]]-G[st[_st-1]], G[i]-G[st[_st]]) >= 0) _st--;
		st[++_st] = i;
	}
	Poly T;
	for(int i = 1; i < _st; i++) T.push_back(G[st[i]]);
	return T;
}
```

还有一种水平扫描线法，类似。

## PART 5 旋转卡壳

求凸包直径

```cpp
db Getmax(const Poly& G) {//逆
	int n = G.size();
	if(n == 1) return 0;
	else if(n == 2) return Len(G[1]-G[0]);
	db ans = Len(G[1]-G[0]);
	for(int i = 0, j = 2; i < n; i++) {
		int i2 = (i+1) % n, j2 = (j+1) % n;
		while(dcmp(Cro(G[i2]-G[i], G[j]-G[i]) - Cro(G[i2]-G[i], G[j2]-G[i])) < 0) j = j2, j2 = (j2+1) % n;
		ans = max(ans, max(Len(G[j]-G[i]), Len(G[j]-G[i2])));
	}
	return ans;
}
```

## PART 6 半平面交

```cpp
int dir(const Pnt& p, const Pnt& a, const Pnt& b) {return dcmp(Cro(p - a, b - a));}
struct Line {
	Pnt a, b;
	db k;
	Line(Pnt A = Pnt(0, 0), Pnt B = Pnt(0, 0)) {
		a = A; b = B; k = atan2(b.y - a.y, b.x - a.x);
	}
};
int dir(const Pnt& p, const Line& l) {return dir(p, l.a, l.b);}
bool operator < (const Line& p, const Line& q) {
	return dcmp(p.k - q.k) == 0 ? dir(p.a, q) == -1 : p.k < q.k;
}
Pnt CrossPoint (const Pnt& a, const Pnt& b, const Pnt& c, const Pnt& d) {
	Vec ab = b-a, cd = d-c, ca = a-c;
	return a + ab * (Cro(cd, ca) / Cro(ab, cd));
}
Pnt CrossPoint(const Line& p, const Line& q) {return CrossPoint(p.a, p.b, q.a, q.b);}
Poly Halfplanecut(vector<Line> G) {
	sort(G.begin(), G.end());
	int n = 0;
	for(int i = 1; i < (int)G.size(); i++)
		if(dcmp(G[i].k - G[i-1].k)) G[++n] = G[i];
	n++; G.resize(n);
	static int que[MAXN];
	int hd = 1, tl = 0;
	for(int i = 0; i < n; i++) {
		while(hd < tl && dir(CrossPoint(G[que[tl]], G[que[tl-1]]), G[i]) > 0) --tl;
		while(hd < tl && dir(CrossPoint(G[que[hd]], G[que[hd+1]]), G[i]) > 0) ++hd;
		que[++tl] = i;
	}
	while(hd < tl && dir(CrossPoint(G[que[tl]], G[que[tl-1]]), G[que[hd]]) > 0) --tl;
	while(hd < tl && dir(CrossPoint(G[que[hd]], G[que[hd+1]]), G[que[tl]]) > 0) ++hd;
	Poly ans;
	for(int i = hd; i <= tl; i++) {
		int j = i == tl ? hd : i + 1;
		ans.push_back(CrossPoint(G[que[i]], G[que[j]]));
	}
	return ans;//逆
}
```