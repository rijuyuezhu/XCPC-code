;include <iostream>
#include <algorithm>
#include <string>
#include <set>
#include <map>
using namespace std;
using pii = pair<int, int>;

map<string, int> nameto;
vector<set<pii> > vec;
vector<int> lstdie;
int _nameto;

int n;

int geti(const string &s) {
	auto i = nameto.find(s);
	if (i != nameto.end()) { 
		return i->second;
	}
	else {
		nameto[s] = ++_nameto;
		vec.push_back(set<pii>());
		lstdie.push_back(0);
		return _nameto;
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	vec.resize(1);
	lstdie.resize(1);
	for (int i = 1; i <= n; i++) {
		string a, b;
		cin >> a >> b;
		int ia = geti(a);
		int ib = geti(b);
		lstdie[ib] = i;
		
		auto iit = vec[ia].begin(), lstiit = vec[ia].end();
		while (iit != vec[ia].end()) {
			if (iit->first < lstdie[iit->second]) {
				lstiit = iit;
			}
			++iit;
		}
		if (lstiit != vec[ia].end()) {
			set<pii> tmp;
			++lstiit;
			for (auto x = lstiit; x != vec[ia].end(); x++)
				tmp.insert(*x);
			vec[ia] = tmp;
		}

		vec[ia].insert(pii(i, ib));
		if (vec[ia].size() == 5) {
			cout << "PENTA KILL!" << '\n';
			return 0;
		}
	}
	cout << "SAD:(" << '\n';
	return 0;
}

