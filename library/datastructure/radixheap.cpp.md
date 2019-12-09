---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: datastructure/radixheap.cpp
* category: datastructure


[Back to top page](../../index.html)



## Verified
* :heavy_check_mark: [test/aoj/1607.test.cpp](../../verify/test/aoj/1607.test.cpp.html)
* :heavy_check_mark: [test/aoj/GRL_1_A.test.cpp](../../verify/test/aoj/GRL_1_A.test.cpp.html)


## Code
{% raw %}
```cpp
#ifndef call_from_test
#include<bits/stdc++.h>
using namespace std;
#endif
//BEGIN CUT HERE
// prohibited to push an element less than popped one
// Key: int or long long
template<typename K,typename V>
struct RadixHeap{
  static constexpr int bit = sizeof(K) * 8;
  array<vector< pair<K, V> >, bit> vs;

  int size;
  K last;
  RadixHeap():size(0),last(0){}

  bool empty() const{return size==0;}

  inline int getbit(int a){
    return a?bit-__builtin_clz(a):0;
  }

  inline int getbit(long long a){
    return a?bit-__builtin_clzll(a):0;
  }

  void emplace(K key,V val){
    size++;
    vs[getbit(key^last)].emplace_back(key,val);
  }

  pair<K, V> pop(){
    if(vs[0].empty()){
      int idx=1;
      while(vs[idx].empty()) idx++;
      last=min_element(vs[idx].begin(),vs[idx].end())->first;
      for(auto &p:vs[idx]) vs[getbit(p.first^last)].emplace_back(p);
      vs[idx].clear();
    }
    --size;
    auto res=vs[0].back();
    vs[0].pop_back();
    return res;
  }
};
//END CUT HERE
#ifndef call_from_test
//INSERT ABOVE HERE
signed main(){
  return 0;
}
#endif

```
{% endraw %}

[Back to top page](../../index.html)
