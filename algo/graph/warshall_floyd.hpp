// 全ノードペア間最短経路
#include <bits/stdc++.h>
using namespace std;

template <class Matrix>
void init_warshall_floyd(Matrix d, int V){
    for(int i=0;i<V;++i)
        for(int j=0;j<V;++j)
            d[i][j] = (i==j) ? 0 : (numeric_limits<int>::max()/2);
    // 初期化後にエッジコストを設定する必要あり
}

template <class Matrix>
void warshall_floyd(Matrix &d, int V){
    // [input] d: 隣接行列 (size: V x V) d[i][j] は (i,j) のコスト
    //         (エッジがない場合「無限大」にする．オーバーフローを避けるため
    //          numeric_limits<int>::max() を使ってはいけない)
    // [output] d[i][j] が (i,j) の最短経路長となる
    for(int k=0;k<V;++k) d[k][k] = 0;  // for safety
    for(int k=0;k<V;++k)
        for(int i=0;i<V;++i)
            for(int j=0;j<V;++j)
                d[i][j] = min(d[i][j], d[i][k]+d[k][j]);
}