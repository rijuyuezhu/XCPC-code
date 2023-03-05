extern "C" int Seniorious(int x);
extern "C" int Chtholly(int n, int c) {
	int l = 1, r = n;
	while(l <= r) {
		int mid = (l + r) >> 1;
		int op = Seniorious(mid);
		if(op == 0) return mid;
		else if(op == 1) r = mid - 1;
		else l = mid + 1;
	}
	return -1;
}
