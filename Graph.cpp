#include "Graph.hpp"
#include <algorithm>

namespace dijkstra {
namespace graph {

bool Graph::addNode(NodePtr node) {
    if (!node || nodes_.find(node->getId()) != nodes_.end()) {
        return false; // Node is null or already exists
    }
    
    nodes_[node->getId()] = node;
    adjacencyList_[node->getId()] = EdgeList(); // Initialize empty edge list
    return true;
}

bool Graph::removeNode(const Node::NodeId& nodeId) {
    auto nodeIt = nodes_.find(nodeId);
    if (nodeIt == nodes_.end()) {
        return false; // Node doesn't exist
    }
    
    // Remove all edges connected to this node
    edges_.erase(
        std::remove_if(edges_.begin(), edges_.end(),
            [&nodeId](const EdgePtr& edge) {
                return edge->getSource()->getId() == nodeId || 
                       edge->getDestination()->getId() == nodeId;
            }),
        edges_.end()
    );
    
    // Remove from adjacency list
    adjacencyList_.erase(nodeId);
    
    // Remove references from other nodes' adjacency lists
    for (auto& pair : adjacencyList_) {
        auto& edgeList = pair.second;
        edgeList.erase(
            std::remove_if(edgeList.begin(), edgeList.end(),
                [&nodeId](const EdgePtr& edge) {
                    return edge->getDestination()->getId() == nodeId;
                }),
            edgeList.end()
        );
    }
    
    // Remove the node itself
    nodes_.erase(nodeIt);
    return true;
}

bool Graph::addEdge(EdgePtr edge) {
    if (!edge || !edge->getSource() || !edge->getDestination()) {
        return false; // Invalid edge
    }
    
    const auto& sourceId = edge->getSource()->getId();
    const auto& destId = edge->getDestination()->getId();
    
    // Ensure both nodes exist in the graph
    if (nodes_.find(sourceId) == nodes_.end() || 
        nodes_.find(destId) == nodes_.end()) {
        return false;
    }
    
    // Check if edge already exists
    auto it = std::find_if(edges_.begin(), edges_.end(),
        [&edge](const EdgePtr& existingEdge) {
            return existingEdge->getId() == edge->getId();
        });
    
    if (it != edges_.end()) {
        return false; // Edge already exists
    }
    
    edges_.push_back(edge);
    adjacencyList_[sourceId].push_back(edge);
    return true;
}

bool Graph::removeEdge(const Edge::EdgeId& edgeId) {
    auto it = std::find_if(edges_.begin(), edges_.end(),
        [&edgeId](const EdgePtr& edge) {
            return edge->getId() == edgeId;
        });
    
    if (it == edges_.end()) {
        return false; // Edge doesn't exist
    }
    
    EdgePtr edge = *it;
    const auto& sourceId = edge->getSource()->getId();
    
    // Remove from adjacency list
    auto& edgeList = adjacencyList_[sourceId];
    edgeList.erase(
        std::remove_if(edgeList.begin(), edgeList.end(),
            [&edgeId](const EdgePtr& e) {
                return e->getId() == edgeId;
            }),
        edgeList.end()
    );
    
    // Remove from edges list
    edges_.erase(it);
    return true;
}

NodePtr Graph::getNode(const Node::NodeId& nodeId) const {
    auto it = nodes_.find(nodeId);
    return (it != nodes_.end()) ? it->second : nullptr;
}

Graph::EdgeList Graph::getOutgoingEdges(const Node::NodeId& nodeId) const {
    auto it = adjacencyList_.find(nodeId);
    return (it != adjacencyList_.end()) ? it->second : EdgeList();
}

std::vector<NodePtr> Graph::getAllNodes() const {
    std::vector<NodePtr> result;
    result.reserve(nodes_.size());
    
    for (const auto& pair : nodes_) {
        result.push_back(pair.second);
    }
    
    return result;
}

std::vector<EdgePtr> Graph::getAllEdges() const {
    return edges_;
}

void Graph::clear() {
    nodes_.clear();
    adjacencyList_.clear();
    edges_.clear();
}

} // namespace graph
} // namespace dijkstra