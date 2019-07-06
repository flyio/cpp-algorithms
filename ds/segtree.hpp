#include <bits/stdc++.h>
using namespace std;


struct SegTree {
  // なるべく汎用的になるように書いたセグ木のクラス
  // * 使う際には update と query メソッドを実装する
  // * 配列の添字は0-basedを仮定 / Interval は半開区間 [l,r) としている（問題の設定に注意!!）
  // * Interval クラスはポインタレスな二分木のノードに対応していて，子ノード，親ノードへ自由に行き来できる

  using T = int;  // 配列のデータ型
  vector<T> dat;
  int n;
  T default_value;

  struct Interval {
    // セグ木の範囲のためのクラス (セグ木のノードに一対一対応する)
    int node_id, left, right;  // id はノードID
    inline bool intersects(Interval &other) const { return (right<=other.left) || (other.right<=left); }
    inline bool includes(Interval &other) const { return (left<=other.left) && (other.right<=right); }
    inline Interval left_child() const { return {2*node_id+1, left, (left+right)/2 }; };
    inline Interval right_child() const { return {2*node_id+2, (left+right)/2, right }; };
    inline Interval parent() const {
      assert(!is_root());
      bool is_left = (node_id%2==1);
      if(is_left) return { (node_id-1)/2, left, 2*right-left };
      else return { (node_id-1)/2, 2*left-right, right };
    }
    inline bool is_root() const { return node_id==0; }
  };


  // 実装すべきもの = update & query
  // 典型的には2パターンの走査がある
  // 1. 配列添字 i を決めて対応する子ノードから根まで上昇する (RMQのサンプルでは update 関数内)
  // 2. 範囲 [l,r) を決めてそれに対応するノード (一般には複数ノード) をスキャンする (RMQのサンプルでは query 関数内)
  // [Remark] RMQ のケースでは pattern 1 = update / pattern 2 = query だったが，逆になる場合もある．例えば
  //          Range Add Query / Range Update Query などは逆になるパターン (See AOJ)
  void update(int i, T val){
    // i番目の要素にvalを適用する
    Interval node = get_node(i);
    (*this)[node] = val;  // RMQ の場合
    while(!node.is_root()){
      node = node.parent();
      (*this)[node] = min((*this)[node], val); // RMQ の場合
    }
  }
  T query(int left, int right){
    Interval q = {-1, left, right};
    return query(q, root());
  }
  T query(Interval &q, Interval i){
    if(!q.intersects(i)) return default_value;  // RMQ の場合
    else if(q.includes(i)) return (*this)[i];   // RMQ の場合
    else {
      T vl = query(q, i.left_child());  // RMQ
      T vr = query(q, i.right_child()); // RMQ
      return min(vl, vr);             // RMQ
    }
  }

  SegTree(int n_, T default_value) : default_value(default_value) {
    // n_: 配列サイズ
    // default_value: 配列の初期値
    init(n_, default_value);
  }
protected:
  // 根を取得
  Interval root() const { return {0, 0, n}; }
  // 配列の i 番目の要素に対応する葉ノードを得る (範囲の大きさは1)
  Interval get_node(int i) const { return {i+n-1, i, i+1}; }
  // 範囲に対応する値への参照を返す
  T& operator[](Interval &lr) { return dat[lr.node_id]; }
  // 木ノードの移動関連 (通常は Interval クラスを使えば十分なので使わない)
  inline int parent(int node) const { return (node-1)/2; }
  inline int left_child(int node) const { return 2*node+1; }  // おアノード
  inline int right_child(int node) const { return 2*node+2; }
  inline int is_root(int node) const { return node==0; }

  // 木の初期化
  void init(int n_, T default_value){
    int n=1; while(n<n_) n*=2; dat.resize(n, default_value);
  }
};