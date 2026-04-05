template <typename T, size_t B>
struct Basis {
  int sz = 0, tot = 0;
  T base[B + 1];

  Basis() {
    for (int i = 0; i <= B; i++) base[i] = 0;
  }

  bool add(T x) {
    tot++;
    for (int i = B; i >= 0; i--) {
      if (!(x >> i & 1)) continue;
      if (!base[i]) {
        base[i] = x;
        for (int j = i + 1; j <= B; j++) {
          if (base[j] >> i & 1) base[j] ^= base[i];
        }
        for (int j = i - 1; j >= 0; j--) {
          if (base[i] >> j & 1) base[i] ^= base[j];
        }
        sz++;
        return true;
      }
      x ^= base[i];
    }
    return false;
  }
  T reduce(T x) {
    for (int i = B; i >= 0; i--) {
      if (x >> i & 1) x ^= base[i];
    }
    return x;
  }
  bool check(T x) {
    return reduce(x) == 0;
  }
  T max() {
    T res = 0;
    for (int i = B; i >= 0; i--) {
      if ((res ^ base[i]) > res) res ^= base[i];
    }
    return res;
  }
  T min() {
    for (int i = 0; i <= B; i++) {
      if (base[i]) return base[i];
    }
    return 0;
  }
  T kth_smallest(unsigned __int128 k) {
    if (k >= (1ll << sz)) return -1;
    int res = 0;
    int cur = 0;
    for (int i = 0; i <= B; i++) {
      if (base[i]) {
        if (k >> cur & 1) res ^= base[i];
        cur++;
      }
    }
    return res;
  }
  unsigned __int128 count() { return (unsigned __int128)1 << sz; }
  T max(T k) {
    T res = k;
    for (int i = B; i >= 0; i--) {
      if ((res ^ base[i]) > res) res ^= base[i];
    }
    return res;
  }
  unsigned __int128 count_ways(T k) {
    if (!check(k)) return 0;
    return (unsigned __int128)1 << (tot - sz);
  }
  int count_ways(T k, int mod) {
    if (!check(k)) return 0;
    int exp = tot - sz;
    int res = 1, p = 2;
    while (exp) {
      if (exp & 1) res = res * p % mod;
      p = p * p % mod;
      exp >>= 1;
    }
    return res;
  }
};


// not completed
template <size_t N> 
struct Basis {
  bitset<N> base[N];
  int sz = 0;
  int tot = 0;

  bool add(bitset<N> x) {
    tot++;
    for (int i = N - 1; N >= 0; i--) {
      if (!x.test(i)) continue;
      if (!base[i].any()) {
        base[i] = x;
        for (int j = i + 1; j < N; j++) {
          if (base[j].test(i)) base[j] ^= base[i];
        }
        for (int j = i - 1; j >= 0; j--) {
          if (base[i].test(j) && base[j].any(i)) base[i] ^= base[j]; 
        }
        sz++;
        return true;
      }
      x ^= base[i];
    }
    return false;
  }
  bitset<N> reduce(bitset<N> x) {
    for (int i = N - 1; i >= 0; i--) {
      if (x.test(i)) x ^= base[i];
    }
    return x;
  }
  bool check(bitset<N> x) {
    return reduce(x).none();
  }
};

