#include <set>
#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using StateSet   = std::set<std::string>;
using StationSet = StateSet;
using StationMap = std::unordered_map<std::string, std::set<std::string>>;

std::set<std::string>
StationSetCoveringSolver(StateSet states_needed,
                         StationMap stations)
{
    StateSet final_stations;
    while (!states_needed.empty()) {
        std::string best_station = "";
        StateSet states_covered;
        for (const auto& kv : stations) {
            StateSet covered;
            std::set_intersection(states_needed.begin(),
                                  states_needed.end(),
                                  kv.second.begin(),
                                  kv.second.end(),
                                  std::inserter(covered, covered.begin()));
            if (covered.size() > states_covered.size()) {
                best_station   = kv.first;
                states_covered = covered;
            }
        }

        StateSet tmp;
        std::set_difference(states_needed.begin(),
                            states_needed.end(),
                            states_covered.begin(),
                            states_covered.end(),
                            std::inserter(tmp, tmp.begin()));
        states_needed = tmp;

        final_stations.insert(best_station);
    }
    return final_stations;
}

int main(void)
{
    StateSet states_needed {
        "mt", "wa", "or", "id", "nv", "ut", "ca", "az"
    };
    StationMap stations {
        {"kone", {"id", "nv", "ut"}},
        {"ktwo", {"wa", "id", "mt"}},
        {"kthree", {"or", "nv", "ca"}},
        {"kfour", {"nv", "ut"}},
        {"kfive", {"ca", "az"}}
    };

    StationSet soln = StationSetCoveringSolver(states_needed, stations);

    std::cout << "Solution Station Set = { ";
    for (const std::string& station : soln)
        std::cout << station << ' ';
    std::cout << "}" << std::endl;

    return 0;
}
