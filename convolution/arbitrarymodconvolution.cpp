#ifndef call_from_test
#include<bits/stdc++.h>
using namespace std;

#define call_from_test
#include "fastfouriertransform.cpp"
#undef call_from_test

#endif
//BEGIN CUT HERE
template<typename T>
struct ArbitraryModConvolution{
  using dbl=FFT::dbl;
  using num=FFT::num;

  vector<T> multiply(vector<T> as,vector<T> bs){
    int need=as.size()+bs.size()-1;
    int sz=1;
    while(sz<need) sz<<=1;
    vector<num> fa(sz),fb(sz);
    for(int i=0;i<(int)as.size();i++)
      fa[i]=num(as[i].v&((1<<15)-1),as[i].v>>15);
    for(int i=0;i<(int)bs.size();i++)
      fb[i]=num(bs[i].v&((1<<15)-1),bs[i].v>>15);

    fft(fa);fft(fb);

    dbl ratio=0.25/sz;
    num r2(0,-1),r3(ratio,0),r4(0,-ratio),r5(0,1);
    for(int i=0;i<=(sz>>1);i++){
      int j=(sz-i)&(sz-1);
      num a1=(fa[i]+conj(fa[j]));
      num a2=(fa[i]-conj(fa[j]))*r2;
      num b1=(fb[i]+conj(fb[j]))*r3;
      num b2=(fb[i]-conj(fb[j]))*r4;
      if(i!=j){
        num c1=(fa[j]+conj(fa[i]));
        num c2=(fa[j]-conj(fa[i]))*r2;
        num d1=(fb[j]+conj(fb[i]))*r3;
        num d2=(fb[j]-conj(fb[i]))*r4;
        fa[i]=c1*d1+c2*d2*r5;
        fb[i]=c1*d2+c2*d1;
      }
      fa[j]=a1*b1+a2*b2*r5;
      fb[j]=a1*b2+a2*b1;
    }
    fft(fa);fft(fb);

    vector<T> cs(need);
    using ll = long long;
    for(int i=0;i<need;i++){
      ll aa=T(llround(fa[i].x)).v;
      ll bb=T(llround(fb[i].x)).v;
      ll cc=T(llround(fa[i].y)).v;
      cs[i]=T(aa+(bb<<15)+(cc<<30));
    }
    return cs;
  }
};
//END CUT HERE
#ifndef call_from_test

#define call_from_test
#include "../tools/fastio.cpp"
#include "../mod/mint.cpp"
#include "../mod/enumeration.cpp"
#undef call_from_test

//INSERT ABOVE HERE
signed YUKI_829(){
  int n,b;
  cin>>n>>b;
  vector<int> s(n);
  for(int i=0;i<n;i++) cin>>s[i];
  using M = Mint<int>;
  using E = Enumeration<M>;
  E::init(3e5);

  vector<int> cnt(n,0);
  for(int i=0;i<n;i++) cnt[s[i]]++;

  using P = pair<int, vector<M> > ;
  priority_queue<P> pq;
  pq.emplace(-1,vector<M>(1,1));

  int sum=0;
  for(int i=n-1;i>=0;i--){
    if(cnt[i]==0) continue;
    M x=E::H(sum,cnt[i]);
    M y=E::H(sum+1,cnt[i])-x;
    x*=E::Fact(cnt[i]);
    y*=E::Fact(cnt[i]);

    pq.emplace(-2,vector<M>({x,y}));
    sum+=cnt[i];
  }

  ArbitraryModConvolution<M> arb;
  while(pq.size()>1u){
    auto as=pq.top().second;pq.pop();
    auto bs=pq.top().second;pq.pop();
    auto cs=arb.multiply(as,bs);
    pq.emplace(-(int)cs.size(),cs);
  }

  auto dp=pq.top().second;
  M ans(0),res(1);
  for(int j=0;j<(int)dp.size();j++){
    ans+=M(j)*dp[j]*res;
    res*=M(b);
  }
  cout<<ans.v<<endl;
  return 0;
}
/*
  verified on 2019/10/24
  https://yukicoder.me/problems/no/829
*/

signed main(){
  YUKI_829();
  return 0;
}
#endif
