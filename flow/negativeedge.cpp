#ifndef call_from_test
#include<bits/stdc++.h>
using namespace std;

#define call_from_test
#include "primaldual.cpp"
#undef call_from_test

#endif
//BEGIN CUT HERE
template<typename TF,typename TC>
struct NegativeEdge{
  PrimalDual<TF, TC> G;
  vector<TF> fs;
  TC sum;
  int S,T;
  NegativeEdge(){}
  NegativeEdge(int n):G(n+2),fs(n+2,0),sum(0),S(n),T(n+1){}

  void use_edge(int u,int v,TF cap,TC cost){
    fs[u]-=cap;
    fs[v]+=cap;
    sum=sum+cost*cap;
  }

  void add_edge(int u,int v,TF cap,TC cost){
    if(cost<TC(0)){
      use_edge(u,v,cap,cost);
      swap(u,v);
      cost=-cost;
    }
    G.add_edge(u,v,cap,cost);
  }

  TC flow(int &ok){
    TF f=0;
    for(int i=0;i<S;i++){
      if(fs[i]>0){
        f+=fs[i];
        G.add_edge(S,i,+fs[i],TC(0));
      }
      if(fs[i]<0){
        G.add_edge(i,T,-fs[i],TC(0));
      }
    }
    return sum+G.flow(S,T,f,ok);
  }

  TC flow(int ts,int tt,TF tf,int &ok){
    fs[ts]+=tf;
    fs[tt]-=tf;
    return flow(ok);
  }
};
//END CUT HERE
#ifndef call_from_test

#define call_from_test
#include "../tools/fastio.cpp"
#include "../tools/chminmax.cpp"
#undef call_from_test

//INSERT ABOVE HERE
signed CFR190_B(){
  using ll = long long;

  int n,m;
  cin>>n>>m;
  vector<string> vp(n);
  vector<int> vs(n);
  for(int i=0;i<n;i++) cin>>vp[i]>>vs[i];
  vector<int> ss(m);
  for(int i=0;i<m;i++) cin>>ss[i];

  int S=n+m,T=n+m+1;
  NegativeEdge<ll, ll> G(n+m+2);

  for(int i=0;i<m;i++){
    G.add_edge(S,i,1,0);
    for(int j=0;j<n;j++){
      if(vp[j]=="ATK"){
        if(ss[i]>=vs[j]) G.add_edge(i,m+j,1,vs[j]-ss[i]);
      }
      if(vp[j]=="DEF"){
        if(ss[i]> vs[j]) G.add_edge(i,m+j,1,0);
      }
    }
  }

  auto H=G;
  for(int i=0;i<m;i++){
    G.add_edge(i,T,1,-ss[i]);
    H.add_edge(i,T,1,0);
  }

  for(int j=0;j<n;j++){
    G.use_edge(m+j,T,1,0);
    H.add_edge(m+j,T,1,0);
  }

  int ok;
  ll ans=0;
  if(n<m){
    ll gv=G.flow(S,T,m,ok);
    if(ok) chmin(ans,gv);
  }
  ll hv=H.flow(S,T,m,ok);
  if(ok) chmin(ans,hv);

  cout<<-ans<<endl;
  return 0;
}
/*
  verified on 2019/10/13
  https://codeforces.com/contest/321/problem/B
*/

signed KUPC2019_H(){
  int n,m;
  cin>>n>>m;
  NegativeEdge<int, int> G(n+2);

  int cap=1;
  for(int i=0;i<m;i++){
    int u,v,l;
    cin>>u>>v>>l;
    u--;v--;
    G.add_edge(v,u,1,l-1);
    if(l==0) cap++;
  }

  for(int i=0;i<n;i++){
    G.add_edge(n,i,cap,2);
    G.add_edge(i,n,cap,0);
  }

  int ok=0;
  cout<<-G.flow(n,n,0,ok)<<endl;
  return 0;
}
/*
  verified on 2019/10/24
  https://atcoder.jp/contests/kupc2019/tasks/kupc2019_h
*/

signed main(){
  //CFR190_B();
  KUPC2019_H();
  return 0;
}
#endif
