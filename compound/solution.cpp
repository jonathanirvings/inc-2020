#include <stdio.h>
#include <iostream>
#include <sstream>
#include <iomanip>
 
#include <algorithm>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <utility>
 
#include <math.h>
#include <complex>
 
#include <assert.h>
#include <time.h>
#include <chrono>
#include <random>
 
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <stack>
#include <list>
#include <bitset>
 
#define F first
#define S second
#define pb push_back
#define pf push_front
#define pob pop_back
#define pof pop_front
#define endl '\n'
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

 
void desperate_optimization(int precision){
  	ios_base::sync_with_stdio(false);
  	cin.tie(0);
  	cout.tie(0);
  	cout.setf(ios::fixed);
  	cout.setf(ios::showpoint);
  	cout.precision(precision);
}

const ll LIMIT = 1e12;
const int N = 1e3;
const int NN = N * (N + 1) / 2;

ll arr[N + 5];

map<ll, int> group, occurence;

vector<int> weight;


bitset<NN + 5> dp;

ll gcd(ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    desperate_optimization(10);
    int n, q;
    cin>>n>>q;

    for(int i = 1;i <= n;i++) cin>>arr[i];
    for(int i = 1;i <= n;i++) {
        for(int j = i + 1;j <= n;j++) {
            ll gc = gcd(arr[i], arr[j]);
            ll limit = LIMIT / gc;
            ll ni = arr[i] / gc, nj = arr[j] / gc;
            ll not_expressed = (ni - 1) * (nj - 1) / 2;
            not_expressed += (nj + ni - 1);
            group[limit - not_expressed]++;
        }
    }
    for(auto x: group) {
        occurence[x.S]++;
    }
    for(auto x: occurence) {
        ll v = x.F;
        int occ = x.S;
        int cur = 1;
        while(cur <= occ) {
            weight.pb(v * cur);
            occ -= cur;
            cur *= 2;
        }
        if(occ) {
            weight.pb(v * occ);
        }
    }
    dp[0] = 1;
    for(auto x: weight) {
        dp |= (dp << x);
    }
    
    while(q--) {
        int m;
        cin>>m;
        if(dp[m] == 1) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
}