#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include "Node.hpp"
#include "Edge.hpp"

namespace dijkstra {
namespace graph {

/**
 * @class Graph
 * @brief Represents a directed weighted graph for path finding.
 * 
 * This graph supports nodes and edges with multiple weight criteria,
 * making it suitable for complex travel planning scenarios.
 */
class Graph {
public:
    using NodeMap = std::unordered_map<Node::NodeId, NodePtr>;
    using EdgeList = std::vector<EdgePtr>;
    using AdjacencyList = std::unordered_map<Node::NodeId, EdgeList>;
    
    /**
     * @brief Default constructor.
     */
    Graph() = default;
    
    /**
     * @brief Virtual destructor.
     */
    virtual ~Graph() = default;
    
    /**
     * @brief Add a node to the graph.
     * @param node Shared pointer to the node to add
     * @return true if the node was added successfully, false if it already exists
     */
    bool addNode(NodePtr node);
    
    /**
     * @brief Remove a node from the graph.
     * @param nodeId ID of the node to remove
     * @return true if the node was removed successfully, false if it doesn't exist
     */
    bool removeNode(const Node::NodeId& nodeId);
    
    /**
     * @brief Add an edge to the graph.
     * @param edge Shared pointer to the edge to add
     * @return true if the edge was added successfully, false otherwise
     */
    bool addEdge(EdgePtr edge);
    
    /**
     * @brief Remove an edge from the graph.
     * @param edgeId ID of the edge to remove
     * @return true if the edge was removed successfully, false if it doesn't exist
     */
    bool removeEdge(const Edge::EdgeId& edgeId);
    
    /**
     * @brief Get a node by its ID.
     * @param nodeId ID of the node to retrieve
     * @return Shared pointer to the node, or nullptr if not found
     */
    NodePtr getNode(const Node::NodeId& nodeId) const;
    
    /**
     * @brief Get all edges originating from a specific node.
     * @param nodeId ID of the source node
     * @return Vector of edges originating from the node
     */
    EdgeList getOutgoingEdges(const Node::NodeId& nodeId) const;
    
    /**
     * @brief Get all nodes in the graph.
     * @return Vector of all nodes
     */
    std::vector<NodePtr> getAllNodes() const;
    
    /**
     * @brief Get all edges in the graph.
     * @return Vector of all edges
     */
    std::vector<EdgePtr> getAllEdges() const;
    
    /**
     * @brief Get the number of nodes in the graph.
     * @return Number of nodes
     */
    size_t getNodeCount() const { return nodes_.size(); }
    
    /**
     * @brief Get the number of edges in the graph.
     * @return Number of edges
     */
    size_t getEdgeCount() const { return edges_.size(); }
    
    /**
     * @brief Check if the graph is empty.
     * @return true if the graph has no nodes, false otherwise
     */
    bool isEmpty() const { return nodes_.empty(); }
    
    /**
     * @brief Clear all nodes and edges from the graph.
     */
    void clear();

private:
    NodeMap nodes_;                  ///< Map of node IDs to node objects
    AdjacencyList adjacencyList_;    ///< Adjacency list representation
    std::vector<EdgePtr> edges_;     ///< List of all edges in the graph
};

} // namespace graph
} // namespace dijkstra