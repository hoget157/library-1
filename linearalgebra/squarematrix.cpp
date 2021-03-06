#ifndef call_from_test
#include<bits/stdc++.h>
using namespace std;
#endif
//BEGIN CUT HERE
template<typename R, size_t N>
struct SquareMatrix{
  typedef array<R, N> arr;
  typedef array<arr, N> mat;
  mat dat;

  SquareMatrix(){
    for(size_t i=0;i<N;i++)
      for(size_t j=0;j<N;j++)
        dat[i][j]=R::add_identity();
  }

  bool operator==(const SquareMatrix& a) const{
    return dat==a.dat;
  }

  size_t size() const{return N;}
  arr& operator[](size_t k){return dat[k];}
  const arr& operator[](size_t k) const {return dat[k];}

  static SquareMatrix add_identity(){return SquareMatrix();}
  static SquareMatrix mul_identity(){
    SquareMatrix res;
    for(size_t i=0;i<N;i++) res[i][i]=R::mul_identity();
    return res;
  }

  SquareMatrix operator*(const SquareMatrix &B) const{
    SquareMatrix res;
    for(size_t i=0;i<N;i++)
      for(size_t j=0;j<N;j++)
        for(size_t k=0;k<N;k++)
          res[i][j]=res[i][j]+(dat[i][k]*B[k][j]);
    return res;
  }

  SquareMatrix operator+(const SquareMatrix &B) const{
    SquareMatrix res;
    for(size_t i=0;i<N;i++)
      for(size_t j=0;j<N;j++)
        res[i][j]=dat[i][j]+B[i][j];
    return res;
  }

  SquareMatrix pow(long long n) const{
    SquareMatrix a=*this,res=mul_identity();
    while(n){
      if(n&1) res=res*a;
      a=a*a;
      n>>=1;
    }
    return res;
  }
};
//END CUT HERE
#ifndef call_from_test

#define call_from_test
#include "../tools/fastio.cpp"
#include "../tools/compress.cpp"
#include "../mod/mint.cpp"
#include "../segtree/basic/ushi.cpp"
#undef call_from_test

//INSERT ABOVE HERE
signed YAHOO2019_FINAL_D(){
  using ll = long long;
  using M = Mint<int>;
  using MM = SquareMatrix<M, 2>;

  int n,q;
  cin>>n>>q;
  vector<ll> ts(q),ls(q),rs(q),ps(q);
  for(ll i=0;i<q;i++){
    cin>>ts[i];
    if(ts[i]==1) cin>>ps[i];
    if(ts[i]==2) cin>>ls[i]>>rs[i];
  }
  vector<ll> vs;
  for(ll i=0;i<q;i++){
    if(ts[i]==1){
      vs.emplace_back(ps[i]);
      vs.emplace_back(ps[i]+1);
      vs.emplace_back(ps[i]+2);
      vs.emplace_back(ps[i]+3);
    }
    if(ts[i]==2){
      vs.emplace_back(ls[i]);
      vs.emplace_back(ls[i]+1);
      vs.emplace_back(rs[i]);
      vs.emplace_back(rs[i]+1);
    }
  }
  vs.emplace_back(0);
  vs.emplace_back(n+1);
  vs=compress(vs);
  auto ms=dict(vs);

  MM A;
  A[0][0]=M(1);A[0][1]=M(1);
  A[1][0]=M(1);A[1][1]=M(0);

  vector<MM> vt(vs.size()-1,A);
  for(ll i=0;i+1<(ll)vs.size();i++){
    vt[i]=A.pow(vs[i+1]-vs[i]);
  }

  MM I=MM::mul_identity();
  auto f=[&](MM a,MM b){return b*a;};
  SegmentTree<MM> seg(f,I);
  seg.build(vt);

  vector<int> used(vs.size(),0);
  for(ll i=0;i<q;i++){
    if(ts[i]==1){
      ll k=ms[ps[i]];
      used[k]^=1;
      MM B;
      for(ll j=k;j<=k+2;j++){
        if(used[j]){
          B[0][0]=M(0);B[0][1]=M(0);
          B[1][0]=M(1);B[1][1]=M(0);
        }else{
          B[0][0]=M(!used[j-1]);B[0][1]=M(!used[j-2]);
          B[1][0]=M(1);B[1][1]=M(0);
        }
        seg.set_val(j,B);
      }
    }
    if(ts[i]==2){
      ll l=ms[ls[i]],r=ms[rs[i]];
      if(used[l]){
        cout<<0<<"\n";
        continue;
      }
      auto B=seg.query(l+1,r+1);
      cout<<B[0][0].v<<"\n";
    }
  }
  cout<<flush;
  return 0;
}
/*
  verified on 2019/10/29
  https://atcoder.jp/contests/yahoo-procon2019-final/tasks/yahoo_procon2019_final_d
*/

signed DDCC2019_FINAL_D(){
  string s;
  cin>>s;

  struct M{
    uint32_t v;
    M(){*this=add_identity();}
    M(uint32_t v):v(v){}
    M operator+(const M &a)const{return M(v+a.v);}
    M operator*(const M &a)const{return M(v*a.v);}
    static M add_identity(){return M(0);}
    static M mul_identity(){return M(1);}
  };

  using SM = SquareMatrix<M, 6>;

  auto f=[](SM a,SM b){return a*b;};
  SM ti=SM::mul_identity();
  SegmentTree<SM> seg(f,ti);
  vector<SM> vt(s.size(),ti);
  for(int i=0;i<(int)s.size();i++){
    if(s[i]=='D') vt[i][0][1]=1;
    if(s[i]=='I') vt[i][1][2]=1;
    if(s[i]=='S') vt[i][2][3]=1;
    if(s[i]=='C') vt[i][3][4]=1;
    if(s[i]=='O') vt[i][4][5]=1;
  }
  seg.build(vt);

  int q;
  cin>>q;
  for(int i=0;i<q;i++){
    int l,r;
    cin>>l>>r;
    l--;
    cout<<seg.query(l,r)[0][5].v<<"\n";
  }
  cout<<flush;
  return 0;
}
/*
  verified on 2019/10/29
  https://atcoder.jp/contests/ddcc2019-final/tasks/ddcc2019_final_d
*/

signed main(){
  //YAHOO2019_FINAL_D();
  //DDCC2019_FINAL_D();
  return 0;
}
#endif
