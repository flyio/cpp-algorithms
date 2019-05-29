// Segtree for Range Minimum Queries (RMQs)
#include<bits/stdc++.h>
using namespace std;

template <class T>  // T can be any class (operator< must be implemented)
struct RMQ {
  int n; vector<T> a; T themax;
  // n_: size of array, themax: something like numeric_limits<int>::max()
  RMQ(int n_, T themax) : n(1), themax(themax) {
    while(n<n_) n*=2;
    a.resize(2*n-1, themax);
    cout << "n=" << n << endl;
  }
  void update(int k, T val){
    k += n-1; a[k] = val;
    while(k>0){ k = (k-1)/2; a[k]=min(a[2*k+1], a[2*k+2]); }  // going up towards the root;
  }
  // find minimum within a[i,j)
  T query(int i, int j){ return query(i,j,0,0,n); }
  T query(int i, int j, int k, int l, int r){
    if(r<=i || j<=l) return themax;
    if(i<=l && r<=j) return a[k];
    else {
      T vl = query(i,j,2*k+1,l,(l+r)/2);
      T vr = query(i,j,2*k+2,(l+r)/2,r);
      return min(vl,vr);
    }
  }
};