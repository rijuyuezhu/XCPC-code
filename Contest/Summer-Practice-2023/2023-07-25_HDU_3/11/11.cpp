#include<iostream>
#include<algorithm>
using namespace std;
constexpr int MAXN = 55;
char ori[MAXN][MAXN], sca[MAXN][MAXN];
int n, m, Z;
bool scale(int k) {
	m = n / k;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++) {
			char c = ori[i * k][j * k];
			for (int p = 0; p < k; p++)
				for (int q = 0; q < k; q++)
					if (ori[i * k + p][j * k + q] != c)
						return 0;
			sca[i][j] = c;
		}
	return 1;
}
void run(int k) {
	for (int i = 0; i < m; i++)
		for(int t = 0; t < k; t++) {
			for (int j = 0; j < m; j++) 
				for (int q = 0; q < k; q++)
					cout << sca[i][j];
			cout << '\n';
		}
}
void fail() {
	cout << "error" << '\n';
}

void work() {
	cin >> n >> Z;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> ori[i][j];
	switch (Z) {
	case 100:
	case 200:
		scale(1);
		run(Z / 100);
		break;
	case 150:
		if (n % 2) {
			fail();
		} else {
			if (scale(2))
				run(3);
			else
				fail();
		}
		break;
	default:
		if (n % 4) {
			fail();
		} else {
			if (scale(4))
				run(Z / 25);
			else
				fail();
		}
	}
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
