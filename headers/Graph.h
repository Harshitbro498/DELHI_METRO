#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <utility>
#include <functional>

using namespace std;
using pairstr = pair<string,string>;

struct node {
    int val = 0;
    vector<string> route;
};

// Original parsing / graph functions
void load_lines(vector<string>& lines);
void hashes(map<pairstr,int>& result, vector<string>& station_name);
string line_name(const vector<string>& lines, const map<pairstr,int>& m, const string& name);
void intersecting_stations_funtion(map<pairstr,set<string>>& intersecting_stations,
                                   const vector<string>& lines,
                                   const map<pairstr,int>& m,
                                   const vector<string>& station_name);
void line_hash_function(map<int,string>& line_num, const vector<string>& lines);
void graph_function(vector<vector<int>>& graph);
int line_num_function(const map<int,string>& line_num, const string& line);
vector<vector<int>> path_function(vector<vector<int>>& graph, int& src, int& des);
vector<node> path_with_station(const vector<vector<int>>& dfs_paths,
                               const map<pairstr,set<string>>& intersecting_stations,
                               const map<pairstr,int>& m,
                               const map<int,string>& line_num,
                               const string& start,
                               const string& end);
void sorting(vector<node>& routes);

// Wrappers / helpers used by worker.cpp
vector<vector<int>> iddfs_wrapper(const vector<vector<int>>& graph, int src, int dest, int maxDepth);
void build_station_graph_wrapper(const map<pairstr,int>& m,
                                 const vector<string>& lines,
                                 unordered_map<string,int>& station_to_id,
                                 vector<string>& id_to_station,
                                 vector<vector<pair<int,int>>>& station_adj);
int astar_wrapper(const vector<vector<pair<int,int>>>& adj,
                  int start, int goal,
                  function<int(int,int)> heuristic,
                  vector<int>& parent_out);

#endif // GRAPH_H
