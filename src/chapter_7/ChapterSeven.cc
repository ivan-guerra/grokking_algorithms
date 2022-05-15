#include <string>
#include <limits>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

using Neighbors = std::unordered_map<std::string, uint32_t>;
using Graph     = std::unordered_map<std::string, Neighbors>;
using Cost      = std::unordered_map<std::string, uint32_t>;
using Parent    = std::unordered_map<std::string, std::string>;

static const uint32_t kInfinity =
    std::numeric_limits<uint32_t>::max();

void InitNetwork(Graph& network)
{
    network["start"]      = {};
    network["start"]["a"] = 6;
    network["start"]["b"] = 2;

    network["a"]        = {};
    network["a"]["fin"] = 1;

    network["b"]        = {};
    network["b"]["a"]   = 3;
    network["b"]["fin"] = 5;

    network["fin"] = {};
}

void InitCosts(Cost& costs)
{
    costs        = {};
    costs["a"]   = 6;
    costs["b"]   = 2;
    costs["fin"] = kInfinity;
}

void InitParents(Parent& parent)
{
    parent["a"]   = "start";
    parent["b"]   = "start";
    parent["fin"] = "";
}

std::string
FindLowestCostNode(const Cost& costs,
                   const std::unordered_set<std::string>& processed)
{
    uint32_t    lowest_cost      = kInfinity;
    std::string lowest_cost_node = "";
    for (const auto& kv : costs) {
        uint32_t cost = kv.second;
        if ((cost < lowest_cost) &&
            (processed.find(kv.first) == processed.end())) {
            lowest_cost      = cost;
            lowest_cost_node = kv.first;
        }
    }
    return lowest_cost_node;
}

void
ShortestPath(const Graph& network, Cost& costs, Parent& parents)
{
    std::unordered_set<std::string> processed;
    std::string node = FindLowestCostNode(costs, processed);
    while (node != "") {
        uint32_t cost = costs[node];
        Neighbors neighbors = network.find(node)->second;
        for (const auto& neighbor : neighbors) {
            uint32_t new_cost = cost + neighbor.second;
            if (costs[neighbor.first] > new_cost) {
                costs[neighbor.first]   = new_cost;
                parents[neighbor.first] = node;
            }
        }
        processed.insert(node);
        node = FindLowestCostNode(costs, processed);
    }
}

int main(void)
{
    /* Initialize the network, cost, and parent tables. */
    Graph network;
    InitNetwork(network);

    Cost costs;
    InitCosts(costs);

    Parent parents;
    InitParents(parents);

    /* Run Dijkstra's shortest path algorithm. */
    ShortestPath(network, costs, parents);

    /* Print out the solution cost and path. */
    std::cout << "Shortest Path Cost is = "
              << costs["fin"] << std::endl;
    std::cout << "Shortest Path is: ";
    std::string node = "fin";
    while (parents.find(node) != parents.end()) {
        std::cout << node << " <- ";
        node = parents[node];
    }
    std::cout << node << std::endl;

    return 0;
}
