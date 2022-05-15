#include <queue>
#include <string>
#include <forward_list>
#include <unordered_set>
#include <iostream>

#include "Graph.h"

bool IsMangoSeller(const std::string& name)
{
    if (name.empty())
        return false;

    return ('m' == name.back());
}

/*!
 * \brief Search for the nearest mango seller in \a network.
 *
 * GetMangoSeller() implements a BFS into the parameter network.
 *
 * \return The name of the nearest mango seller. If no mango seller
 *         is located, the empty string is returned.
 */
std::string GetMangoSeller(const Graph<std::string>& network,
                           const std::string& start)
{
    std::unordered_set<std::string> visited;
    std::queue<std::string>         buffer;

    buffer.push(start);
    while (!buffer.empty()) {
        std::string candidate = buffer.front();
        buffer.pop();

        if (visited.find(candidate) == visited.end()) {
            if (IsMangoSeller(candidate))
                return candidate;

            const auto& neighbors = network.GetNeighbors(candidate);
            for (const std::string& neighbor : neighbors)
                buffer.push(neighbor);

            visited.insert(candidate);
        }
    }

    /* No mango seller was found in the network. */
    return "";
}

int main(void)
{
    Graph<std::string> network(
        {
            {"Ivan", {"Claire", "Bob", "Alice"}},
            {"Claire", {"Thom", "Johnny"}},
            {"Alice", {"Peggy"}},
            {"Bob", {"Peggy", "Anuj"}}
        }
    );

    std::string mango_seller = GetMangoSeller(network, "Ivan");
    if (mango_seller.empty()) {
        std::cout << "There are no mango sellers in the network."
                  << std::endl;
    } else {
        std::cout << "The nearest mango seller is: "
                  << mango_seller << std::endl;
    }

    return 0;
}
