// Daniil Zimin
// d.zimin@innopolis.university
// tg: daniilzimin4

#include <bits/stdc++.h>

#include <utility>

using namespace std;

typedef long long ll;
typedef long double ld;

mt19937 rnd(time(0));

#define ioss ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define file freopen("sum.in", "r", stdin); freopen("sum.out", "w", stdout);
#define pb push_back
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()

template<class T>
ll upmax(T &a, T b) { return (b > a) ? a = b, 1 : 0; }

template<class T>
ll upmin(T &a, T b) { return (b < a) ? a = b, 1 : 0; }

const ll inf = 1e18 + 7;

template<class K, class V>
struct MyHashMap {
    int n = 2;
    int maxLoadFactor = 2;
    int now = 0;

    struct Bucket {
        K key;
        V value;

        Bucket(K k, V v) : key(std::move(k)), value(v) {};

        int hash(int mod) {
            int local = 0;
            if (typeid(key) == typeid(string)) {
                int prime = 137;
                for (auto i: key) {
                    local = (local * prime) + i;
                    local %= mod;
                }
            }
            return local;
        }

        bool operator==(const Bucket &o) {
            return (key == o.key);
        }

    };

    vector<vector<Bucket>> list = vector<vector<Bucket>>(n, vector<Bucket>());

private:
    void reset() {
        n *= 2;
        now = 0;
        vector<vector<Bucket>> lastList = list;
        list.clear();
        list.resize(n * 2, vector<Bucket>());

        for (int i = 0; i < lastList.size(); i += 1) {
            for (const auto &j: lastList[i]) {
                add_(j);
            }
        }
    }

    void add_(Bucket el) {
        int hash = el.hash(n);
        for (int i = 0; i < list[hash].size(); i += 1) {
            if (el == list[hash][i]) {
                list[hash][i].value += el.value;
                return;
            }
        }
        list[hash].pb(el);
        now += 1;
        if (now > maxLoadFactor * n) {
            reset();
        }
    }

public:
    void addKeyAndValue(K key, V value) {
        add_(Bucket(key, value));
    }


    void addOnlyKey(K key) {
        add_(Bucket(key, 1));
    }


    vector<pair<V, K>> convertToArr() {
        vector<pair<V, K>> arr;
        for (int i = 0; i < n; i += 1) {
            for (const auto &el: list[i]) {
                arr.push_back({el.value, el.key});
            }
        }
        return arr;
    }

    bool contains(K key) {
        Bucket bucket(key, 1);
        int hash = bucket.hash(n);
        for (const auto &i: list[hash]) {
            if (i.key == bucket.key) {
                return true;
            }
        }
        return false;
    }

    void removeFull(K key) {
        Bucket bucket(key, 1);
        int hash = bucket.hash(n);
        for (int i = 0; i < list[hash]; i += 1) {
            if (bucket.key == list[hash][i].key) {
                list[hash].erase(list[hash].begin() + i);
                return;
            }
        }
    }


};

void n2sort(vector<pair<int, string>> &a) {
    for (int i = 0; i < a.size(); i += 1) {
        for (int j = 0; j < a.size() - 1; j += 1) {
            if (a[j].first < a[j + 1].first || (a[j].first == a[j + 1].first && a[j].second > a[j + 1].second)) {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

void solve() {
    MyHashMap<string, int> MyMap;
    int n;
    cin >> n;
    for (int i = 0; i < n; i += 1) {
        string x;
        cin >> x;
        MyMap.addOnlyKey(x);
    }
    vector<string> ans;
    int m;
    cin >> m;
    MyHashMap<string, int> MyMap2;
    for (int i = 0; i < m; i += 1) {
        string x;
        cin >> x;
        if (!MyMap.contains(x) && !MyMap2.contains(x)) {
            ans.pb(x);
            MyMap2.addOnlyKey(x);
        }
    }
    cout << ans.size() << '\n';
    for (auto i: ans) {
        cout << i << '\n';
    }
}


signed main() {
    ioss
    // file
    // (a += b) -> return value
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    // printf("Time taken: %.10fs\n", (double)(clock() - CLOCK_START)/CLOCKS_PER_SEC);
    return 0;
}