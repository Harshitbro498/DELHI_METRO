// worker.cpp
#include "headers/Graph.h"
#include <bits/stdc++.h>
using namespace std;

static inline string to_lower(const string &s) {
    string r = s;
    transform(r.begin(), r.end(), r.begin(), [](unsigned char c){ return tolower(c); });
    return r;
}

// Paginated station picker: shows pages of stations, supports:
//  - entering a number to select that station
//  - entering text to filter stations (case-insensitive substring)
//  - 'n' or 'p' for next/prev page
//  - 'q' to cancel (returns empty string)
string pick_station_interactive(const vector<string>& id_to_station) {
    if (id_to_station.empty()) return string();

    const int PAGE_SIZE = 20;
    vector<int> indices(id_to_station.size());
    iota(indices.begin(), indices.end(), 0);

    vector<int> current_list = indices; // indices into id_to_station
    int page = 0;

    auto show_page = [&](int page_num) {
        int total_pages = (int)ceil((double)current_list.size() / PAGE_SIZE);
        if (total_pages == 0) total_pages = 1;
        if (page_num < 0) page_num = 0;
        if (page_num >= total_pages) page_num = total_pages - 1;
        int start = page_num * PAGE_SIZE;
        int end = min(start + PAGE_SIZE, (int)current_list.size());
        cout << "\nStations (page " << page_num + 1 << " / " << total_pages << "):\n";
        for (int i = start; i < end; ++i) {
            int idx = current_list[i];
            // Display 1-based index for user-friendly choice
            cout << setw(4) << (i + 1) << ") " << id_to_station[idx] << "\n";
        }
        if (current_list.empty()) cout << "  (no stations match your filter)\n";
        cout << "\nCommands: Enter number to pick | type substring to filter | 'n' next | 'p' prev | 'a' show all | 'q' cancel\n";
        cout << "Your choice: " << flush;
    };

    auto apply_filter = [&](const string &filter) {
        current_list.clear();
        string f = to_lower(filter);
        for (int i = 0; i < (int)id_to_station.size(); ++i) {
            if (to_lower(id_to_station[i]).find(f) != string::npos) current_list.push_back(i);
        }
        page = 0;
    };

    // Initial show first page
    show_page(page);

    string line;
    while (true) {
        if (!getline(cin, line)) return string(); // EOF -> abort
        string input = line;
        // trim
        auto a = input.find_first_not_of(" \t\r\n");
        if (a == string::npos) input.clear();
        else {
            auto b = input.find_last_not_of(" \t\r\n");
            input = input.substr(a, b - a + 1);
        }
        if (input.empty()) {
            // re-show current page
            show_page(page);
            continue;
        }
        // single-char commands
        if (input == "n" || input == "N") {
            int total_pages = max(1, (int)ceil((double)current_list.size() / PAGE_SIZE));
            if (page + 1 < total_pages) ++page;
            show_page(page);
            continue;
        }
        if (input == "p" || input == "P") {
            if (page > 0) --page;
            show_page(page);
            continue;
        }
        if (input == "a" || input == "A") {
            // show all: reset filter
            current_list = indices;
            page = 0;
            show_page(page);
            continue;
        }
        if (input == "q" || input == "Q") {
            return string();
        }

        // If numeric: pick that index (1-based number is shown)
        bool is_number = true;
        for (char c : input) if (!isdigit((unsigned char)c)) { is_number = false; break; }
        if (is_number) {
            long long num = stoll(input);
            if (num >= 1 && num <= (long long)current_list.size()) {
                int chosen_global = current_list[(int)num - 1];
                return id_to_station[chosen_global];
            }
            // number outside current list — but maybe user used page-local numbering (i.e., they saw numbers starting at 1 per page)
            // So support page-local selection (1..PAGE_SIZE)
            int start = page * PAGE_SIZE;
            int end = min(start + PAGE_SIZE, (int)current_list.size());
            if (num >= 1 && num <= (end - start)) {
                int chosen_global = current_list[start + (int)num - 1];
                return id_to_station[chosen_global];
            }
            cout << "Number out of range. Try again: " << flush;
            continue;
        }

        // Otherwise treat input as filter substring
        apply_filter(input);
        show_page(page);
    }
}

