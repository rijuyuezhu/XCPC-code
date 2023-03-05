#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef pair <int,int> Pii;
#define reg register
#define pb push_back
#define mp make_pair
#define Mod1(x) ((x>=P)&&(x-=P))
#define Mod2(x) ((x<0)&&(x+=P))
#define rep(i,a,b) for(int i=a,i##end=b;i<=i##end;++i)
#define drep(i,a,b) for(int i=a,i##end=b;i>=i##end;--i)
template <class T> inline void cmin(T &a,T b){ ((a>b)&&(a=b)); }
template <class T> inline void cmax(T &a,T b){ ((a<b)&&(a=b)); }

char IO;
template <class T=int> T rd(){
	T s=0; int f=0;
	while(!isdigit(IO=getchar())) if(IO=='-') f=1;
	do s=(s<<1)+(s<<3)+(IO^'0');
	while(isdigit(IO=getchar()));
	return f?-s:s;
}

const int N=1<<17,P=998244353;
typedef vector <int> Poly;

int n,m;
ll qpow(ll x,ll k=P-2) {
	ll res=1;
	for(;k;k>>=1,x=x*x%P) if(k&1) res=res*x%P;
	return res;
}
int w[N],Inv[N+1],rev[N];
void Init(){
	w[N/2]=1;
	for(int t=qpow(3,(P-1)/N),i=N/2+1;i<N;++i) w[i]=1ll*w[i-1]*t%P;
	drep(i,N/2-1,1) w[i]=w[i<<1];
	Inv[0]=Inv[1]=1;
	rep(i,2,N) Inv[i]=1ll*(P-P/i)*Inv[P%i]%P;
}
int Init(int n) {
	int R=1,cc=-1;
	while(R<n) R<<=1,cc++;
	rep(i,1,R-1) rev[i]=(rev[i>>1]>>1)|((i&1)<<cc);
	return R;
}

void Show(const Poly &a,int k=0){ 
	if(k==0) { for(int i:a) printf("%d ",i); puts(""); }
	else for(int i:a) printf("%d\n",i); 
}

void NTT(int n,Poly &a,int f){
	if((int)a.size()<n) a.resize(n);
	rep(i,1,n-1) if(i<rev[i]) swap(a[i],a[rev[i]]);
	for(int i=1;i<n;i<<=1) {
		int *e=w+i;
		for(int l=0;l<n;l+=i*2) {
			for(int j=l;j<l+i;++j) {
				int t=1ll*a[j+i]*e[j-l]%P;
				a[j+i]=a[j]-t; Mod2(a[j+i]);
				a[j]+=t,Mod1(a[j]);
			}
		}
	}
	if(f==-1) {
		reverse(a.begin()+1,a.end());
		rep(i,0,n-1) a[i]=1ll*a[i]*Inv[n]%P;
	}
}

Poly Poly_Inv(Poly F) {
	int n=F.size();
	if(n==1) return Poly{(int)qpow(F[0])};
	Poly G=F; G.resize((n+1)/2); G=Poly_Inv(G);
	int R=Init(n*2);
	NTT(R,F,1),NTT(R,G,1);
	rep(i,0,R-1) F[i]=(2-1ll*F[i]*G[i]%P+P)*G[i]%P;
	NTT(R,F,-1),F.resize(n);
	return F;
}

Poly operator * (Poly A,Poly B) {
	int n=A.size()+B.size()-1;
	int R=Init(n);
	NTT(R,A,1),NTT(R,B,1);
	rep(i,0,R-1) A[i]=1ll*A[i]*B[i]%P;
	NTT(R,A,-1),A.resize(n);
	return A;
}

Poly Evaluate(Poly F,Poly X){
	static int ls[N<<1],rs[N<<1],cnt;
	static Poly T[N<<1];
	static auto TMul=[&] (Poly F,Poly G){ // 转置卷积
		int n=F.size(),m=G.size();
		if(n<=20 && m<=20){
			rep(i,0,n-m) {
				int t=0;
				rep(j,0,m-1) t=(t+1ll*F[i+j]*G[j])%P;
				F[i]=t;
			} 
			F.resize(n-m+1);
			return F;
		}
		reverse(G.begin(),G.end());
		int R=Init(n);
		NTT(R,F,1),NTT(R,G,1);
		rep(i,0,R-1) F[i]=1ll*F[i]*G[i]%P;
		NTT(R,F,-1); Poly T(n-m+1);
		rep(i,0,n-m) T[i]=F[i+m-1];
		return T;
	};

	static function <int(int,int)> Build=[&](int l,int r) { // 分治节点预处理
		int u=++cnt; ls[u]=rs[u]=0;
		if(l==r) {
			T[u]=Poly{1,P-X[l]};
			return u;
		}
		int mid=(l+r)>>1;
		ls[u]=Build(l,mid),rs[u]=Build(mid+1,r);
		T[u]=T[ls[u]]*T[rs[u]];
		return u;
	};

	int n=F.size(),m=X.size();
	cmax(n,m),F.resize(n),X.resize(n); // 事先让两个等大为n
	cnt=0,Build(0,n-1);
	F.resize(n*2+1),T[1]=TMul(F,Poly_Inv(T[1])); // 处理T[1]的前n项
	int p=0;
	rep(i,1,cnt) if(ls[i]) {
		swap(T[ls[i]],T[rs[i]]);
		T[ls[i]]=TMul(T[i],T[ls[i]]); T[rs[i]]=TMul(T[i],T[rs[i]]);
        // 自顶向下递归
	} else X[p++]=T[i][0];
	X.resize(m); // 最后返回时变回m项

	return X;
}

int main(){
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	int t1 = clock();
	Init(),n=rd(),m=rd();
	Poly F(n+1),X(m);
	rep(i,0,n) F[i]=rd();
	rep(i,0,m-1) X[i]=rd();
	Show(Evaluate(F,X),1);
	cerr << clock()-t1;
}
