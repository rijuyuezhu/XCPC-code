#include <algorithm>
#include <iostream>
#include <string>
#include <set>
using namespace std;
const int bas1 = 233, P1 = 998244353;
const int bas2 = 454, P2 = 1e9 + 7;
const int MAXN = 1e4 + 5;
using pii = pair<int, int>;
pii hs(string s) {
	int n = s.length();
	pii t = {0, 0};
	for(int i = 0; i < n; i++) {
		t.first = (1ll * t.first * bas1 + s[i]) % P1;
		t.second = (1ll * t.second * bas1 + s[i]) % P1;
	}
	return t;
}
int n;
set<pii> st;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	for(int i = 1; i <= n; i++) {
		int m;
		cin >> m;
		bool flag = 0;
		for(int j = 1; j <= m; j++) {
			string s;
			cin >> s;
			if(s.find("bie") != string::npos) {
				pii h = hs(s);
				if(st.find(h) == st.end()) {
					st.insert(h);
					flag = 1;
					cout << s << '\n';
				}
			}
		}
		if(!flag) {
			cout << "Time to play Genshin Impact, Teacher Rice!" << '\n';
		}
	}
	return 0;	
}

