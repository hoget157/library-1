#define PROBLEM "https://judge.yosupo.jp/problem/bernoulli_number"

#include<bits/stdc++.h>
using namespace std;

#define call_from_test
#include "../../tools/fastio.cpp"
#include "../../mod/mint.cpp"
#include "../../convolution/numbertheoretictransform.cpp"
#include "../../polynomial/formalpowerseries.cpp"
#undef call_from_test

signed main(){
  int n;
  cin>>n;

  NTT<2> ntt;
  using M = NTT<2>::M;
  auto conv=[&](auto as,auto bs){return ntt.multiply(as,bs);};
  FormalPowerSeries<M> FPS(conv);

  auto ps=FPS.bernoulli(n);
  for(int i=0;i<=n;i++){
    if(i) cout<<" ";
    cout<<ps[i];
  }
  cout<<endl;
  return 0;
}
