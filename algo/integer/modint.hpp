#include <vector>
using namespace std;


// Copy from Here!!

template <int M>
struct ModInt {
    int num;
    ModInt(): num(0){ }
    ModInt(int num): num(num){ }
    operator int () const { return num; }
    template <class T> ModInt operator + (T n) const { auto ret = num + n; return ret >= M ? ret - M : ret; }
    template <class T> ModInt operator - (T n) const { auto ret = num - n; return ret < 0 ? ret + M : ret; }
    template <class T> ModInt operator * (T n) const { return (ll)num * n % M; }
    template <class T> ModInt operator / (T n) const { return (ll)num * modInv(ModInt(n)) % M; }
    template <class T> ModInt operator >> (T n) const { return num >> n; }
    template <class T> ModInt operator << (T n) const { return ((ll)num << n) % M; }
    template <class T> ModInt operator | (T n) const { return num | n; }
    template <class T> ModInt operator & (T n) const { return num & n; }
    template <class T> bool operator < (T n) const { return num < n; }
    template <class T> bool operator > (T n) const { return num > n; }
    template <class T> bool operator <= (T n) const { return num <= n; }
    template <class T> bool operator >= (T n) const { return num >= n; }
    template <class T> bool operator == (T n) const { return num == n; }
    template <class T> bool operator != (T n) const { return num != n; }
    ModInt operator ++ (int){ int ret = num; num = num == M + 1 ? 0 : num + 1; return ret; }
    ModInt operator -- (int){ int ret = num; num = num == 0 ? M - 1 : num - 1; return ret; }
    ModInt operator ++ (){ return num = num == M + 1 ? 0 : num + 1; }
    ModInt operator -- (){ return num = num == 0 ? M - 1 : num - 1; }
    template <class T> ModInt operator += (T n){ num += n; return num = num >= M ? num - M : num; }
    template <class T> ModInt operator -= (T n){ num -= n; return num = num < 0 ? num + M : num; }
    template <class T> ModInt operator *= (T n){ return num = (ll)num * n % M; }
    template <class T> ModInt operator /= (T n){ return num = (ll)num * modInv(n) % M; }
    template <class T> ModInt operator >>= (T n){ return num = num >> n; }
    template <class T> ModInt operator <<= (T n){ return num = ((ll)num << n) % M; }
    friend ModInt modPow(ModInt base, ModInt ex) {
        ModInt ret = 1;
        while(ex.num){
            if(ex.num & 1){ ret = ret * base; }
            ex >>= 1;
            base = base * base;
        }
        return ret;
    }
    static vector<ModInt> mFacts, mInvFacts;
    friend ModInt modFact(ModInt n){ return mFacts[n.num]; }        // 階乗: n! 
    friend ModInt modInvFact(ModInt n){ return mInvFacts[n.num]; }  // 階乗分の1: 1/n!
    friend ModInt modInv(ModInt n){ return modPow(n, M - 2); }      // 1/n
    friend ModInt modC(ModInt n, ModInt k){ return modFact(n) * modInvFact(k) * modInvFact(n - k); }  // nCk
    static void init(int n){
        mFacts.resize(n + 1);
        mInvFacts.resize(n + 1);
        mFacts[0] = 1;
        for(int i = 1; i <= n; i++){
            mFacts[i] = mFacts[i - 1] * i;
        }
        mInvFacts[n] = modInv(mFacts[n]);
        for(int i = n - 1; i >= 0; i--){
            mInvFacts[i] = mInvFacts[i + 1] * (i + 1);
        }
    }
    friend istream& operator >> (istream& in, ModInt& e){ return in >> e.num; }
    friend ostream& operator << (ostream& out, const ModInt& e) { return out << e.num; }
};

template <int M>
vector<ModInt<M>> ModInt<M>::mFacts;
template <int M>
vector<ModInt<M>> ModInt<M>::mInvFacts;
// using mint = ModInt<998244353>;
using mint = ModInt<1000000007>;

// End
