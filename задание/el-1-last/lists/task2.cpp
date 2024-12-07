#include <cstddef>
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>

using graph_t = std::unordered_map<std::string, std::vector<std::string>>;
using used_t = std::unordered_map<std::string, bool> ;

void dfs(used_t &used, std::string &current, graph_t &g, std::string &parent) {
  if (used[current]) {
    return;
  }

  used[current] = true;
  if (current.find(".src") != std::string::npos) {
    std::ifstream file(current);
    
    std::string line;
    while (file >> line) {
      dfs(used, line, g, current); 
    }
  } else {
    g[parent].push_back(current);
  }
}

int main() {
  graph_t out;
  used_t used;

  std::string list = "all.src", start = ".";
  dfs(used, list, out, start);
   
  for (auto &p: out) {
    std::cout << p.first << " -> {"; 
    for (std::size_t i = 0; i < p.second.size(); ++i) {
      std::cout << p.second[i];
    
      if (i!= p.second.size() - 1) {
        std::cout << ", ";
      }
    }
    std::cout << "}\n";
  } 
}

