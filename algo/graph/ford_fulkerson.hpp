// Maxflow

#include <bits/stdc++.h>
using namespace std;

struct FordFulkerson {
    int n;
    vector<bool> used;
    vector<vector<int>> capa;
    FordFulkerson(int n) : n(n), used(n), capa(n) {
        for(int i=0;i<n;++i) capa[i].resize(n,0);
    }
    inline void set_capa(int u, int v, int c){
        capa[u][v] = c;
    }
    int dfs(int u, int t, int f){
        if(u==t) return f;
        used[u] = true;  // "labeling"
        for(int v=0;v<n;++v){
            if(!used[v] && capa[u][v]>0){
                int d = dfs(v,t,min(f,capa[u][v]));
                if(d>0){ capa[u][v] -= d; capa[v][u] += d; return d; }
            }
        }
        return 0;
    }
    int solve(int s, int t){
        int flow = 0;
        while(true){
            fill(used.begin(), used.end(), false); // reset labels
            int f = dfs(s,t,numeric_limits<int>::max());
            if(f==0) return flow;
            flow += f;
        }
        return 0;  // never comes here
    }
};
