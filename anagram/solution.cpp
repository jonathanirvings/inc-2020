#include <bits/stdc++.h>

using namespace std;

struct NTT {
public:
  NTT(const int _mod) : mod(_mod) {
    proot = find_primitive_root();
    int totient = mod-1;
    max_len = 1;
    while ((totient & max_len) == 0)
      max_len <<= 1;
  }

  void fft(vector<int> & a, bool invert) {
    int n = (int) a.size();
    if (n & (n-1)) {
      int pw = 1;
      while (pw < n) pw <<= 1;
      n = pw;
      a.resize(n, 0);
    }
    assert(n <= max_len);

    for (int i=1, j=0; i<n; ++i) {
      int bit = n >> 1;
      for (; j>=bit; bit>>=1)
        j -= bit;
      j += bit;
      if (i < j)
        swap (a[i], a[j]);
    }

    int root = powmod(proot, (mod-1) / n);
    if (invert)
      root = inverse(root);

    for (int len = 2; len <= n; len <<= 1) {
      int wlen = root;
      for (int i = len; i < n; i <<= 1)
        wlen = int (wlen * 1ll * wlen % mod);
      for (int i = 0; i < n; i += len) {
        int w = 1;
        for (int j = 0; j < len/2; ++j) {
          int u = a[i+j], v = int (a[i+j+len/2] * 1ll * w % mod);
          a[i+j] = u+v < mod ? u+v : u+v-mod;
          a[i+j+len/2] = u-v >= 0 ? u-v : u-v+mod;
          w = int (w * 1ll * wlen % mod);
        }
      }
    }
    if (invert) {
      int nrev = inverse(n);
      for (int i = 0; i < n; ++i)
        a[i] = int (a[i] * 1ll * nrev % mod);
    }
  }

  vector<int> multiply(vector<int> a, vector<int> b) {
    int len = a.size() + b.size() - 1;
    int pw = 1;
    while (pw < len) pw <<= 1;
    len = pw;
    a.resize(len, 0);
    b.resize(len, 0);
    fft(a, false);
    fft(b, false);
    for (int i = 0; i < len; ++i)
      a[i] = 1LL * a[i] * b[i] % mod;
    fft(a, true);
    while (len > 0 && a[len-1] == 0)
      --len;
    a.resize(len);
    return a;
  }
  long long powmod(long long b, long long p) {
    long long r = 1;
    for (; p; p >>= 1, b = b * b % mod)
      if (p & 1)
        r = r * b % mod;
    return r;
  }

  long long inverse(int x) {
    return powmod(x, mod-2);
  }

private:
  const int mod;
  int proot;
  int max_len = 1;

  int find_primitive_root() {
    int totient = mod - 1;
    vector<int> checks;
    int tmp = totient;
    for (int p = 2; p * p <= tmp; ++p) {
      if (tmp % p) continue;
      checks.push_back(totient/p);
      while ((tmp % p) == 0) tmp /= p;
    }
    if (tmp > 1)
      checks.push_back(totient/tmp);
    for (int r = 2; ; ++r) {
      bool ok = 1;
      for (int f : checks) {
        if (powmod(r, f) == 1) {
          ok = 0;
          break;
        }
      }
      if (ok)
        return r;
    }
    assert(false);
  }
};

const int mod = 998244353;

NTT ntt(mod);

char dir[] = "NESW";
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
int cnt[4];

int n, m;
string p;
vector<vector<int>> polynoms;

vector<int> multiply_all(int l, int r) {
  if (l == r)
    return polynoms[l];
  int mid = (l + r) >> 1;
  return ntt.multiply(multiply_all(l, mid), multiply_all(mid+1, r));
}

int main() {
  auto startt = clock();
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  cin >> n >> m;
  cin >> p;
  assert((int)p.size() == n);
  vector<int> t(m+2, 0), x(m+2, 0), y(m+2, 0);
  for (int i = 1; i <= m; ++i)
    cin >> t[i] >> x[i] >> y[i];
  int posx = 0, posy = 0;
  for (char c : p) {
    for (int i = 0; i < 4; ++i)
      if (c == dir[i]) {
        posx += dx[i];
        posy += dy[i];
        ++cnt[i];
      }
  }
  t[m+1] = n;
  x[m+1] = posx;
  y[m+1] = posy;

  vector<int> fact(n+1), inv(n+1);
  fact[0] = inv[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fact[i] = 1LL * i * fact[i-1] % mod;
    inv[i] = ntt.inverse(fact[i]);
  }
  int sum = 0;
  for (int i = 0; i <= m; ++i) {
    if (t[i] == t[i+1]) {
      if (x[i] != x[i+1] || y[i] != y[i+1]) {
        puts("0");
        return 0;
      }
      continue;
    }
    int move_x = x[i+1]-x[i], move_y = y[i+1]-y[i], duration = t[i+1]-t[i];
    int tot = abs(move_x) + abs(move_y);
    if (tot > duration || (tot & 1) != (duration & 1)) {
      puts("0");
      return 0;
    }
    if (move_x > 0)
      cnt[1] -= move_x;
    else
      cnt[3] += move_x;
    if (move_y > 0)
      cnt[0] -= move_y;
    else
      cnt[2] += move_y;
    int rest = (duration - tot) / 2;
    vector<int> polynom(rest + 1);
    for (int hor = 0; hor <= rest; ++hor) {
      int ver = rest - hor;
      long long cur = 1LL * fact[duration] * inv[hor] % mod;
      cur = cur * inv[hor + abs(move_x)] % mod;
      cur = cur * inv[ver] % mod;
      cur = cur * inv[ver + abs(move_y)] % mod;
      polynom[hor] = cur;
    }
    sum += rest;
    polynoms.push_back(polynom);
  }
  for (int i = 0; i < 4; ++i) {
    if (cnt[i] < 0) {
      puts("0");
      return 0;
    }
  }
  if (cnt[0] != cnt[2] || cnt[1] != cnt[3]) {
    puts("0");
    return 0;
  }
  vector<int> result = multiply_all(0, (int)polynoms.size()-1);
  cout << (cnt[1] < (int)result.size() ? result[cnt[1]] : 0) << endl;
  cerr << "execution time : " << (double)(clock() - startt) / CLOCKS_PER_SEC << " s" << endl;
  return 0;
}
