#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <limits>
#include <iomanip>

#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>


int main() {
    const int NUM_VERTICES = 10;

    using Graph = boost::adjacency_matrix<
        boost::undirectedS,
        boost::no_property,
        boost::property<boost::edge_weight_t, int>
    >;

    Graph g(NUM_VERTICES);
    auto weights = boost::get(boost::edge_weight, g);

    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<int> dist(1, 10);

    for (int i = 0; i < NUM_VERTICES; ++i) {
        for (int j = i + 1; j < NUM_VERTICES; ++j) {
            add_edge(i, j, dist(engine), g);
        }
    }

    std::cout << "Adjacency Matrix:" << std::endl;
    std::cout << "     ";
    for (int i = 0; i < NUM_VERTICES; ++i) {
        std::cout << std::setw(3) << i << " ";
    }
    std::cout << "\n-----";
    for (int i = 0; i < NUM_VERTICES; ++i) {
        std::cout << "----";
    }
    std::cout << std::endl;

    for (int i = 0; i < NUM_VERTICES; ++i) {
        std::cout << std::setw(3) << i << " |";
        for (int j = 0; j < NUM_VERTICES; ++j) {
            if (i == j) {
                std::cout << std::setw(3) << 0 << " ";
            } else {
                auto edge_descriptor = boost::edge(i, j, g);
                if (edge_descriptor.second) {
                    std::cout << std::setw(3) << weights[edge_descriptor.first] << " ";
                } else {
                    std::cout << std::setw(3) << "X" << " ";
                }
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::vector<int> path(NUM_VERTICES);
    std::iota(path.begin(), path.end(), 0);

    long long min_cost = std::numeric_limits<long long>::max();
    std::vector<int> best_path;

    do {
        long long current_cost = 0;
        bool possible = true;

        for (int i = 0; i < NUM_VERTICES - 1; ++i) {
            auto edge_descriptor = boost::edge(path[i], path[i+1], g);
            if (!edge_descriptor.second) {
                possible = false;
                break;
            }
            current_cost += weights[edge_descriptor.first];
        }

        if (!possible) continue;

        auto closing_edge = boost::edge(path.back(), path.front(), g);
        if(!closing_edge.second) continue;
        current_cost += weights[closing_edge.first];

        if (current_cost < min_cost) {
            min_cost = current_cost;
            best_path = path;
        }

    } while (std::next_permutation(path.begin() + 1, path.end()));


    if (best_path.empty()) {
        std::cout << "Could not find a valid path." << std::endl;
    } else {
        std::cout << "Optimal path:" << std::endl;
        for (int vertex : best_path) {
            std::cout << vertex << " -> ";
        }
        std::cout << best_path.front() << std::endl;

        std::cout << "\nTotal Cost: " << min_cost << std::endl;
    }
}
