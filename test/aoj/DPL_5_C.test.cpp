#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_C"

#include<bits/stdc++.h>
using namespace std;

#define call_from_test
#include "../../mod/mint.cpp"
#include "../../mod/enumeration.cpp"
#include "../../mod/stirling_2nd.cpp"
#undef call_from_test

signed main(){
  int n,k;
  scanf("%d %d",&n,&k);
  using M = Mint<int>;
  using E = Enumeration<M>;
  E::init(k);
  printf("%d\n",(stirling_2nd<M>(n,k)*E::Fact(k)).v);
  return 0;
}
