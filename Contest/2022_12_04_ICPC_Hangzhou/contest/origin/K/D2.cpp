#include<bits/stdc++.h>
using namespace std;

double a[1000000];
int n;

int main(){
	
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}	
	
	for(int j=1;j<=1000;j++){
		
		for(int i=1;i<n;i++){
			a[i]/=2;a[i+1]+=a[i];
		}
		a[n]/=2;a[1]+=a[n];
		
	}
	
	for(int i=1;i<=n;i++){
		printf("%0.4lf",a[i]);
	}
	
	
	return 0;
}
