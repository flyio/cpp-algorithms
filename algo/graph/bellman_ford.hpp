// Shortest path distance with Bellman-Ford (which allows negative edge costs)
#include <bits/stdc++.h>
using namespace std;

template<class T> inline bool chmin(T &minval, const T &newval) { if (minval>newval) { minval=newval; return 1; } return 0; }

struct BellmanFord {
  const int INF;
  struct edge {int from, to, cost; };
  vector<edge> G; int V, E;
  BellmanFord() : V(0), E(0), INF(numeric_limits<int>::max()) {}
  void add_edge(int from, int to, int cost){ G.push_back({from,to,cost}); V = max(max(from,to)+1,V); ++E; }

  void solve(int s, vector<int> &d, vector<int> *back=nullptr){  // s: begin node id, d: result vector of size V
    if(d.size()!=V) throw "size error";
    if(back) back->at(s) = -1;
    fill(d.begin(), d.end(), INF); d[s] = 0;
    for(int v=0;v<V;++v){
      bool update = false;
      for(edge &e : G)
        if(d[e.from] != INF)
          if(chmin(d[e.to], d[e.from]+e.cost)){
            update = true;
            if(back) back->at(e.to) = e.from;
          }
      if(!update) break;
      if(v==V-1) throw "iteration did not stop, including negative loops";
    }
  }

  // check if there exist "negative loops", whose total cost is negative
  // (note that this is different from loops with all edge costs being negative!)
  bool find_negative_loops(vector<int> &d){  // if d[u]<0, u is included in negative loops; if d[u]==0, u is not.
    fill(d.begin(),d.end(),0);
    for(int i=0;i<V;++i)
      for(edge &e : G)
        if(chmin(d[e.to], d[e.from]+e.cost) && i==V-1) return true;
    return false;
  }
};

#ifndef SP_BACKTRACK
#define SP_BACKTRACK

// Find the shortest path between the root of spanning tree (i.e. back) and the node "to"
vector<int> backward(int to, vector<int> &back){
    vector<int> path = {to};
    while(back[to]>=0) path.push_back(to=back[to]);
    reverse(path.begin(), path.end());
    return path;
}

#endif

