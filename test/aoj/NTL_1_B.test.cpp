#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_B"

#include<bits/stdc++.h>
using namespace std;

#define call_from_test
#include "../../tools/fastio.cpp"
#include "../../mod/pow.cpp"
#undef call_from_test

signed main(){
  int n,m;
  cin>>n>>m;

  const int MOD = 1e9+7;
  cout<<mod_pow(n,m,MOD)<<endl;
  return 0;
}
