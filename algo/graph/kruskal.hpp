// Compute minimum spanning tree (and its cost)
#include <bits/stdc++.h>
using namespace std;

struct Edge {
  int from, to, cost;
};

// undirected graph
void add_edge(int from, int to, int cost, vector<Edge> &G){
  if(from>to) swap(from, to);
  G.push_back({from, to, cost});
}

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

int kruskal(vector<Edge> &G){
  int ret = 0;
  UnionFind S(G.size());
  auto comp = [](Edge e1, Edge e2) { return e1.cost < e2.cost; };
  sort(G.begin(), G.end(), comp);
  for(Edge &e : G){
    if(!S.same(e.from, e.to)){
      ret += e.cost;
      S.unite(e.from, e.to);
    }
  }
  return ret;
}