#ifndef call_from_test
#include<bits/stdc++.h>
using namespace std;
#endif
//BEGIN CUT HERE
template<typename T,bool isMin>
struct NonmonotonicConvexHullTrick {
  using number = double;
  static constexpr number INF = numeric_limits<T>::max();
  struct Line {
    T m,b,val;
    number x;
    bool q;
    Line(T m=0,T b=0):m(m),b(b),val(0),x(-INF),q(false){}

    T eval(T x) const{return m*x+b;}
    bool parallel(const Line &l) const{return m==l.m;}
    number intersect(const Line &l) const{
      return parallel(l)?number(INF):number(l.b-b)/number(m-l.m);
    }
    bool operator<(const Line &l) const{
      if(l.q) return x<l.val;
      return m<l.m;
    }
  };

  set<Line> hull;
  using iter = typename set<Line>::iterator;

  bool cPrev(iter it){return it!=hull.begin();}
  bool cNext(iter it){return it!=hull.end()&&next(it)!=hull.end();}

  bool bad(const Line &l1,const Line &l2,const Line &l3){
    return l1.intersect(l3) <= l1.intersect(l2);
  }
  bool bad(iter it){
    return cPrev(it)&&cNext(it)&&bad(*prev(it),*it,*next(it));
  }

  iter update(iter it){
    if(!cPrev(it)) return it;
    number x=it->intersect(*prev(it));
    Line tmp(*it);
    tmp.x=x;
    it=hull.erase(it);
    return hull.insert(it,tmp);
  }

  void addLine(T m,T b){
    if(isMin) m=-m,b=-b;
    Line l(m,b);
    iter it=hull.lower_bound(l);
    if(it!=hull.end()&&l.parallel(*it)){
      if(it->b<b) it=hull.erase(it);
      else return;
    }
    it=hull.insert(it,l);
    if(bad(it)){
      hull.erase(it);
      return;
    }
    while(cPrev(it)&&bad(prev(it))) hull.erase(prev(it));
    while(cNext(it)&&bad(next(it))) hull.erase(next(it));

    it=update(it);
    if(cPrev(it)) update(prev(it));
    if(cNext(it)) update(next(it));
  }

  bool empty() const{
    return hull.empty();
  }

  T query(T x){
    assert(!empty());
    Line q;
    q.val=x;q.q=1;
    iter it=--hull.lower_bound(q);
    if(isMin) return -(it->eval(x));
    return it->eval(x);
  }
} ;
//END CUT HERE
#ifndef call_from_test
template<typename T1,typename T2> void chmin(T1 &a,T2 b){if(a>b) a=b;}
template<typename T1,typename T2> void chmax(T1 &a,T2 b){if(a<b) a=b;}

//INSERT ABOVE HERE

signed TENKA12016FINAL_E(){
  using ll = long long;

  int n,l;
  scanf("%d %d",&n,&l);
  vector<vector<int> > as(n,vector<int>(l));
  for(int i=0;i<n;i++)
    for(int j=0;j<l;j++)
      scanf("%d",&as[i][j]);

  vector<ll> dp(l,0);

  for(int i=0;i<n;i++){
    NonmonotonicConvexHullTrick<ll, true> cht;
    for(ll j=0;j<l;j++)
      cht.addLine(-2*j,as[i][j]+j*j);
    for(ll j=0;j<l;j++)
      dp[j]+=j*j+cht.query(j);
  }

  printf("%lld\n",*min_element(dp.begin(),dp.end()));
  return 0;
}

/*
  verified on 2019/12/17
  https://atcoder.jp/contests/tenka1-2016-final/tasks/tenka1_2016_final_e
*/

signed COLOPL2018FINAL_C(){
  using ll = long long;

  int n;
  scanf("%d",&n);
  vector<ll> as(n);
  for(int i=0;i<n;i++) scanf("%lld",&as[i]);
  NonmonotonicConvexHullTrick<ll, false> cht;
  for(ll i=0;i<n;i++) cht.addLine(-2*i,-(as[i]+i*i));
  for(ll i=0;i<n;i++) printf("%lld\n",-cht.query(-i)+i*i);
  return 0;
}

/*
  verified on 2019/12/17
  https://atcoder.jp/contests/colopl2018-final-open/tasks/colopl2018_final_c
*/

signed main(){
  //TENKA12016FINAL_E();
  //COLOPL2018FINAL_C();
  return 0;
}
#endif
