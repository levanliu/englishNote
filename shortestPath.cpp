#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <cmath>

struct Node {
    int value;
    std::vector<int> path;
};

std::vector<std::vector<int>> bfs(int start, int target) {
    std::queue<Node> queue;
    std::unordered_set<int> visited;
    std::vector<std::vector<int>> paths;
    
    queue.push({start, {start}});
    
    while (!queue.empty()) {
        Node current = queue.front();
        queue.pop();
        
        if (current.value == target) {
            paths.push_back(current.path);
        }
        
        visited.insert(current.value);
        
        int next_values[] = { current.value + 2, current.value - 2, current.value * 2, current.value / 2, current.value * current.value, static_cast<int>(std::pow(2, current.value)) };
        
        for (int i = 0; i < 6; i++) {
            int next_value = next_values[i];
            if (next_value >= 1 && next_value <= 666 && visited.find(next_value) == visited.end()) {
                std::vector<int> next_path = current.path;
                next_path.push_back(next_value);
                queue.push({next_value, next_path});
            }
        }
    }
    
    return paths;
}

std::vector<int> shortestPath(const std::vector<std::vector<int>>& paths) {
    std::vector<int> shortest;
    int min_length = INT_MAX;
    
    for (const auto& path : paths) {
        if (path.size() < min_length) {
            min_length = path.size();
            shortest = path;
        }
    }
    
    return shortest;
}

int main() {
    int start = 10;
    int target = 666;
    
    std::vector<std::vector<int>> allPaths = bfs(start, target);
    std::vector<int> shortest = shortestPath(allPaths);
    
    std::cout << "All paths from " << start << " to " << target << ":\n";
    for (const auto& path : allPaths) {
        for (int i = 0; i < path.size(); i++) {
            std::cout << path[i];
            if (i != path.size() - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;
    }
    
    std::cout << "Shortest path from " << start << " to " << target << ":\n";
    for (int i = 0; i < shortest.size(); i++) {
        std::cout << shortest[i];
        if (i != shortest.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
    
    return 0;
}
