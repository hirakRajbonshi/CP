// mod is not used in this code
// add mod if required
template <class T>
struct Matrix
{
    int n, m;
    vector<vector<T>> a;
    Matrix(int _n) : n(_n), m(_n), a(_n, vector<T>(_n, T(0))) {}
    Matrix(int _n, int _m) : n(_n), m(_m), a(_n, vector<T>(_m, T(0))) {}
    Matrix(vector<vector<T>> A) : n(A.size()), m(A[0].size()), a(A) {}

    vector<T> &operator[](int i)
    {
        return a[i];
    }

    const vector<T> &operator[](int i) const
    {
        return a[i];
    }

    Matrix &operator+=(const Matrix &other)
    {
        assert(n == other.n && m == other.m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                (*this)[i][j] += other[i][j];
        return (*this);
    }

    Matrix &operator-=(const Matrix &other)
    {
        assert(n == other.n && m == other.m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                (*this)[i][j] -= other[i][j];
        return (*this);
    }

    Matrix &operator*=(const Matrix &other)
    {
        assert(m == other.n);
        int t = m;
        m = other.m;
        vector<vector<T>> res(n, vector<T>(m, 0));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                for (int k = 0; k < t; k++)
                    res[i][j] = (res[i][j] + (*this)[i][k] * other[k][j]);
        a.swap(res);
        return (*this);
    }

    Matrix &operator^=(int p)
    {
        assert(p >= 0);
        assert(n == m);
        Matrix res(n);
        res.identity();
        Matrix base(*this);
        while (p)
        {
            if (p & 1)
                res *= base;
            base *= base;
            p >>= 1;
        }
        (*this) = res;
        return (*this);
    }

    Matrix operator+(const Matrix &other) const
    {
        return Matrix(*this) += other;
    }
    Matrix operator-(const Matrix &other) const
    {
        return Matrix(*this) -= other;
    }
    Matrix operator*(const Matrix &other) const
    {
        return Matrix(*this) *= other;
    }
    Matrix operator^(const int p) const
    {
        return Matrix(*this) ^= p;
    }

    void identity()
    {
        assert(n == m);
        for (int i = 0; i < n; i++)
            a[i][i] = T(1);
    }
    void print()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
                cout << a[i][j] << " ";
            cout << "\n";
        }
    }
};