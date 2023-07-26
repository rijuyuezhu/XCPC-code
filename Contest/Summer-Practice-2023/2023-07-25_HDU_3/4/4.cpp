#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<vector>
#define fg for (int t = 0; t < 10; t++)
using namespace std;
#define x first
#define y second
using db = long double;
using pr = pair<db, db>;
using pi = pair<int, int>;
constexpr int MAXN = 1e5 + 5;
const db PI = acos((db)-1.0);
constexpr db eps = 1e-10;
int dcmp(db x) {return x > eps ? 1 : (x < -eps ? -1 : 0);}
int n;
db theta[10], cs[10], sn[10];
int id[10][MAXN];
pi P[MAXN];
pr Q[10][MAXN];
vector<pi> ans;

pr rotate(pi P, int t) {
	return pr(P.x * cs[t] - P.y * sn[t], P.x * sn[t] + P.y * cs[t]);
}

int test_id;
bool cmp(int a, int b) {
	return Q[test_id][a].x < Q[test_id][b].x;
}
void try_find(int k) {
	bool flag = 0;
	int whole = 0;
	fg {
		flag = 1;
		db delta = Q[t][id[t][k+1]].x - Q[t][id[t][1]].x;
		for (int i = 0; i < 2 * n; i += 2 * k)
			for (int j = i + 1; j <= i + k; j++)
				if (dcmp(Q[t][id[t][j + k]].x - Q[t][id[t][j]].x - delta) != 0) {
					flag = 0;
					goto FAIL;
				}
FAIL:
		;
		if (flag) {
			whole++;
		}
	}
	if (whole <= 5)
		return ;
	int dx = P[id[0][k+1]].x - P[id[0][1]].x;
	int dy = P[id[0][k+1]].y - P[id[0][1]].y;
	ans.push_back(pi(dx, dy));
	ans.push_back(pi(-dx, -dy));

}
void work() { 
	fg {
		theta[t] = ((db)rand() / RAND_MAX) * 2.0 * PI;
		cs[t] = cos(theta[t]);
		sn[t] = sin(theta[t]);
	}
	cin >> n;
	ans.clear();
	db mx[10] = {0};
	for (int i = 1; i <= 2 * n; i++) {
		cin >> P[i].x >> P[i].y;
		fg {
			Q[t][i] = rotate(P[i], t);
			mx[t] = max(mx[t], std::abs(Q[t][i].x));
			id[t][i] = i;
		}
	}
	for (int i = 1; i <= 2 * n; i++) {
		fg {
			Q[t][i].x /= mx[t];
		}
	}
	fg {
		test_id = t;
		sort(id[t] + 1, id[t] + 1 + 2 * n, cmp);
	}
	for (int i = 1; 1ll * i * i <= n; i++)
		if (n % i == 0) {
			try_find(i);
			if (i * i != n)
				try_find(n / i);
		}
	sort(ans.begin(), ans.end());
	int ans_s = unique(ans.begin(), ans.end()) - ans.begin();
	ans.resize(ans_s);
	cout << ans_s << '\n';
	for (auto v : ans)
		cout << v.first << ' ' << v.second << '\n';
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while (T--) 
		work();
	return 0;
}
