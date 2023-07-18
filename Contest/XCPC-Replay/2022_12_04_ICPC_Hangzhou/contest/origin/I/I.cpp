#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;
using ll = long long;
const ll TIMES = 1e4 - 5;
const ll UP = 1e9;
ll n, total, t[TIMES], mx, ave;
ll myrand() {
	return 1ll * rand() * RAND_MAX + rand();
}
int main() {
	srand(time(0));
	total = TIMES;
	n = TIMES / 2;
	total -= n;
	for(int i = 1; i <= n; i++) {
		cout << "walk " << (myrand() % UP + 1);
		cout.flush();
//		printf("walk %lld\n", myrand() % UP + 1);
//		fflush(stdout);
//		scanf("%lld", &t[i]);
		cin >> t[i];
		ave += t[i];
		mx = max(mx, t[i]);
	}
	ave /= n;
	ave *= 2;
	ave = min(ave, UP);
	ll nowpos = t[n], newpos;
	ll left = min(mx, ave - total / 2);
	for(int i = left; i <= ave && total; i++) {
//		printf("walk %d\n", i);
//		fflush(stdout);
//		scanf("%lld", &newpos);
		cout << "walk " << i;
		cout.flush();
		cin >> newpos;
		if(nowpos == newpos) {
//			printf("guess %d\n", i);
//			fflush(stdout);
			cout << "guess " << i;
			cout.flush();
			return 0;
		}
		nowpos = newpos;
		total--;
	}
	for(int i = ave + 1; i <= UP && total; i++) {
//		printf("walk %d\n", i);
//		fflush(stdout);
//		scanf("%lld", &newpos);
		cout << "walk " << i;
		cout.flush();
		cin >> newpos;
		if(nowpos == newpos) {
//			printf("guess %d\n", i);
//			fflush(stdout);
			cout << "guess " << i;
			cout.flush();
			return 0;
		}
		nowpos = newpos;
		total--;
	}
	return 0;
}
