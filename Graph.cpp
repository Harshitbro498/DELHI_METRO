// graph.cpp
#include "headers/Graph.h"
#include <bits/stdc++.h>
using namespace std;

// ---------- Utilities & parsing ----------
static inline string trim(const string &s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

void load_lines(vector<string>& lines) {
    ifstream f("Resources/example.txt");
    if (!f.is_open()) { cerr << "Unable to open Resources/example.txt\n"; return; }
    string l;
    while (getline(f, l)) {
        string s;
        for (char c : l) { if (c == '/') break; s.push_back(c); }
        s = trim(s);
        if (!s.empty()) lines.push_back(s);
    }
}

void hashes(map<pairstr,int>& result, vector<string>& station_name) {
    ifstream f("Resources/stations.txt");
    if (!f.is_open()) { cerr << "Unable to open Resources/stations.txt\n"; return; }
    string full;
    unordered_set<string> seen;
    while (getline(f, full)) {
        string line = trim(full);
        if (line.empty()) continue;
        string station, lineName;
        int idx = -1;

        // Try CSV
        if (line.find(',') != string::npos) {
            vector<string> parts; string tmp; stringstream ss(line);
            while (getline(ss, tmp, ',')) parts.push_back(trim(tmp));
            if (parts.size() >= 3) {
                station = parts[0]; lineName = parts[1];
                try { idx = stoi(parts[2]); } catch(...) { idx = -1; }
            }
        }

        // Try "\n" tokens (literal) e.g. "A \n line \n 1"
        if (idx == -1 && line.find("\\n") != string::npos) {
            vector<string> parts; string tmp; stringstream ss(line);
            while (getline(ss, tmp, '\\')) {
                if (!tmp.empty()) {
                    if (tmp[0] == 'n') tmp = tmp.substr(1);
                    parts.push_back(trim(tmp));
                }
            }
            if (parts.size() >= 3) {
                station = parts[0]; lineName = parts[1];
                try { idx = stoi(parts[2]); } catch(...) { idx = -1; }
            }
        }

        // Fallback whitespace split
        if (idx == -1 && station.empty()) {
            vector<string> toks; string tmp; stringstream ss(line);
            while (ss >> tmp) toks.push_back(tmp);
            if (toks.size() >= 3) {
                try { idx = stoi(toks.back()); } catch(...) { idx = -1; }
                lineName = toks[toks.size()-2];
                string sacc;
                for (size_t i = 0; i + 2 < toks.size(); ++i) {
                    if (i) sacc += " ";
                    sacc += toks[i];
                }
                station = trim(sacc);
                if (station.empty()) station = toks.front();
            }
        }

        if (idx == -1) {
            int a = 0, b = 0;
            if (!line.empty() && isdigit(line.back())) a = line.back() - '0';
            if (line.size() >= 2 && isdigit(line[line.size()-2])) b = line[line.size()-2] - '0';
            idx = b * 10 + a;
        }

        station = trim(station); lineName = trim(lineName);
        if (station.empty() || lineName.empty()) continue;
        result[{station, lineName}] = idx;
        if (seen.insert(station).second) station_name.push_back(station);
    }
}

string line_name(const vector<string>& lines, const map<pairstr,int>& m, const string& name) {
    for (const auto& ln : lines) {
        if (m.find({name, ln}) != m.end()) return ln;
    }
    return string("invalid station name");
}

void intersecting_stations_funtion(map<pairstr,set<string>>& intersecting_stations,
                                   const vector<string>& lines,
                                   const map<pairstr,int>& m,
                                   const vector<string>& station_name) {
    int L = (int)lines.size();
    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < L; ++j) {
            if (i == j) continue;
            pairstr key{lines[i], lines[j]};
            pairstr keyr{lines[j], lines[i]};
            if (intersecting_stations.find(keyr) != intersecting_stations.end()) {
                intersecting_stations[key] = intersecting_stations[keyr];
                continue;
            }
            for (const auto &st : station_name) {
                if (m.find({st, lines[i]}) != m.end() && m.find({st, lines[j]}) != m.end())
                    intersecting_stations[key].insert(st);
            }
        }
    }
}

void line_hash_function(map<int,string>& line_num, const vector<string>& lines) {
    for (int i = 0; i < (int)lines.size(); ++i) line_num[i] = lines[i];
}

void graph_function(vector<vector<int>>& graph) {
    ifstream f("Resources/matrix.txt");
    if (!f.is_open()) { cerr << "Unable to open Resources/matrix.txt\n"; return; }
    string l; int i = 0;
    while (getline(f, l) && i < (int)graph.size()) {
        for (int j = 0; j < (int)l.size() && j < (int)graph.size(); ++j) {
            if (l[j] == '/') break;
            if (l[j] == '1') graph[i].push_back(j);
        }
        ++i;
    }
}

int line_num_function(const map<int,string>& line_num, const string& line) {
    for (auto &p : line_num) if (p.second == line) return p.first;
    return -1;
}

// ---------- line-level helpers ----------
bool is_unvisited(int node, const vector<int>& path) {
    for (int x : path) if (x == node) return false;
    return true;
}

// vector<vector<int>> path_function(vector<vector<int>>& graph, int& src, int& des) {
//     vector<vector<int>> ans;
//     queue<vector<int>> q;
//     q.push({src});
//     const int MAX_DEPTH = 4;
//     while (!q.empty()) {
//         auto path = q.front(); q.pop();
//         int last = path.back();
//         if (last == des && (int)path.size() <= MAX_DEPTH) {
//             ans.push_back(path);
//             continue;
//         }
//         if ((int)path.size() >= MAX_DEPTH) continue;
//         for (int nxt : graph[last]) {
//             if (is_unvisited(nxt, path)) {
//                 auto np = path;
//                 np.push_back(nxt);
//                 q.push(np);
//             }
//         }
//     }
//     return ans;
// }

