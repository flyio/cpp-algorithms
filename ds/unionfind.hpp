#pragma once

#include <vector>

struct UnionFind {
  int n;
  std::vector<int> par;
  std::vector<int> rank;
  UnionFind(int n_) : par(n_), rank(n_,0), n(n_) { for(int i=0;i<n;++i) par[i] = i; }
  int root(int x) { return par[x] == x ? x : (par[x]=root(par[x])); }
  bool same(int x, int y) { return root(x)==root(y); }
  void unite(int x, int y) {
    x = root(x); y = root(y);
    if(x==y) return;
    if(rank[x] < rank[y]) par[x] = y;
    else {
      par[y] = x;
      if(rank[x]==rank[y]) rank[x]++;
    }
  }
};
