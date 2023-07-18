#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <vector>
#define int long long
inline int getint(){
	int ssum=0,ff=1;char ch;
	for(ch=getchar();!isdigit(ch)&&ch!='-';ch=getchar());
	if(ch=='-') ff=-1,ch=getchar();
	for(;isdigit(ch);ch=getchar()) ssum=ssum*10+ch-'0';
	return ssum*ff;
}
using db = long double;
using namespace std;
constexpr int MAXN = 2e5 + 5;
constexpr db eps = 1e-10, inf = 1e10;
int dcmp(db x) {return x < -eps ? -1 : (x > eps ? 1 : 0);}
db Abs(db x) {return x * dcmp(x);}
struct Pnt {
	db x, y;
	Pnt(db x = 0, db y = 0) : x(x), y(y) {}
};
using Vec = Pnt;
db Dot(const Vec &a, const Vec &b) {return a.x * b.x + a.y * b.y;}
db Cro(const Vec &a, const Vec &b) {return a.x * b.y - a.y * b.x;}
db Len(const Vec &a) {return sqrt(Dot(a, a));}
Vec operator + (const Vec &a, const Vec &b) {return Vec(a.x + b.x, a.y + b.y);}
Vec operator - (const Vec &a, const Vec &b) {return Vec(a.x - b.x, a.y - b.y);}
Vec operator * (const Vec &a, const db &b) {return Vec(a.x * b, a.y * b);}
bool operator == (const Vec &a, const Vec &b) {return !dcmp(a.x - b.x) && !dcmp(a.y - b.y);}

Pnt CrossPoint(const Pnt &a, const Pnt &b, const Pnt &c, const Pnt &d) {
	Vec ab = b-a, cd = d-c, ca = a-c;
	return a + ab * (Cro(cd, ca) / Cro(ab, cd));
}

int righthand(const Pnt &a, const Pnt &b, const Pnt &p)
{
	return dcmp(Cro(p-a, b-a));
}

using Poly = vector<Pnt>;

int _out, _in, s, t;
Poly out, in;
vector<db> dis;
db nowans, circ, ans;


void calc(int p) {
	int q = p + 1;
	if (q == _in) q = 0;
	db ret = nowans;
	int sn = s + 1;
	if (sn == _out) sn = 0;
	int tp = t - 1;
	if (tp < 0) tp = _out - 1;
	Pnt a = CrossPoint(in[p], in[q], out[s], out[sn]);
	ret += Len(out[sn]-a);
	Pnt b = CrossPoint(in[p], in[q], out[tp], out[t]);
	ret += Len(b-out[tp]);
	ans += Len(in[q] - in[p]) * (ret / circ);
}

void adjust(int p) {
	int q = p + 1;
	if (q == _in) q = 0;
	int sn = s + 1;
	if (sn == _out) sn = 0;
	while (righthand(in[p], in[q], out[sn]) < 0) {
		nowans -= dis[sn];
		s = sn;
		sn = s + 1;
		if (sn == _out) sn = 0;
	}
	while (righthand(in[p], in[q], out[t]) >= 0) {
		int tp = t - 1;
		if (tp < 0) tp = _out - 1;
		nowans += dis[tp];
		t++;
		if (t == _out) t = 0;
	}
}


signed main() 
{
	scanf("%lld%lld", &_out, &_in);
	out.resize(_out);
	in.resize(_in);
	dis.resize(_out);
	for (int i = 0; i < _out; i++) {
		int x, y;
		x=getint();y=getint();
		out[i].x = x; out[i].y = y;
	}
	for (int i = 0; i < _in; i++) {
		int x, y;
		x=getint();y=getint();
		in[i].x = x; in[i].y = y;
	}
	for (int i = 0; i < _out; i++) {
		int j = i+1;
		if (j == _out) j = 0;
		dis[i] = Len(out[j] - out[i]);
		circ += dis[i];
	}
	for(int i = 0; i < _out; i++) {
		int j = i + 1;
		if (j == _out) j = 0;
		if (righthand(in[0], in[1], out[i]) < 0 && righthand(in[0], in[1], out[j]) >= 0) {
			s = i;
			t = j;
			break;
		}
	}
	int flag = 0;
	while (!flag) {
		int nxt = t + 1;
		if (nxt == _out) nxt = 0;
		if (righthand(in[0], in[1], out[t]) >= 0 && righthand(in[0], in[1], out[nxt]) < 0) {
			flag = 1;
		} else {
			nowans += dis[t];
		}
		t = nxt;
	}
	calc(0);
	for (int i = 1; i < _in; i++) {
		adjust(i);
		calc(i);
	}
	printf("%.15lf\n", (double)ans);
	return 0;
}
