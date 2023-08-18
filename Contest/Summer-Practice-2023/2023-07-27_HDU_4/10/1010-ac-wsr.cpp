#include<bits/stdc++.h>
using namespace std;
 
int main(){
	
	int T;cin>>T;
	while(T--){
		int n,m;
		cin>>n>>m;
		if(m==1||n==1) cout<<(n+m)/2<<endl;
		else if(n%3==0||m%3==0) cout<<"2"<<endl;
		else cout<<"1"<<endl;		
	}
	
	return 0;
} 


