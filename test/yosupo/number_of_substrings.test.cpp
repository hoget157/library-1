#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"

#include<bits/stdc++.h>
using namespace std;

#define call_from_test
#include "../../tools/fastio.cpp"
#include "../../string/suffixarray.cpp"
#include "../../string/longestcommonprefix.cpp"
#undef call_from_test

signed main(){
  string s;
  cin>>s;
  LongestCommonPrefix lcp(s);

  int n=s.size();
  long long ans=0;
  for(int i=0;i<n;i++)
    ans+=(n-lcp.sa[i+1])-lcp.query(i,i+1);

  cout<<ans<<endl;
  return 0;
}
