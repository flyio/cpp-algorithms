#include <bits/stdc++.h>
using namespace std;

struct Knapsack01 { // 各アイテム最大1個まで
    void add_item(int vi, int wi){ v.push_back(vi); w.push_back(wi);}
    int solve(int W){
        int n=v.size(); vector<int> dp(W+1,0);
        for(int i=0;i<n;++i)
            for(int j=W;j>=w[i];--j)
                dp[j] = max(dp[j],dp[j-w[i]]+v[i]);
        return dp[W];
    }
    vector<int> v, w;  // val, wei
};

struct KnapsackNolim { // 各アイテムの個数制限なし
    void add_item(int vi, int wi){ v.push_back(vi); w.push_back(wi);}
    int solve(int W){
        int n=v.size(); vector<int> dp(W+1,0);
        for(int i=0;i<n;++i)
            for(int j=w[i];j<W+1;++j)
                dp[j] = max(dp[j],dp[j-w[i]]+v[i]);
        return dp[W];
    }
    vector<int> v, w;  // val, wei
};