// Reconstruct path (station IDs) into station names
vector<string> reconstruct_from_parent(const vector<int>& parent, int start, int goal, const vector<string>& id_to_station) {
    vector<string> route;
    if (goal < 0 || goal >= (int)parent.size()) return route;
    int cur = goal;
    while (cur != -1) {
        route.push_back(id_to_station[cur]);
        if (cur == start) break;
        cur = parent[cur];
    }
    reverse(route.begin(), route.end());
    return route;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(&cout); // ensure prompts flush

    // Load graph resources
    map<pairstr,int> m;
    vector<string> station_names;
    vector<string> lines;
    map<pairstr,set<string>> intersections;
    map<int,string> line_num;

    load_lines(lines);
    if (lines.empty()) {
        cerr << "No lines loaded. Check Resources/example.txt\n";
        return 1;
    }

    vector<vector<int>> line_graph(lines.size());
    hashes(m, station_names);
    line_hash_function(line_num, lines);
    intersecting_stations_funtion(intersections, lines, m, station_names);
    graph_function(line_graph);

    // Build station-level graph & name lists
    unordered_map<string,int> station_to_id;
    vector<string> id_to_station;
    vector<vector<pair<int,int>>> station_adj;
    build_station_graph_wrapper(m, lines, station_to_id, id_to_station, station_adj);

    if (id_to_station.empty()) {
        cerr << "No stations found. Check Resources/stations.txt\n";
        return 1;
    }

    cout << "Welcome to Delhi Metro Assistant (station-picker enabled)\n";

    // Let user pick source and destination using the interactive picker
    cout << "\nSelect SOURCE station (you can type part of the name to filter):\n";
    string src = pick_station_interactive(id_to_station);
    if (src.empty()) { cout << "Source selection cancelled. Exiting.\n"; return 0; }
    cout << "You chose SOURCE: " << src << "\n";

    cout << "\nSelect DESTINATION station (you can type part of the name to filter):\n";
    string dest = pick_station_interactive(id_to_station);
    if (dest.empty()) { cout << "Destination selection cancelled. Exiting.\n"; return 0; }
    cout << "You chose DEST: " << dest << "\n\n";

    // Pick algorithm
    cout << "Choose algorithm: 1) A* (station-level shortest stops)  2) IDDFS (line-level transfer options)\n";
    cout << "Enter choice (1/2): " << flush;
    string algs; getline(cin, algs);
    int alg = 1;
    try { alg = stoi(algs); } catch(...) { alg = 1; }

    if (alg == 1) {
        // A* (here heuristic=0 => Dijkstra on unweighted station graph)
        if (!station_to_id.count(src) || !station_to_id.count(dest)) {
            cout << "Station names don't map to unified IDs; cannot run A*. Try IDDFS option.\n";
        } else {
            int s = station_to_id[src], t = station_to_id[dest];
            auto heur = [](int a,int b){ return 0; };
            vector<int> parent;
            int dist = astar_wrapper(station_adj, s, t, heur, parent);
            if (dist >= numeric_limits<int>::max()/4) {
                cout << "No route found between " << src << " and " << dest << "\n";
            } else {
                vector<string> route = reconstruct_from_parent(parent, s, t, id_to_station);
                cout << "\nShortest route (" << dist << " stops):\n";
                for (size_t i = 0; i < route.size(); ++i) {
                    if (i) cout << " --> ";
                    cout << route[i];
                }
                cout << "\n";
            }
        }
        return 0;
    }

    // IDDFS path on line-level then expand to station routes
    string src_line = line_name(lines, m, src);
    string dst_line = line_name(lines, m, dest);
    int sline = line_num_function(line_num, src_line);
    int dline = line_num_function(line_num, dst_line);
    if (sline == -1 || dline == -1) {
        cout << "Could not determine lines for the selected stations. Try picking different stations.\n";
        return 0;
    }

    int maxDepth = 4;
    auto line_paths = iddfs_wrapper(line_graph, sline, dline, maxDepth);
    if (line_paths.empty()) {
        cout << "No line-level paths found between lines (within depth " << maxDepth << ").\n";
        return 0;
    }

    auto routes = path_with_station(line_paths, intersections, m, line_num, src, dest);
    if (routes.empty()) {
        cout << "No station routes derived from the line sequences found.\n";
        return 0;
    }

    sorting(routes);
    cout << "\nTop route options:\n";
    int limit = min(3, (int)routes.size());
    for (int i = 0; i < limit; ++i) {
        auto &r = routes[i];
        cout << (i==0 ? "Best: " : to_string(i+1)+": ");
        for (size_t k = 0; k < r.route.size(); ++k) {
            if (k) cout << " --> ";
            cout << r.route[k];
        }
        cout << "   [stops: " << r.val << "]\n";
    }

    cout << "\nThank you. Safe travels!\n";
    return 0;
}
