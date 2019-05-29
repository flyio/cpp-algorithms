#pragma once

#include <map>

using namespace std;

// vector出力
template<typename T>
ostream& operator << (ostream& os, vector<T>& vec) {
    os << "{";
    for (int i = 0; i<vec.size(); i++) {
        os << vec[i] << (i + 1 == vec.size() ? "" : ", ");
    }
    os << "}";
    return os;
}

// map出力
template<typename T, typename U>
ostream& operator << (ostream& os, map<T,U>& map_var) {
    os << "{";
    for (typename map<T, U>::iterator itr = map_var.begin(); itr != map_var.end(); itr++) {
        os << "(" << itr->first << ", " << itr->second << ")";
        itr++;
        if(itr != map_var.end()) os << ", ";
        itr--;
    }
    os << "}";
    return os;
}

// set 出力
template<typename T>
ostream& operator << (ostream& os, set<T>& set_var) {
    os << "{";
    for (auto itr = set_var.begin(); itr != set_var.end(); itr++) {
        os << *itr;
        ++itr;
        if(itr != set_var.end()) os << ", ";
        itr--;
    }
    os << "}";
    return os;
}

// 再帰の終端。引数が0個の場合を担当。改行を出力。
void dump_func() {
    cerr << endl;
}
// 可変長引数。引数が1つ以上存在する場合を担当。
// 最初の引数をHead、残りをTailとして切り離すことを再帰的に行う。
template <class Head, class... Tail>
void dump_func(Head&& head, Tail&&... tail)
{
    cerr << head;
    if (sizeof...(Tail) == 0) {
        cerr << " ";
    }
    else {
        cerr << ", ";
    }
    dump_func(std::move(tail)...);
}

#define dump(...) cerr<<"  "; \
cerr << #__VA_ARGS__<<" :[line "<<__LINE__<<":"<<__FUNCTION__<<"]"<<endl; \
cerr<<"    "; \
dump_func(__VA_ARGS__)
