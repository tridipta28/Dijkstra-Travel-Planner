#include "PathFinder.hpp"

namespace dijkstra {
namespace graph {

PathFinder::PathFinder(const Graph& graph) : graph_(graph) {
}

PathResult PathFinder::findShortestPath(
    const Node::NodeId& source,
    const Node::NodeId& destination,
    OptimizationMode mode) {
    
    PathResult result;
    
    // Check if source and destination nodes exist
    auto sourceNode = graph_.getNode(source);
    auto destNode = graph_.getNode(destination);
    
    if (!sourceNode || !destNode) {
        return result; // Source or destination not found
    }
    
    // Distance map (node ID -> distance)
    std::unordered_map<Node::NodeId, double> distances;
    
    // Predecessor map (node ID -> predecessor node ID)
    std::unordered_map<Node::NodeId, Node::NodeId> predecessors;
    
    // Set of nodes that have not been processed yet
    std::priority_queue<NodeDistance, std::vector<NodeDistance>, std::greater<NodeDistance>> pq;
    
    // Initialize distances
    for (const auto& node : graph_.getAllNodes()) {
        const auto& nodeId = node->getId();
        distances[nodeId] = (nodeId == source) ? 0.0 : std::numeric_limits<double>::infinity();
    }
    
    // Initialize priority queue
    pq.push({source, 0.0});
    
    // Dijkstra's algorithm
    while (!pq.empty()) {
        NodeDistance current = pq.top();
        pq.pop();
        
        const auto& currentId = current.nodeId;
        double currentDist = current.distance;
        
        // If we've reached the destination, we can stop
        if (currentId == destination) {
            break;
        }
        
        // Skip if we've found a better path already
        if (currentDist > distances[currentId]) {
            continue;
        }
        
        // Process all outgoing edges
        for (const auto& edge : graph_.getOutgoingEdges(currentId)) {
            const auto& neighborId = edge->getDestination()->getId();
            double weight = getEdgeWeight(edge, mode);
            double dist = currentDist + weight;
            
            // If we've found a better path
            if (dist < distances[neighborId]) {
                distances[neighborId] = dist;
                predecessors[neighborId] = currentId;
                pq.push({neighborId, dist});
            }
        }
    }
    
    // Check if a path was found
    if (distances[destination] == std::numeric_limits<double>::infinity()) {
        return result; // No path found
    }
    
    // Reconstruct the path
    auto path = reconstructPath(predecessors, source, destination);
    
    // Calculate metrics
    double totalDistance = 0.0;
    double totalTime = 0.0;
    double totalCost = 0.0;
    
    for (size_t i = 0; i < path.size() - 1; ++i) {
        const auto& currentId = path[i];
        const auto& nextId = path[i + 1];
        
        // Find the edge between current and next node
        auto edgeList = graph_.getOutgoingEdges(currentId);
        auto edgeIt = std::find_if(edgeList.begin(), edgeList.end(),
            [&nextId](const EdgePtr& edge) {
                return edge->getDestination()->getId() == nextId;
            });
        
        if (edgeIt != edgeList.end()) {
            EdgePtr edge = *edgeIt;
            totalDistance += edge->getWeight();
            totalTime += edge->getTimeWeight();
            totalCost += edge->getCostWeight();
        }
    }
    
    // Set the result
    result.setFound(true);
    result.setPath(path);
    result.setTotalDistance(totalDistance);
    result.setTotalTime(totalTime);
    result.setTotalCost(totalCost);
    
    return result;
}

std::unordered_map<Node::NodeId, double> PathFinder::findShortestPaths(
    const Node::NodeId& source,
    OptimizationMode mode) {
    
    // Distance map (node ID -> distance)
    std::unordered_map<Node::NodeId, double> distances;
    
    // Check if source node exists
    if (!graph_.getNode(source)) {
        return distances; // Source not found
    }
    
    // Set of processed nodes
    std::unordered_set<Node::NodeId> processed;
    
    // Initialize distances
    for (const auto& node : graph_.getAllNodes()) {
        const auto& nodeId = node->getId();
        distances[nodeId] = (nodeId == source) ? 0.0 : std::numeric_limits<double>::infinity();
    }
    
    // Dijkstra's algorithm
    while (processed.size() < graph_.getNodeCount()) {
        // Find the node with the minimum distance
        double minDist = std::numeric_limits<double>::infinity();
        Node::NodeId minNode;
        
        for (const auto& pair : distances) {
            const auto& nodeId = pair.first;
            double dist = pair.second;
            
            if (processed.find(nodeId) == processed.end() && dist < minDist) {
                minDist = dist;
                minNode = nodeId;
            }
        }
        
        // If no more reachable nodes, break
        if (minDist == std::numeric_limits<double>::infinity()) {
            break;
        }
        
        // Mark node as processed
        processed.insert(minNode);
        
        // Update distances to neighbors
        for (const auto& edge : graph_.getOutgoingEdges(minNode)) {
            const auto& neighborId = edge->getDestination()->getId();
            
            if (processed.find(neighborId) == processed.end()) {
                double weight = getEdgeWeight(edge, mode);
                double dist = distances[minNode] + weight;
                
                if (dist < distances[neighborId]) {
                    distances[neighborId] = dist;
                }
            }
        }
    }
    
    return distances;
}

double PathFinder::getEdgeWeight(EdgePtr edge, OptimizationMode mode) const {
    switch (mode) {
        case OptimizationMode::DISTANCE:
            return edge->getWeight();
        case OptimizationMode::TIME:
            return edge->getTimeWeight();
        case OptimizationMode::COST:
            return edge->getCostWeight();
        case OptimizationMode::BALANCED:
            // Balanced optimization: normalize and combine all three weights
            double distNorm = edge->getWeight() / 100.0;       // Normalize to approximately 0-1
            double timeNorm = edge->getTimeWeight() / 5.0;     // Normalize to approximately 0-1
            double costNorm = edge->getCostWeight() / 50.0;    // Normalize to approximately 0-1
            return (distNorm + timeNorm + costNorm) / 3.0;     // Equal weight to all three
        default:
            return edge->getWeight();
    }
}

PathFinder::Path PathFinder::reconstructPath(
    const std::unordered_map<Node::NodeId, Node::NodeId>& predecessors,
    const Node::NodeId& source,
    const Node::NodeId& destination) const {
    
    Path path;
    
    for (Node::NodeId at = destination; ; at = predecessors.at(at)) {
        path.push_back(at);
        
        if (at == source) {
            break;
        }
        
        // Check for missing predecessor (should not happen with a correct graph)
        if (predecessors.find(at) == predecessors.end()) {
            path.clear();
            return path;
        }
    }
    
    // Reverse the path to get it from source to destination
    std::reverse(path.begin(), path.end());
    return path;
}

} // namespace graph
} // namespace dijkstra