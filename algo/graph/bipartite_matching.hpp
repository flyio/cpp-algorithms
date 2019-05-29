// Solving bipartitle matching using Ford-Fulkerson
// This implementation is more efficient than naive adjacency matrix impl
// for maxflow + general graphs

#include <bits/stdc++.h>
using namespace std;

struct BipartiteMatching {
    int m, n;
    vector<vector<int> > G;
    vector<bool> used; vector<int> match;
    BipartiteMatching(int m, int n) : m(m), n(n), G(m+n), used(m+n), match(m+n) {}

    void add_edge(int u, int v){  // 0 <= u < m && 0 <= v < n
        if( !(0<=u&&u<m&&0<=v&&v<n) ) throw domain_error("invalid edge"); 
        G[u].push_back(m+v); G[m+v].push_back(u);
    }
    int solve(){
        int nmatch = 0;
        fill(match.begin(), match.end(), -1);
        for(int v=0;v<m+n;++v)
            if(match[v]<0){ fill(used.begin(),used.end(),false); if(dfs(v)) nmatch++; }
        return nmatch;  // after solving, we can extract matching by seeing match[u]
    }
    bool check_match(int i, int j){ return match[i]==m+j; }  // 0 <= u < m && 0 <= v < n

private:
    bool dfs(int v){  // check if there exists a path from v to t
        used[v] = true;
        for(int i=0;i<G[v].size();++i){
            int u = G[v][i], w = match[u];
            if(w<0 || !used[w] && dfs(w)) { match[v] = u; match[u] = v; return true; }
        }
        return false;
    }
};



