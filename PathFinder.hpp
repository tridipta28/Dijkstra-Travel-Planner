#pragma once

#include <vector>
#include <unordered_map>
#include <limits>
#include <queue>
#include "Graph.hpp"

namespace dijkstra {
namespace graph {

/**
 * @class PathResult
 * @brief Represents the result of a path finding operation.
 */
class PathResult {
public:
    using Path = std::vector<Node::NodeId>;
    
    PathResult() : totalDistance_(0.0), totalTime_(0.0), totalCost_(0.0), found_(false) {}
    
    bool isFound() const { return found_; }
    void setFound(bool found) { found_ = found; }
    
    const Path& getPath() const { return path_; }
    void setPath(const Path& path) { path_ = path; }
    
    double getTotalDistance() const { return totalDistance_; }
    void setTotalDistance(double distance) { totalDistance_ = distance; }
    
    double getTotalTime() const { return totalTime_; }
    void setTotalTime(double time) { totalTime_ = time; }
    
    double getTotalCost() const { return totalCost_; }
    void setTotalCost(double cost) { totalCost_ = cost; }

private:
    Path path_;
    double totalDistance_;
    double totalTime_;
    double totalCost_;
    bool found_;
};

/**
 * @class PathFinder
 * @brief Implements Dijkstra's algorithm for shortest path finding.
 */
class PathFinder {
public:
    enum class OptimizationMode {
        DISTANCE,  ///< Optimize for shortest distance
        TIME,      ///< Optimize for shortest time
        COST,      ///< Optimize for lowest cost
        BALANCED   ///< Balanced optimization
    };
    
    explicit PathFinder(const Graph& graph);
    
    /**
     * @brief Find the shortest path between two nodes.
     * @param source Source node ID
     * @param destination Destination node ID
     * @param mode Optimization mode
     * @return PathResult containing the path and metrics
     */
    PathResult findShortestPath(const Node::NodeId& source, 
                               const Node::NodeId& destination,
                               OptimizationMode mode = OptimizationMode::DISTANCE);
    
    /**
     * @brief Find shortest paths from source to all other nodes.
     * @param source Source node ID
     * @param mode Optimization mode
     * @return Map of node IDs to their shortest distances
     */
    std::unordered_map<Node::NodeId, double> findShortestPaths(
        const Node::NodeId& source,
        OptimizationMode mode = OptimizationMode::DISTANCE);

private:
    struct NodeDistance {
        Node::NodeId nodeId;
        double distance;
        
        bool operator>(const NodeDistance& other) const {
            return distance > other.distance;
        }
    };
    
    const Graph& graph_;
    
    double getEdgeWeight(EdgePtr edge, OptimizationMode mode) const;
    Path reconstructPath(const std::unordered_map<Node::NodeId, Node::NodeId>& predecessors,
                        const Node::NodeId& source, const Node::NodeId& destination) const;
};

} // namespace graph
} // namespace dijkstra