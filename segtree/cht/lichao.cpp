#ifndef call_from_test
#include<bits/stdc++.h>
using namespace std;
#endif
//BEGIN CUT HERE
template <typename T, bool isMin>
struct LiChao{
  static constexpr T INF = numeric_limits<T>::max();
  struct Line{
    T a,b;
    Line(T a,T b):a(a),b(b){}
    T get(T x){return a*x+b;}
  };

  int n;
  vector<T> pos;
  vector<Line> dat;
  LiChao(int n){
    pos.resize(n);
    iota(pos.begin(),pos.end(),T(0));
    init(n);
  }

  LiChao(const vector<T> &pos):pos(pos){init(pos.size());}

  void init(int n_){
    n=1;
    while(n<n_) n<<=1;
    while((int)pos.size()<n)
      pos.emplace_back(T(pos.back()+1));
    dat.assign(2*n,Line(0,-INF));
  }

  void addLine(T a,T b){
    if(isMin) a=-a,b=-b;
    Line x(a,b);
    update(1,0,n-1,x);
  }

  T query(T x){
    int t=lower_bound(pos.begin(),pos.end(),x)-pos.begin();
    if(isMin) return -query(1,0,n-1,t);
    return query(1,0,n-1,t);
  }

  inline bool over(Line &a,Line &b,T lb,T ub){
    return a.get(lb)>=b.get(lb)&&a.get(ub)>=b.get(ub);
  }

  void update(int k,int l,int r,Line &x){
    T lb=pos[l],ub=pos[r];
    if(over(dat[k],x,lb,ub)) return;
    if(over(x,dat[k],lb,ub)){
      dat[k]=x;
      return;
    }
    int c=(l+r)>>1;
    if(dat[k].get(pos[c])<x.get(pos[c])) swap(dat[k],x);
    if(dat[k].get(lb)<=x.get(lb)) update((k<<1)|0,l,c,x);
    else update((k<<1)|1,c+1,r,x);
  }

  T query(int k,int l,int r,int t){
    T res=dat[k].get(pos[t]);
    if(l==r) return res;
    int c=(l+r)>>1;
    if(t<=c) return max(res,query((k<<1)|0,l,c,t));
    return max(res,query((k<<1)|1,c+1,r,t));
  }
};
template <typename T, bool isMin>
constexpr T LiChao<T, isMin>::INF;
//END CUT HERE
#ifndef call_from_test

#define call_from_test
#include "../../tools/fastio.cpp"
#include "../../tools/vec.cpp"
#include "../../tools/compress.cpp"
#undef call_from_test

//INSERT ABOVE HERE

signed CSA070_SQUAREDEND(){
  using ll = long long;

  int n,k;
  cin>>n>>k;
  vector<ll> as(n+1,0);
  for(int i=0;i<n;i++) cin>>as[i];

  if(n==1){
    puts("0");
    return 0;
  }

  vector<ll> pos=compress(as);
  vector<LiChao<ll, true> > vs;
  for(int i=0;i<k+1;i++) vs.emplace_back(pos);
  vs[0].addLine(-2*as[0],as[0]*as[0]);

  const ll INF = 1e15;
  auto dp=make_v<ll>(k+1,n+1);
  fill_v<ll>(dp,INF);
  dp[0][0]=0;

  for(int i=0;i<n;i++){
    for(int j=0;j<k;j++){
      dp[j+1][i+1]=vs[j].query(as[i])+as[i]*as[i];
      vs[j+1].addLine(-2*as[i+1],dp[j+1][i+1]+as[i+1]*as[i+1]);
    }
  }

  cout<<dp[k][n]<<endl;
  return 0;
}

/*
  verified on 2019/12/17
  https://csacademy.com/contest/archive/task/squared-ends
*/

signed main(){
  //CSA070_SQUAREDEND();
  return 0;
}
#endif
