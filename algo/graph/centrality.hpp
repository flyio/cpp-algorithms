// 有向グラフの中心性
#include <bits/stdc++.h>
using namespace std;

template<class T> inline bool chmin(T &minval, const T &newval) { if (minval>newval) { minval=newval; return 1; } return 0; }


// 近接中心性
struct ClosenessCentrality {
    typedef pair<int,int> pii;
    typedef pii Edge;  // (cost, to)
    vector<vector<Edge>> G; int V;
    vector<int> d;
    ClosenessCentrality(int V) : G(V), V(V), d(V) {}
    void add_edge(int from, int to, int cost){ G[from].push_back({cost,to}); }
    
    double compute(int node) {
      dijkstra(node, d);
      double dsum = 0.0;
      for(int di : d) dsum += (double)di;
      return 1.0/dsum;
    }

private:
    void dijkstra(int from, vector<int> &d)
    {   // back => if not nullptr, it will contain backward node id.
        fill(d.begin(), d.end(), numeric_limits<int>::max());
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        d[from] = 0; pq.push({0, from});
        while(!pq.empty()){
            auto p = pq.top(); pq.pop();
            int v = p.second;
            if(d[v]<p.first) continue;
            for(int i=0;i<G[v].size();++i){
                auto &e = G[v][i]; int c = e.first;
                if(chmin(d[e.second], d[v]+c)){
                    pq.push({d[v]+c, e.second});  // new cost, node
                }
            }
        }
    }
};



// 媒介中心性
struct BetweenessCentrality {
    typedef pair<int,int> pii;
    typedef pii Edge;  // (cost, to)
    vector<vector<Edge>> G; int V;
    vector<int> d, back, bc; vector<bool> is_leaf;
    BetweenessCentrality(int V) : G(V), V(V), d(V), back(V), is_leaf(V), bc(V,0) {}
    void add_edge(int from, int to, int cost){ G[from].push_back({cost,to}); }

    void compute(){
        for(int u=0;u<V;++u){
            dijkstra(u, d, &back);
            for(int v=0;v<V;++v){
                if(is_leaf[v]) backward(v,back);
            }
        }
    }
private:    
    void dijkstra(int from, vector<int> &d, vector<int>* back=nullptr)
    {   // back => if not nullptr, it will contain backward node id.
        fill(d.begin(), d.end(), numeric_limits<int>::max());
        fill(is_leaf.begin(), is_leaf.end(), true);
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
                    is_leaf[v] = false;
                    if(back) back->at(e.second) = p.second;
                }
            }
        }
    }
    void backward(int to, vector<int> &back){
        int cnt = 0;
        while(back[to]>=0){
            bc[to] += cnt; cnt++; to=back[to];
        } 
    }
};

