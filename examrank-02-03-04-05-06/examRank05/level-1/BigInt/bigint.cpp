#include "bigint.hpp"
#include <cctype>
#include <climits>   // ULONG_MAX
#include <algorithm> // std::max

// --- util local (C++98) ---
static void trim_inplace(std::string& s){
    std::string::size_type i=0, j=s.size();
    while (i<j && std::isspace((unsigned char)s[i])) ++i;
    while (j>i && std::isspace((unsigned char)s[j-1])) --j;
    s = s.substr(i, j-i);
}

static bool all_digits(const std::string& s){
    if (s.empty()) return false;
    for (std::string::size_type i=0;i<s.size();++i)
        if (!std::isdigit((unsigned char)s[i])) return false;
    return true;
}

// --- regra dos três ---
bigint::bigint() : d_(1,0) {}

bigint::bigint(int n){
    if (n <= 0) { d_.assign(1,0); return; }
    while (n) { d_.push_back(n%10); n/=10; }
}

bigint::bigint(const std::string& raw){
    std::string s = raw;
    trim_inplace(s);
    if (s.empty()) { d_.assign(1,0); return; }
    if (s[0]=='-') { d_.assign(1,0); return; } // unsigned: negativo => 0
    if (s[0]=='+') s.erase(0,1);
    if (!all_digits(s)) { d_.assign(1,0); return; }
    std::string::size_type k=0; while (k<s.size() && s[k]=='0') ++k;
    if (k==s.size()) { d_.assign(1,0); return; }
    for (std::string::size_type i=s.size(); i-- > k; ) d_.push_back(s[i]-'0');
    normalize();
}

bigint::bigint(const bigint& o) : d_(o.d_) {}
bigint::~bigint() {}
bigint& bigint::operator=(const bigint& o){ if(this!=&o) d_=o.d_; return *this; }

// --- básicos ---
void bigint::normalize(){
    while (d_.size()>1 && d_.back()==0) d_.pop_back();
    if (d_.empty()) d_.assign(1,0);
}

int bigint::cmpAbs(const bigint& a, const bigint& b){
    if (a.d_.size()!=b.d_.size()) return a.d_.size()<b.d_.size() ? -1:1;
    for (std::vector<int>::size_type i=a.d_.size(); i-- > 0; ){
        if (a.d_[i]!=b.d_[i]) return a.d_[i]<b.d_[i] ? -1:1;
    }
    return 0;
}

unsigned long bigint::to_ul(const bigint& n){
    unsigned long x=0UL;
    for (std::vector<int>::size_type i=n.d_.size(); i-- > 0; ){
        if (x > ULONG_MAX/10UL) return ULONG_MAX; // saturar
        x = x*10UL + (unsigned long)n.d_[i];
        if (x < (unsigned long)n.d_[i]) return ULONG_MAX; // proteção
    }
    return x;
}

void bigint::shl_digits(unsigned long k){
    if (!k) return;
    if (d_.size()==1 && d_[0]==0) return;
    d_.insert(d_.begin(), (std::vector<int>::size_type)k, 0);
}

void bigint::shr_digits(unsigned long k){
    if (!k) return;
    if (k >= d_.size()) { d_.assign(1,0); return; }
    d_.erase(d_.begin(), d_.begin() + (std::vector<int>::size_type)k);
    normalize();
}

// --- impressão ---
std::string bigint::to_string() const{
    std::string s; s.reserve(d_.size());
    for (std::vector<int>::size_type i=d_.size(); i-- > 0; ) s.push_back(char('0'+d_[i]));
    return s.empty()? std::string("0") : s;
}

// --- comparações ---
bool bigint::operator<(const bigint& r) const { return cmpAbs(*this,r) < 0; }

// --- soma ---
bigint bigint::operator+(const bigint& r) const{
    bigint out; out.d_.clear();
    int carry=0;
    std::vector<int>::size_type n = d_.size()>r.d_.size()?d_.size():r.d_.size();
    for (std::vector<int>::size_type i=0; i<n || carry; ++i){
        int a = (i<d_.size()?d_[i]:0), b = (i<r.d_.size()?r.d_[i]:0);
        int s = a+b+carry;
        out.d_.push_back(s%10);
        carry = s/10;
    }
    out.normalize();
    return out;
}
bigint& bigint::operator+=(const bigint& r){ return *this = *this + r; }

// --- ++ ---
bigint& bigint::operator++(){ // prefixo
    int i=0, carry=1;
    while (carry){
        if (i==(int)d_.size()) d_.push_back(0);
        int s = d_[i]+carry; d_[i]=s%10; carry=s/10; ++i;
    }
    return *this;
}
bigint bigint::operator++(int){ bigint old(*this); ++(*this); return old; }

// --- digitshift (int) ---
bigint bigint::operator<<(int n) const{
    if (n <= 0) return *this >> (-n);
    bigint t(*this); t.shl_digits((unsigned long)n); return t;
}

bigint bigint::operator>>(int n) const{
    if (n <= 0) return *this << (-n);
    bigint t(*this); t.shr_digits((unsigned long)n); return t;
}

bigint& bigint::operator<<=(int n){ if (n>=0) shl_digits((unsigned long)n); else shr_digits((unsigned long)(-n)); return *this; }

bigint& bigint::operator>>=(int n){ if (n>=0) shr_digits((unsigned long)n); else shl_digits((unsigned long)(-n)); return *this; }

// --- digitshift (bigint) ---
bigint bigint::operator<<(const bigint& n) const{ bigint t(*this); t.shl_digits(to_ul(n)); return t; }

bigint bigint::operator>>(const bigint& n) const{ bigint t(*this); t.shr_digits(to_ul(n)); return t; }

bigint& bigint::operator<<=(const bigint& n){ shl_digits(to_ul(n)); return *this; }

bigint& bigint::operator>>=(const bigint& n){ shr_digits(to_ul(n)); return *this; }