// IDDFS
void dfs_idlimit(int node, int dest, int depth, int maxDepth, vector<int>& path,
                 const vector<vector<int>>& graph, vector<vector<int>>& out) {
    if (depth > maxDepth) return;
    if (node == dest) out.push_back(path);
    if (depth == maxDepth) return;
    for (int nxt : graph[node]) {
        if (!is_unvisited(nxt, path)) continue;
        path.push_back(nxt);
        dfs_idlimit(nxt, dest, depth + 1, maxDepth, path, graph, out);
        path.pop_back();
    }
}
vector<vector<int>> iddfs_wrapper(const vector<vector<int>>& graph, int src, int dest, int maxDepth) {
    vector<vector<int>> res;
    for (int d = 0; d <= maxDepth; ++d) {
        vector<int> p{src};
        dfs_idlimit(src, dest, 0, d, p, graph, res);
    }
    return res;
}

// ---------- station-level graph builder ----------
void build_station_graph_wrapper(const map<pairstr,int>& m,
                                 const vector<string>& lines,
                                 unordered_map<string,int>& station_to_id,
                                 vector<string>& id_to_station,
                                 vector<vector<pair<int,int>>>& station_adj) {
    unordered_map<string, vector<pair<int,string>>> per_line;
    for (auto &kv : m) {
        const string &station = kv.first.first;
        const string &line = kv.first.second;
        int pos = kv.second;
        per_line[line].push_back({pos, station});
        if (!station_to_id.count(station)) {
            int id = (int)id_to_station.size();
            station_to_id[station] = id;
            id_to_station.push_back(station);
            station_adj.emplace_back();
        }
    }
    for (auto &kv : per_line) {
        auto &vec = kv.second;
        sort(vec.begin(), vec.end());
        for (int i = 1; i < (int)vec.size(); ++i) {
            int u = station_to_id[vec[i-1].second];
            int v = station_to_id[vec[i].second];
            station_adj[u].push_back({v, 1});
            station_adj[v].push_back({u, 1});
        }
    }
}

// ---------- A* ----------
int Astar(const vector<vector<pair<int,int>>>& adj,
          int start, int goal,
          function<int(int,int)> heuristic,
          vector<int>& parent_out) {
    int n = (int)adj.size();
    const int INF = numeric_limits<int>::max()/4;
    vector<int> g(n, INF);
    parent_out.assign(n, -1);
    using P = pair<int,int>;
    priority_queue<P, vector<P>, greater<P>> pq;
    g[start] = 0;
    pq.push({heuristic(start,goal), start});
    while (!pq.empty()) {
        auto f = pq.top().first;
        auto u=pq.top().second;
        pq.pop();
        if (u == goal) return g[goal];
        int gu = f - heuristic(u,goal);
        if (gu != g[u]) continue;
        for (auto &e : adj[u]) {
            int v = e.first, w = e.second;
            int ng = g[u] + w;
            if (ng < g[v]) {
                g[v] = ng;
                parent_out[v] = u;
                pq.push({ng + heuristic(v,goal), v});
            }
        }
    }
    return INF;
}

int astar_wrapper(const vector<vector<pair<int,int>>>& adj,
                  int start, int goal,
                  function<int(int,int)> heuristic,
                  vector<int>& parent_out) {
    return Astar(adj, start, goal, heuristic, parent_out);
}

// ---------- expand line paths to station routes ----------
vector<node> path_with_station(const vector<vector<int>>& dfs_paths,
                               const map<pairstr,set<string>>& intersecting_stations,
                               const map<pairstr,int>& m,
                               const map<int,string>& line_num,
                               const string& start,
                               const string& end) {
    vector<node> ans;
    for (auto seq : dfs_paths) {
        if (seq.size() <= 1) continue;
        pairstr key01{ line_num.at(seq[0]), line_num.at(seq[1]) };
        if (intersecting_stations.find(key01) == intersecting_stations.end()) continue;
        vector<node> curr;
        for (auto k : intersecting_stations.at(key01)) {
            node t; t.route.clear();
            t.route.push_back(start);
            string firstLine = line_num.at(seq[0]);
            if (start != k) t.route.push_back(k);
            t.val = abs(m.at({k, firstLine}) - m.at({start, firstLine}));
            curr.push_back(t);
        }
        for (int j = 1; j < (int)seq.size()-1; ++j) {
            pairstr keyj{ line_num.at(seq[j]), line_num.at(seq[j+1]) };
            if (intersecting_stations.find(keyj) == intersecting_stations.end()) { curr.clear(); break; }
            vector<node> newcurr;
            for (auto k : intersecting_stations.at(keyj)) {
                for (auto &prev : curr) {
                    node t = prev;
                    string prevStation = t.route.back();
                    string currLine = line_num.at(seq[j]);
                    t.val += abs(m.at({k, currLine}) - m.at({prevStation, currLine}));
                    if (prevStation != k) t.route.push_back(k);
                    newcurr.push_back(t);
                }
            }
            curr.swap(newcurr);
            if (curr.empty()) break;
        }
        if (!curr.empty()) {
            string lastLine = line_num.at(seq.back());
            for (auto t : curr) {
                string prev = t.route.back();
                t.val += abs(m.at({end, lastLine}) - m.at({prev, lastLine}));
                if (prev != end) t.route.push_back(end);
                ans.push_back(t);
            }
        }
    }
    return ans;
}

bool compare_node(const node &a, const node &b) {
    if (a.val == b.val) return a.route.size() < b.route.size();
    return a.val < b.val;
}
void sorting(vector<node>& routes) { sort(routes.begin(), routes.end(), compare_node); }
