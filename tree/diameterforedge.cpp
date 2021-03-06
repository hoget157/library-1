#ifndef call_from_test
#include<bits/stdc++.h>
using namespace std;
#endif
//BEGIN CUT HERE
template<typename T>
struct DiameterForEdge{
  using Edge = pair<int, T>;
  vector<T> dp;
  vector<vector<Edge> > G;
  DiameterForEdge(int n):dp(n),G(n){}
  void add_edge(int u,int v,T c){
    G[u].emplace_back(v,c);
    G[v].emplace_back(u,c);
  }
  void dfs(int v,int p,int &s){
    if(p<0) dp[v]=T(0);
    if(dp[s]<dp[v]) s=v;
    for(Edge e:G[v]){
      int u=e.first;
      if(u==p) continue;
      dp[u]=dp[v]+e.second;
      dfs(u,v,s);
    }
  }
  pair<int, int> endPoints(){
    int s=0;
    dfs(s,-1,s);
    int t=s;
    dfs(t,-1,t);
    return make_pair(s,t);
  }
  T build(){
    int t=endPoints().second;
    return dp[t];
  }
  vector<T> distance(int v){
    dfs(v,-1,v);
    return dp;
  }
  vector<T> farthest(){
    int t=endPoints().second;
    auto ds=dp;
    auto dt=distance(t);
    for(int i=0;i<(int)ds.size();i++)
      if(ds[i]<dt[i]) ds[i]=dt[i];
    return ds;
  }
};
//END CUT HERE
#ifndef call_from_test

#define call_from_test
#include "../tools/fastio.cpp"
#undef call_from_test

//INSERT ABOVE HERE
signed YAHOO2019_FINAL_B(){
  int n;
  cin>>n;
  DiameterForEdge<int> G(n);
  for(int i=1;i<n;i++){
    int x,y;
    cin>>x>>y;
    x--;y--;
    G.add_edge(x,y,1);
  }

  int m;
  cin>>m;
  DiameterForEdge<int> H(m);
  for(int i=1;i<m;i++){
    int x,y;
    cin>>x>>y;
    x--;y--;
    H.add_edge(x,y,1);
  }

  auto dp1=G.farthest();
  auto dp2=H.farthest();
  sort(dp1.begin(),dp1.end());
  sort(dp2.begin(),dp2.end());

  using ll = long long;
  vector<ll> s(m+1,0);
  for(int i=0;i<m;i++) s[i+1]=s[i]+dp2[i];

  ll ans=0;
  ll di=max(dp1.back(),dp2.back());

  for(ll x:dp1){
    ll y=lower_bound(dp2.begin(),dp2.end(),di-(x+1))-dp2.begin();
    ans+=di*y;
    ans+=(s[m]-s[y])+(m-y)*(x+1);
  }

  cout<<ans<<endl;
  return 0;
}
/*
  verified on 2019/12/17
  https://atcoder.jp/contests/yahoo-procon2019-final/tasks/yahoo_procon2019_final_b
*/

signed main(){
  //YAHOO2019_FINAL_B();
  return 0;
}
#endif
