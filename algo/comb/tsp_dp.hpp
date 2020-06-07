// 巡回セールスマン問題をDPで解く (N=16くらいまで)

#include <bits/stdc++.h>

using namespace std;

template <class T>
T tsp_dp_rec(int from, int state, int to, vector<vector<T>> &dist, vector<vector<T>> &memo, bool non_loop_tsp){
  if(state==0) {
    if(non_loop_tsp)
      return dist[from][to];  // from に戻ってくる制約があるとき
    else 
      return 0;               // from に戻る必要がないとき
  }
    
  if(memo[from][state]!=numeric_limits<T>::max())
    return memo[from][state];  // use memo
  int n = dist.size();
  T d_min = numeric_limits<T>::max();
  for(int v=0;v<n;++v){  // まだ訪れていない頂点を順番に訪れる
    if((state>>v) & 1){  // = state変数の v-th ビットが ON になっているとき
      int new_state = state;
      new_state &= ~(1<<v);  // 次の状態は現在の状態の v-th ビットを OFF にしたもの
      d_min = min(d_min, dist[from][v] + tsp_dp_rec(v, new_state, to, dist, memo));
    }
  }
  memo[from][state] = d_min;
  return d_min;
}

template <class T>  // 距離の型
T tsp_dp(vector<vector<T>> &dist, bool non_loop_tsp=false){  // 暗黙的に v=0 から出発するものとしている / non_loop_tsp = true だと v=0 に戻ってこない
  int n = dist.size();
  if(n>20){
    cerr << "input size too large" << endl;
    exit(-1);
  }

  int num_states = 1;
  for(int i=0; i<n; ++i) num_states *= 2;  // 状態数 = 2^n
  vector<vector<T>> memo(n, vector<T>(num_states,numeric_limits<T>::max()));  // メモ化再帰のためのバッファ

  int state = num_states - 1;  // 状態．v-th ビットが ON のときは v はまだ訪れていない / OFF のときはすでに訪れた (ので二度目は行けない)
  return tsp_dp_rec(0,state,0,dist,memo,non_loop_tsp);  // start from v=0, passing nodes with 1, end at v=0
}

