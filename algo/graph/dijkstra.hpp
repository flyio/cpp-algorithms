#include <bits/stdc++.h>
using namespace std;

template<class T> inline bool chmin(T &minval, const T &newval) { if (minval>newval) { minval=newval; return 1; } return 0; }

// Dijkstra for a weighted directed graph
//   G => adjlist
struct Dijkstra {
    typedef pair<int,int> pii;
    typedef pii Edge;  // (cost, to)
    vector<vector<Edge>> G; int V;
    Dijkstra(int V) : G(V), V(V) {}
    void add_edge(int from, int to, int cost){ G[from].push_back({cost,to}); }
    
    void solve(int from, vector<int> &d, vector<int>* back=nullptr)
    {   // back => if not nullptr, it will contain backward node id.
        fill(d.begin(), d.end(), numeric_limits<int>::max());
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        if(back) back->at(from) = -1;
        d[from] = 0; pq.push({0, from});
        while(!pq.empty()){
            auto p = pq.top(); pq.pop();
            int v = p.second;
            if(d[v]<p.first) continue;
            for(int i=0;i<G[v].size();++i){
                auto &e = G[v][i]; int c = e.first;
                if(chmin(d[e.second], d[v]+c)){
                    pq.push({d[v]+c, e.second});  // new cost, node
                    if(back) back->at(e.second) = p.second;
                }
            }
        }
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