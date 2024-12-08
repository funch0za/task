#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using graph_t = std::unordered_map<std::string, std::vector<std::string>>;
using visited_t = std::unordered_map<std::string, bool>;

void dfs_build_graph(visited_t &visited, std::string &current, graph_t &g,
         std::string &parent) {
 
  if (visited[current]) {
    return;
  }

  visited[current] = true;
  if (current.find(".src") != std::string::npos) {
    
    std::ifstream file("lists/" + current);

    std::string line;
    while (file >> line) {
      dfs_build_graph(visited, line, g, current);
    }
  }
}

int main() {
  graph_t graph;
  visited_t visited;

  std::string list = "all.src", start = ".";
  
  dfs_build_graph(visited, list, graph, start);
  for (auto &p : graph) {
    if (!p.second.empty()) {
      std::cout << "\"" << p.first << "\" -> {";
      for (std::size_t i = 0; i < p.second.size(); ++i) {
        std::cout << "\"" << p.second[i] << "\"";
  
        if (i != p.second.size() - 1) {
          std::cout << ", ";
        }
      }
      std::cout << "}\n";
    }
  }

}
