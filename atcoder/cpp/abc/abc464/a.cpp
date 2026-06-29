#ifdef INCLUDE_MAIN

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s; cin >> s;
    int n, cnt = 0;
    n = s.length();
    for (int i = 0; i < n; i++) {
        if (s[i] == 'E') cnt++;
    }
    if (n - cnt < cnt) cout << "East\n";
    else cout << "West\n";
}


#else

#define INCLUDE_MAIN

#include <algorithm>
#include <bit>
#include <bitset>
#include <cctype>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <numbers>
#include <numeric>
#include <queue>
#include <random>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>


using namespace std;


using ll = long long;
using ld = long double;
// using numbers::pi;


constexpr ld EPS = 1e-14;
constexpr ll INF = 5e18, MINF = -5e18;
constexpr ll BIGMOD = 998244353;
const ld PI = acos(-1.0L);

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }


#if defined(__SIZEOF_INT128__)
// __int128_t is supported (GCC/Clang)
std::ostream &operator<<(std::ostream &dest, __int128_t value) {
  std::ostream::sentry s(dest);
  if (s) {
    __uint128_t tmp = value < 0 ? -value : value;
    char buffer[128];
    char *d = std::end(buffer);
    do {
      --d;
      *d = "0123456789"[tmp % 10];
      tmp /= 10;
    } while (tmp != 0);
    if (value < 0) {
      --d;
      *d = '-';
    }
    int len = std::end(buffer) - d;
    if (dest.rdbuf()->sputn(d, len) != len) {
      dest.setstate(std::ios_base::badbit);
    }
  }
  return dest;
}

__int128 parse(string &s) {
  __int128 ret = 0;
  for (int i = 0; i < s.length(); i++)
    if ('0' <= s[i] && s[i] <= '9')
      ret = 10 * ret + s[i] - '0';
  return ret;
}
#endif



vector<string> DicOrder (string s) {
    vector<string> x;
    do {
        x.push_back(string(s.begin(), s.end()));
    }  while (next_permutation(s.begin(), s.end()));
    return x;
}

vector<vector<ll>> CalcuNext(const string &s) {
    ll n = s.length();
    vector<vector<ll>> next(n + 1, vector<ll>(26, n));
    for (ll i = n - 1; i >= 0; i--) {
        for (ll j = 0; j < 26; j++) {
            next[i][j] = next[i + 1][j];
        }
        next[i][s[i] - 'a'] = i;
    }
    return next;
}


//-----------------------------------Search-------------------------------------
ll MeguruLeft(const vector<ll>& n, ll key) {
    ll ng = -1, ok = n.size();
    while (ok - ng > 1) {
        ll mid = (ok + ng) / 2;
        if (n[mid] <= key) ng = mid;
        else ok = mid;
    }
    return ng + 1;
}
ll MeguruRight(const vector<ll>& n, ll key) {
    ll ng = -1, ok = n.size();
    while (ok - ng > 1) {
        ll mid = (ok + ng) / 2;
        if (n[mid] < key) ng = mid;
        else ok = mid;
    }
    return ok;
}


//-----------------------------------Grid-------------------------------------
const vector<int> dx4 = {1, 0, -1, 0};
const vector<int> dy4 = {0, 1, 0, -1};
const vector<int> dx8 = {1, 1, 0, -1, -1, -1, 0, 1};
const vector<int> dy8 = {0, 1, 1, 1, 0, -1, -1, -1};

bool is_inside(int x, int y, int height, int width) {
    return (0 <= x && x < height && 0 <= y && y < width);
}

//compress_coordinates
vector<ll> Comp_Coor(vector<ll> coords) {
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());
    return coords;
}

vector<string> Turn_Ri_90(const vector<string>& s) {
    ll h = s.size(), w = s[0].size();
    vector<string> res(w, string(h, ' '));
    for (int i = 0; i < h; i++) 
        for (int j = 0; j < w; j++)
            res[j][h - 1 - i] = s[i][j];
    return res;
}
vector<string> Turn_Le_90(const vector<string>& s) {
    ll h = s.size(), w = s[0].size();
    vector<string> res(w, string(h, ' '));
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            res[w - 1 - j][i] = s[i][j];
    return res;
}


//-----------------------------------Graph-------------------------------------
struct UnionFind {
    vector<int> parent, rank, size;

    UnionFind(int n) : parent(n, -1), rank(n, 0), size(n, 1) { }

    int root(int x) {
        if (parent[x] == -1) return x;
        return parent[x] = root(parent[x]);
    }

    bool is_same(int x, int y) {
        return root(x) == root(y);
    }

    bool unite(int x, int y) {
        int rx = root(x), ry = root(y);
        if (rx == ry) return false;
        if (rank[rx] < rank[ry]) swap(rx, ry);
        parent[ry] = rx;
        if (rank[rx] == rank[ry]) rank[rx]++;
        size[rx] += size[ry];
        return true;
    }

    int get_siz(int x) {
        return size[root(x)];
    }
};


struct SCC {
    ll V;
    vector<vector<ll>> graph, rgraph;
    vector<bool> visited;
    vector<ll> finish_order, component_id;
    vector<vector<ll>> scc_groups;

    SCC(ll n) : V(n), graph(n), rgraph(n), visited(n, false), component_id(n, -1) { }

    void add(ll from, ll to) {
        graph[from].push_back(to);
        rgraph[to].push_back(from);
    }

    void dfs(ll v) {
        visited[v] = true;
        for (ll to : graph[v]) if (!visited[to]) dfs(to);
        finish_order.push_back(v);
    }

    void reverse_dfs(ll v, ll k) {
        visited[v] = true;
        component_id[v] = k;
        for (ll to : rgraph[v]) if (!visited[to]) reverse_dfs(to, k);
    }

