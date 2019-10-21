#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2725"

#include<bits/stdc++.h>
using namespace std;

#define call_from_test
#include "../../tools/fastio.cpp"
#include "../../datastructure/convexhulltrick.cpp"
#undef call_from_test

signed main(){
  using ll = long long;

  int n,x;
  cin>>n>>x;
  vector<ll> ts(n),ps(n),fs(n);
  for(int i=0;i<n;i++) cin>>ts[i]>>ps[i]>>fs[i];

  using T = tuple<ll, ll, ll>;
  vector<T> vt(n);
  for(int i=0;i<n;i++) vt[i]=T(fs[i],ps[i],ts[i]);
  sort(vt.begin(),vt.end());
  for(int i=0;i<n;i++) tie(fs[i],ps[i],ts[i])=vt[i];

  vector<ConvexHullTrick<ll, false> > vh(x+1);

  ll ans=0;
  for(int i=0;i<n;i++){
    for(int j=x;j>ts[i];j--){
      if(vh[j-ts[i]].empty()) continue;
      ll val=vh[j-ts[i]].queryMonotoneInc(fs[i])+ps[i]-fs[i]*fs[i];
      vh[j].addLine(2*fs[i],val-fs[i]*fs[i]);
      ans=max(ans,val);
    }
    vh[ts[i]].addLine(2*fs[i],ps[i]-fs[i]*fs[i]);
    ans=max(ans,ps[i]);
  }

  cout<<ans<<endl;
  return 0;
}
