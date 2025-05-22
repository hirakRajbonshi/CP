// const int mod = 1000000007;
const int mod = 998244353;
struct Mint
{
    int x;
    Mint() : x(0) {}
    Mint(int _x)
    {
        _x %= mod;
        if (_x < 0)
            _x += mod;
        x = _x;
    }

    int val() { return x; }

    Mint &operator++()
    {
        x++;
        if (x == mod)
            x = 0;
        return *this;
    }
    Mint &operator--()
    {
        if (!x)
            x = mod;
        x--;
        return *this;
    }
    Mint &operator+=(const Mint &other)
    {
        x += other.x;
        if (x >= mod)
            x -= mod;
        return *this;
    }
    Mint &operator-=(const Mint &other)
    {
        x -= other.x;
        if (x < 0)
            x += mod;
        return *this;
    }
    Mint &operator*=(const Mint &other)
    {
        x = x * other.x % mod;
        return *this;
    }
    Mint &operator/=(const Mint &other)
    {
        return *this *= other.inv();
    }
    Mint operator+() const
    {
        return *this;
    }
    Mint operator-() const
    {
        return Mint() - *this;
    }

    //
    Mint operator+(const Mint &other) const
    {
        return Mint(*this) += other;
    }
    Mint operator-(const Mint &other) const
    {
        return Mint(*this) -= other;
    }
    Mint operator*(const Mint &other) const
    {
        return Mint(*this) *= other;
    }
    Mint operator/(const Mint &other) const
    {
        return Mint(*this) /= other;
    }

    bool operator==(const Mint &other) const
    {
        return x == other.x;
    }
    bool operator!=(const Mint &other) const
    {
        return x != other.x;
    }
    bool operator>=(const Mint &other) const
    {
        return x >= other.x;
    }
    bool operator<=(const Mint &other) const
    {
        return x <= other.x;
    }
    bool operator>(const Mint &other) const
    {
        return x > other.x;
    }
    bool operator<(const Mint &other) const
    {
        return x < other.x;
    }
    Mint power(int p) const
    {
        assert(p >= 0);
        Mint b = *this, res = 1;
        while (p)
        {
            if (p & 1)
                res *= b;
            b *= b;
            p >>= 1;
        }
        return res;
    }
    Mint inv() const
    {
        assert(x);
        return power(mod - 2);
    }
    friend ostream &operator<<(ostream &os, const Mint &m)
    {
        os << m.x;
        return os;
    }
};

struct Factorials
{
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

Factorials F(5e5 + 10);