    vector<vector<ll>> build_scc() {
        for (ll v = 0; v < V; ++v) if (!visited[v]) dfs(v);

        fill(visited.begin(), visited.end(), false);
        reverse(finish_order.begin(), finish_order.end());

        ll num_scc = 0;
        for (ll v : finish_order) if (!visited[v]) reverse_dfs(v, num_scc++);

        vector<vector<ll>> result(num_scc);
        for (ll v = 0; v < V; ++v) result[component_id[v]].push_back(v);
        scc_groups = result;
        return result;
    }

    ll count() {
        auto comps = scc_groups.empty() ? build_scc() : scc_groups;
        ll total = 0;
        for (const auto &group : comps) {
            ll k = group.size();
            total += k * (k - 1) / 2;
        }
        return total;
    }
};

template<class T>
struct dijkstra{
  public:
    vector<vector<pair<T,T>>>graph;
    vector<T>ans;
    priority_queue<pair<T,T>,vector<pair<T,T>>,greater<pair<T,T>>>pq;
    void do_dijkstra(T start){//頂点xからダイクストラを行う
        ans.assign(ans.size(), INF);
        pq.push({0,start});
        ans[start] = 0;
        while(true){
            if(pq.empty())break;
            T cost = pq.top().first;
            T vertex = pq.top().second;
            pq.pop();
            if (cost > ans[vertex]) continue; 
            for(T i = 0;i<graph[vertex].size();i++){
                T nextvertex = graph[vertex][i].first;
                T nextcost = graph[vertex][i].second + cost;
                if(ans[nextvertex] <= nextcost)continue;
                    ans[nextvertex] = nextcost;
                    pq.push({nextcost,nextvertex});
            }
        }
    }
    void make_indirectedgraph(T u,T v,T cost){//無向辺のグラフ作成
        graph[u].push_back({v,cost});
        graph[v].push_back({u,cost});
    }
    void make_directedgraph(T u,T v,T cost){//有向辺のグラフ作成
        graph[u].push_back({v,cost});
    }
    T output(T end){//答えを出す
        return ans[end];
    } 
    void reset(T N){//リセット
        graph.assign(N, {});
        ans.assign(N, INF);
    }
};

 
void EulerTour(ll v, ll p, vector<vector<ll>>& graph, vector<ll>& answer) {
    answer.push_back(v);
    for (auto& to : graph[v]) {
        if (to == p) continue;
        EulerTour(to, v, graph, answer);
        answer.push_back(v);
    }
}

vector<ll> TopologicalSort(ll node_count, vector<vector<ll>>& graph) {
    vector<ll> indegree(graph.size(), 0);
    for (const auto& edges : graph)
        for (ll to : edges) indegree[to]++;

    priority_queue<ll, vector<ll>, greater<ll>> zero_indegree; //通常 queue  辞書順最小 priority_queue (greater) 辞書順最大 priority_queue
    for (ll v = 0; v < node_count; v++) if (indegree[v] == 0) zero_indegree.push(v);

    vector<ll> order;
    while (!zero_indegree.empty()) {
        ll cur = zero_indegree.top(); //queue front  priority_queue top
        zero_indegree.pop();
        order.push_back(cur);
        for (ll to : graph[cur]) {
            indegree[to]--;
            if (indegree[to] == 0) zero_indegree.push(to);
        }
    }

    if (order.size() != node_count) return {};
    return order;
}


//-----------------------------------Math-------------------------------------
bool Is_Prime(ll n) {
    if (n < 2) return false;
	else if (n == 2) return true;
	else if (n % 2 == 0) return false;
	double sqrtNum = sqrt(n);
	for (int i = 3; i <= sqrtNum; i += 2) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}

vector<bool> Prime_Table(ll n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i * i <= n; ++i) {
        if (is_prime[i]) {
            for (ll j = i * i; j <= n; j += i) is_prime[j] = false;
        }
    }
    return is_prime;
}


vector<pair<ll, ll>> Prime_Factor(ll n) {
    vector<pair<ll, ll>> factors;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            ll count = 0;
            while (n % i == 0) {
                n /= i;
                count++;
            }
            factors.emplace_back(i, count);
        }
    }
    if (n > 1) factors.emplace_back(n, 1);
    return factors;
}

ll ModPower(ll base, ll exp, ll mod) {
    ll result = 1;
    if (mod != 0) base %= mod;
    while (exp > 0) {
        if (exp & 1) result = mod ? (result * base) % mod : result * base;
        base = mod ? (base * base) % mod : base * base;
        exp >>= 1;
    }
    return result;
}

ll Factorial (ll n, ll mod) {
    if (n < 0) return 0;
    ll result = 1;
    for (ll i = 2; i <= n; i++) {
        if (mod == 0) result *= i;
        else result = (result * i) % mod;
    }
    return result;
}

ll Combination (ll n, ll r, ll mod) {
    if (n < r || n < 0 || r < 0) return 0;
    ll numerator = 1, denominator = 1;
    for (ll i = 0; i < r; i++) {
        if (mod == 0) {
            numerator *= (n - i);
            denominator *= (i + 1);
        } else {
            numerator = (numerator * (n - i)) % mod;
            denominator = (denominator * (i + 1)) % mod;
        }
    }
    if (mod == 0) return numerator / denominator;
    else return (numerator * ModPower(denominator, mod - 2, mod)) % mod;
}

ll Permutation (ll n, ll r, ll mod) {
    if (n < r || n < 0 || r < 0) return 0;
    ll result = 1;
    for (ll i = 0; i < r; i++) {
        if (mod == 0) result *= (n - i);
        else result = (result * (n - i)) % mod;
    }
    return result;
}

#include __FILE__
#endif
