#pragma once

#include <vector>
#include <utility>

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
  int count_groups() const { int cnt = 0; for(int x=0; x<par.size(); ++x) if(x==par[x]) cnt++; return cnt; }
};

// ポテンシャル Union-Find木
// * 通常のUF木の操作に加えて重み (ポテンシャル) を管理する機能を追加
// * root, same は同じ
// * unite(x,y,w) は x, y を unite するが，その際に weight(y)-weight(x) が w になるように重みを設定する
// * diff(x,y) は weight(y) - weight(x) を返す
// * 詳細は https://qiita.com/drken/items/cce6fc5c579051e64fab
// * See Also: (AOJ) http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B
struct PotentialUnionFind {
  int n;
  std::vector<int> par;
  std::vector<int> rank;
private:
  std::vector<int> diff_w; // diff_w[v] means the difference of weight from its parent
public:
  PotentialUnionFind(int n_) : par(n_), rank(n_,0), diff_w(n_,0), n(n_) { for(int i=0;i<n;++i) par[i] = i; }
  int root(int x) { int r; return par[x] == x ? x : (r=root(par[x]), diff_w[x]+=diff_w[par[x]], par[x]=r); }
  bool same(int x, int y) { return root(x)==root(y); }
  bool unite(int x, int y, int w) {
    w += weight(x); w-=weight(y);
    x = root(x); y = root(y);
    if(x==y) return false;
    if(rank[x] < rank[y]) std::swap(x,y), w=-w;
    if(rank[x]==rank[y]) rank[x]++;
    par[y] = x; diff_w[y] = w;
    return true;
  }
  int diff(int x, int y){ return weight(y)-weight(x); }
private:
  int weight(int x){ root(x); return diff_w[x]; }
};