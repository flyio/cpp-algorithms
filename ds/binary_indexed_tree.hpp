// Binary Indexed Tree (BIT)
//  Supported queries:
//  1. prefix_sum(i) => returns sum(a[0..i))
//  2. increment(i, x) => increment a[i] by x

#include <bits/stdc++.h>
using namespace std;

struct BinaryIndexedTree {
  vector<int> x; int n;
  BinaryIndexedTree(int n) : x(n+1,0), n(n) {}
  void add(int i, int a){
    i+=1; while(i<=n){ x[i]+=a; i+=(i&-i); }
  }
  int prefix_sum(int i){
    int s=0;
    while(i>0) { s+=x[i]; i-=(i&-i); }
    return s;
  }
};