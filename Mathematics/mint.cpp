template<class T>
T power(T a, int b) {
    T res = 1;
    for(; b; b >>= 1, a *= a)
        if(b & 1) res *= a;
    return res;
}

template<int mod = 998244353>
struct mint
{
    int x;
    mint() : x(0) {}
    mint(int _x)
    {
        _x %= mod;
        if (_x < 0)
            _x += mod;
        x = _x;
    }

    int val() { return x; }

    mint &operator++()
    {
        x++;
        if (x == mod)
            x = 0;
        return *this;
    }
    mint &operator--()
    {
        if (!x)
            x = mod;
        x--;
        return *this;
    }
    mint &operator+=(const mint &other)
    {
        x += other.x;
        if (x >= mod)
            x -= mod;
        return *this;
    }
    mint &operator-=(const mint &other)
    {
        x -= other.x;
        if (x < 0)
            x += mod;
        return *this;
    }
    mint &operator*=(const mint &other)
    {
        x = x * other.x % mod;
        return *this;
    }
    mint &operator/=(const mint &other)
    {
        return *this *= other.inv();
    }
    mint operator+() const
    {
        return *this;
    }
    mint operator-() const
    {
        return mint() - *this;
    }

    //
    mint operator+(const mint &other) const
    {
        return mint(*this) += other;
    }
    mint operator-(const mint &other) const
    {
        return mint(*this) -= other;
    }
    mint operator*(const mint &other) const
    {
        return mint(*this) *= other;
    }
    mint operator/(const mint &other) const
    {
        return mint(*this) /= other;
    }

    bool operator==(const mint &other) const
    {
        return x == other.x;
    }
    bool operator!=(const mint &other) const
    {
        return x != other.x;
    }
    bool operator>=(const mint &other) const
    {
        return x >= other.x;
    }
    bool operator<=(const mint &other) const
    {
        return x <= other.x;
    }
    bool operator>(const mint &other) const
    {
        return x > other.x;
    }
    bool operator<(const mint &other) const
    {
        return x < other.x;
    }
    mint power(int p) const
    {
        assert(p >= 0);
        mint b = *this, res = 1;
        while (p)
        {
            if (p & 1)
                res *= b;
            b *= b;
            p >>= 1;
        }
        return res;
    }
    mint inv() const
    {
        assert(x);
        return power(mod - 2);
    }
    friend ostream &operator<<(ostream &os, const mint &m)
    {
        os << m.x;
        return os;
    }
    friend istream &operator>>(istream &is, mint &m)
    {
        int val;
        is >> val;
        m = mint(val);
        return is;
    }
    friend mint operator+(int lhs, const mint &rhs) { return mint(lhs) + rhs; }
    friend mint operator-(int lhs, const mint &rhs) { return mint(lhs) - rhs; }
    friend mint operator*(int lhs, const mint &rhs) { return mint(lhs) * rhs; }
    friend mint operator/(int lhs, const mint &rhs) { return mint(lhs) / rhs; }
};
template<int mod = 998244353>
struct Factorials
{
    using Mint = mint<mod>;
    int n;
    vector<Mint> fact, invf;

    Factorials(int _n) : n(_n)
    {
        fact.resize(n + 1);
        invf.resize(n + 1);

        fact[0] = 1;
        for (int i = 1; i <= n; i++)
        {
            fact[i] = fact[i - 1] * i;
        }
        invf[n] = fact[n].inv();
        for (int i = n - 1; i >= 0; i--)
        {
            invf[i] = invf[i + 1] * (i + 1);
        }
    }

    Mint C(int n, int r)
    {
        assert(n >= 0 || r >= 0 || n >= r);
        if (n == r)
            return Mint(1);
        return fact[n] * invf[r] * invf[n - r];
    }
    Mint P(int n, int r)
    {
        assert(n >= 0 || r >= 0 || n >= r);
        return fact[n] * invf[r];
    }

};
const int m = 1e9 + 7;
using Mint = mint<m>;
// Factorials F(5e5 + 10);
