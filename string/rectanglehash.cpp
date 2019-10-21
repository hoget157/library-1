#ifndef call_from_test
#include<bits/stdc++.h>
using namespace std;
using Int = long long;
template<typename T1,typename T2> inline void chmin(T1 &a,T2 b){if(a>b) a=b;}
template<typename T1,typename T2> inline void chmax(T1 &a,T2 b){if(a<b) a=b;}

template<typename T,T MOD,T B>
struct RollingHash{
  using ll = long long;
  vector<T> hash,p;
  RollingHash(){}
  RollingHash(vector<T> vs){init(vs);}
  RollingHash(string &s){
    vector<T> vs;
    for(char c:s) vs.emplace_back(c);
    init(vs);
  }
  void init(vector<T> vs){
    int n=vs.size();
    hash.assign(n+1,0);
    p.assign(n+1,1);
    for(int i=0;i<n;i++){
      hash[i+1]=((ll)hash[i]*B+vs[i])%MOD;
      p[i+1]=(ll)p[i]*B%MOD;
    }
  }
  //S[l, r)
  T find(int l,int r){
    T res=(ll)hash[r]+MOD-(ll)hash[l]*p[r-l]%MOD;
    return res>=MOD?res-MOD:res;
  }
};
#endif
//BEGIN CUT HERE
template<typename T,T MOD,T B1,T B2>
auto rectangle_hash(vector<string> vs,int r,int c){
  vector< RollingHash<T, MOD, B1> > hs;
  for(string s:vs) hs.emplace_back(s);

  int h=vs.size(),w=vs[0].size();
  vector< vector<T> > res(h-r+1,vector<T>(w-c+1));

  for(int j=0;j+c<=w;j++){
    vector<T> ts(h);
    for(int i=0;i<h;i++)
      ts[i]=hs[i].find(j,j+c);

    RollingHash<T, MOD, B2> rh(ts);
    for(int i=0;i+r<=h;i++)
      res[i][j]=rh.find(i,i+r);
  }
  return res;
}
//END CUT HERE
#ifndef call_from_test
signed main(){
  return 0;
}
#endif
