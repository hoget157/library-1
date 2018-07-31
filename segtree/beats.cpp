#include<bits/stdc++.h>
using namespace std;
using Int = long long;
//BEGIN CUT HERE
template <typename T,typename E>
struct SegmentTree{
  using F = function<T(T,T)>;
  using G = function<T(T,E)>;
  using H = function<E(E,E)>;
  using P = function<E(E,size_t)>;
  using B = function<bool(T,E)>;
  int n;
  F f;
  G g;
  H h;
  T ti;
  E ei;
  B ignore,satisfy;
  P p;
  vector<T> dat;
  vector<E> laz;
  SegmentTree(int n_,F f,G g,H h,T ti,E ei,
	      B ignore,B satisfy,
	      P p=[](E a,size_t b){b++;return a;}):
    f(f),g(g),h(h),ti(ti),ei(ei),
    ignore(ignore),satisfy(satisfy),p(p){
    init(n_);
  }
  void init(int n_){
    n=1;
    while(n<n_) n*=2;
    dat.assign(2*n-1,ti);
    laz.assign(2*n-1,ei);
  }
  void build(int n_, vector<T> v){
    for(int i=0;i<n_;i++) dat[i+n-1]=v[i];
    for(int i=n-2;i>=0;i--)
      dat[i]=f(dat[i*2+1],dat[i*2+2]);
  }
  inline void eval(int len,int k){
    if(laz[k]==ei) return;
    if(k*2+1<n*2-1){
      laz[k*2+1]=h(laz[k*2+1],laz[k]);
      laz[k*2+2]=h(laz[k*2+2],laz[k]);
    }
    dat[k]=g(dat[k],p(laz[k],len));
    laz[k]=ei;
  }
  T update(int a,int b,E x,int k,int l,int r){
    eval(r-l,k);
    if(r<=a||b<=l||ignore(dat[k],x)) return dat[k];
    if(a<=l&&r<=b&&satisfy(dat[k],x)){
      laz[k]=h(laz[k],x);
      return g(dat[k],p(laz[k],r-l));
    }
    return dat[k]=f(update(a,b,x,k*2+1,l,(l+r)/2),
		    update(a,b,x,k*2+2,(l+r)/2,r));
  }
  T update(int a,int b,E x){
    return update(a,b,x,0,0,n);
  }
  T query(int a,int b,int k,int l,int r){
    eval(r-l,k);
    if(r<=a||b<=l) return ti;
    if(a<=l&&r<=b) return dat[k];
    T vl=query(a,b,k*2+1,l,(l+r)/2);
    T vr=query(a,b,k*2+2,(l+r)/2,r);
    return f(vl,vr);
  }
  T query(int a,int b){
    return query(a,b,0,0,n);
  }
};
//END CUT HERE
signed CSA070_AndOrMAX(){
  int n,q;
  scanf("%d %d",&n,&q);
  vector<int> a(n);
  for(int i=0;i<n;i++) scanf("%d",&a[i]);

  int mask=(1<<20)-1;
  using P = pair<int, int>;
  // T.first: max, T.second: same
  // E.first: por, E.second: pand
  auto f=[&](P a,P b){
	   return P(max(a.first,b.first),
		    a.second&b.second&(a.first^b.first^mask));
	 };
  auto g=[&](P a,P b){
	   a.first=(a.first|b.first)&(mask^b.second);
	   a.second|=b.first|b.second;
	   return a;
	 };
  auto h=[&](P a,P b){
	   a.first|=b.first;
	   a.first&=mask^b.second;
	   a.second|=b.second;
	   a.second&=mask^b.first;
	   return a;
	 };
  P ti(0,mask),ei(0,0);
  auto ignore=[](P a,P b){return false;};
  auto satisfy=[](P a,P b){
		 return (a.second&b.first)==b.first
		   &&(a.second&b.second)==b.second;};

  SegmentTree<P, P> seg(n,f,g,h,ti,ei,ignore,satisfy);
  vector<P> v(n);
  for(int i=0;i<n;i++) v[i]=P(a[i],mask);
  seg.build(n,v);
  
  for(int i=0;i<q;i++){
    int t,l,r,x;
    scanf("%d %d %d",&t,&l,&r);
    l--;
    if(t!=3) scanf("%d",&x);
    if(t==1) seg.update(l,r,P(0,mask&~x));
    if(t==2) seg.update(l,r,P(x,0));
    if(t==3){
      int val=seg.query(l,r).first;
      printf("%d\n",val);
    }
    //for(int j=0;j<n;j++) cout<<seg.query(j,j+1).first<<" ";
    //cout<<endl;
  }
  return 0;
}
/*
  verified on 2018/07/31
  https://csacademy.com/contest/round-70/task/and-or-max
*/

signed main(){
  CSA070_AndOrMAX();
}
