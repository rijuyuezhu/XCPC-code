#include<bits/stdc++.h>
using namespace std;

double s,ans,a[1000000];
int n;

int main(){
	
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];s+=a[i];
	}	
	double m=2+(n-1);
	
	double ans=s/m;
	printf("%0.8lf ",ans*2);
	
	for(int i=2;i<=n;i++){
		printf("%0.8lf ",ans);
	}
	
	
	return 0;
}
