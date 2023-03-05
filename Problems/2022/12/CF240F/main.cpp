#include <algorithm>
#include <iostream>
using namespace std;
constexpr int MAXN = 1e5 + 5;


namespace Sgt {
#define ls o << 1
#define rs o << 1 | 1
	struct Tag {
		int cnt[26], single, x, y;
		//when single=-1, it means have no tag
	};
	struct Val {
		int cnt[26];
		Tag tag;
		void upd(const Val &a, const Val &b) {
			for(int i = 0; i < 26; i++)
				cnt[i] = a.cnt[i] + b.cnt[i];
		}
	}e[MAXN << 2];
	void build(int o, int l, int r, char s[]) {
		e[o].tag = {{0}, -1, 0, 0};
		if(l == r) {
			for(int i = 0; i < 26; i++)
				cnt[i] = 0;
			cnt[s[l]-'0'] = 1;
			return ;
		}
		int m = (l + r) >> 1;
		build(ls, l, m, s);
		build(rs, m+1, r, s);
		e[o].upd(e[ls], e[rs]);
	}
	void psdtag(int o, int l, int r, Tag v) {
	}
#undef ls
#undef rs
}
int n, m;
char s[MAXN];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	return 0;
}
