#ifndef call_from_test
#include<bits/stdc++.h>
using namespace std;

#define call_from_test
#include "dinic.cpp"
#undef call_from_test

#endif
//BEGIN CUT HERE
template<typename T>
struct LeastFlow{
  Dinic<T, true> G;
  int X,Y;
  T sum;
  LeastFlow(int n):G(n+2),X(n),Y(n+1),sum(0){}

  void add_edge(int from,int to,T low,T hgh){
    assert(low<=hgh);
    G.add_edge(from,to,hgh-low);
    G.add_edge(X,to,low);
    G.add_edge(from,Y,low);
    sum+=low;
  }

  T flow(int s,int t){
    T a=G.flow(X,Y);
    T b=G.flow(s,Y);
    T c=G.flow(X,t);
    T d=G.flow(s,t);
    return (b==c&&a+b==sum)?b+d:T(-1);
  }
};
//END CUT HERE
#ifndef call_from_test
//INSERT ABOVE HERE

class SRMDiv0Easy {
public:
  int get(int N, vector <int> L, vector <int> R, vector <int> X, vector <int> Y) {
    int M=L.size();
    LeastFlow<int> G(N+1);
    int S=0,T=N;
    for(int i=0;i<M;i++)
      G.add_edge(L[i],R[i]+1,X[i],Y[i]);
    return G.flow(S,T);
  }
};
/*
  verified on 2019/06/10
  https://vjudge.net/problem/TopCoder-14319
*/
#endif
