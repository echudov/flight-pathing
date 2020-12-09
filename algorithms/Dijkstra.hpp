//Created by Charles Xu on December 7, 2020

#include "../graph/Edge.h"
#include "../graph/Graph.h"
#include <vector>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <limits>

namespace Dijkstra {

    /**
     * Uses Dijkstra's algorithm to get the distances of ALL vertices from the given point 
     * @return unordered_map where the key is the Vertex and the value is a pair of the corresponding distance from the source and the previous vertex
     * If source vertex isn't in the graph, returns an empty map
     */
    template <class Vertex>    
    std::unordered_map<Vertex, std::pair<double, Vertex>> getDistanceDataForVertex(Graph<Vertex>& g_, Vertex source) {
        std::unordered_map<Vertex, std::pair<double, Vertex>> distances;
        if (g_.getVertices().size() == 0) {
            return distances;
        }
        if (!g_.vertexExists(source)) {
            //if the source isn't in the graph, return empty map
            return distances;
        }
        std::vector<Vertex> vertices = g_.getVertices();
        std::unordered_map<Vertex, double> not_visited; //key is Vertex, value is current distance to source (to make it easier to check for next node to visit)
        for (Vertex v : vertices) {
            //set up distances
            not_visited.insert(std::make_pair(v, -1.0));
            distances.insert(std::make_pair(v , std::make_pair(-1.0, Edge<Vertex>().source)));
        }

        if (distances.find(source) == distances.end()) {
            return std::unordered_map<Vertex, std::pair<double, Vertex>>();
        }

        // std::cout << "Getting Data for Source " << source << std::endl;
        Vertex current = source;
        distances[current].first = 0.0;
        distances[current].second = source;

        while (not_visited.size() != 0) {
            //Update weights for nodes adjacent to current
            //Find unvisited node with next smallest distance, set to current

            
            // for (std::pair<Vertex, double> n : not_visited) {
            //     std::cout << n.first;
            // }
            // std::cout << std::endl;
            std::vector<std::pair<Vertex, double>> adjacent = g_.getAdjacentWeighted(current);
            double currentDistance = distances[current].first;
            // std::cout << "Currently on " << current << " at distance " << currentDistance << " with " << adjacent.size() << " adjacent vectors" << std::endl;

            for (std::pair<Vertex, double> adj : adjacent) {
                // std::cout << "Adjacent vertex " << adj.first << " with edge weight " << adj.second << std::endl;
                // std::cout << "Current adjacent distance to source: " << distances[adj.first].first << " with previous vertex " << distances[adj.first].second << std::endl;
                
                Edge<Vertex> currentEdge = g_.getEdge(current, adj.first);
                if (currentEdge.source != current) {
                    continue;
                }
                // std::cout << "Current edge from getEdge: " << currentEdge.source << " to " << currentEdge.dest << " with edge weight " << currentEdge.getWeight() << std::endl;
                if ((distances[adj.first].first == -1.0 || distances[adj.first].first > currentDistance + adj.second) && not_visited.find(adj.first) != not_visited.end()) {
                    //if current distance is -1 (hasn't been visited yet) or is longer than the path from current vector, update the distance
                    not_visited[adj.first] = currentDistance + adj.second;
                    distances[adj.first].first = currentDistance + adj.second;
                    distances[adj.first].second = current;
                    // std::cout << "Updating data. New distance: " << not_visited[adj.first] << ". New prev vertex: " << distances[adj.first].second << std::endl;
                }
            }
            

            double nextShortest = -1.0;
            Vertex nextVertex = current;
            not_visited.erase(current);
            if (not_visited.empty()) {
                break;
            }
            // std::cout << not_visited.size() << " remaining nodes to visit." << std::endl;
            for (std::pair<Vertex, double> v : not_visited) {
                // std::cout << "Checking vertex " << v.first << " with distance " << v.second << ". nextShortest " << nextShortest << std::endl;
                if (not_visited.size() == 1) {
                    if (v.second != -1.0) {
                        nextVertex = v.first;
                    }
                } else {
                    if ((nextShortest == -1.0 && v.second != -1.0) || (nextShortest != -1.0 && v.second != -1.0 && v.second < nextShortest)) {
                        nextVertex = v.first;
                        nextShortest = v.second;
                        // std::cout << "Setting nextVertex to " << nextVertex << " and nextShortest to " << nextShortest << std::endl;
                    }
                }
                
            }
            //if no remaining vertices have a path to the source, break
            if (nextVertex == current) {
                break;
            }

            current = nextVertex;

        }
        return distances;
    }
    
    /**
     * Uses Dijkstra's algorithm to get the distance of the shortest path between two points
     * @return shortest distance between two points as a double. Returns -1.0 if one of the inputs is invalid
     */
    template <class Vertex>    
    double getDistanceBetweenPoints(Graph<Vertex>& g_, Vertex source, Vertex sink) {
        std::unordered_map<Vertex, std::pair<double, Vertex>> distances = Dijkstra::getDistanceDataForVertex(g_, source);
        if (distances.find(sink) == distances.end()) {
            return -1.0;
        }
        return distances[sink].first;
    }

    /**
     * Uses Dijkstra's algorithm to get the shortest path between two points
     * @return shortest path between two points as a vector of Vertex objects. Returns empty vector if one of the inputs is invalid
     */
    template <class Vertex, class Edge>    
    std::vector<Edge> getPathBetweenPoints(Graph<Vertex>& g_, Vertex source, Vertex sink) {
        std::unordered_map<Vertex, std::pair<double, Vertex>> distances = getDistanceDataForVertex(g_, source);
        if (distances.find(sink) == distances.end()) {
            return std::vector<Edge>();
        }
        std::pair<double, Vertex> data = distances[sink];

        std::vector<Edge> path;
        Vertex current = sink;
        while (current != source) {
            data = distances[current];
            //std::cout << "inserting edge " << data.second << " to " << current << std::endl;
            if (!g_.edgeExists(data.second, current)) {
                return std::vector<Edge>();
            }
            path.push_back(g_.getEdge(data.second, current));
            current = data.second;
        }
        std::reverse(path.begin(), path.end());
        return path;
    }

    
}