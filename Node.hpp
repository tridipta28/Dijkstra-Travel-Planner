#pragma once

#include <string>
#include <memory>

namespace dijkstra {
namespace graph {

/**
 * @class Node
 * @brief Represents a node in the graph structure.
 * 
 * A node can represent a location, intersection, or any point of interest in the travel network.
 * Each node has a unique identifier and can contain additional metadata.
 */
class Node {
public:
    using NodeId = std::string;
    
    /**
     * @brief Default constructor.
     */
    Node() = default;
    
    /**
     * @brief Constructs a node with a given ID.
     * @param id Unique identifier for the node
     */
    explicit Node(const NodeId& id) : id_(id) {}
    
    /**
     * @brief Constructs a node with a given ID and name.
     * @param id Unique identifier for the node
     * @param name Human-readable name for the node
     */
    Node(const NodeId& id, const std::string& name) : id_(id), name_(name) {}
    
    /**
     * @brief Virtual destructor for polymorphic behavior.
     */
    virtual ~Node() = default;
    
    /**
     * @brief Get the node's unique identifier.
     * @return The node ID
     */
    const NodeId& getId() const { return id_; }
    
    /**
     * @brief Set the node's unique identifier.
     * @param id New node ID
     */
    void setId(const NodeId& id) { id_ = id; }
    
    /**
     * @brief Get the node's human-readable name.
     * @return The node name
     */
    const std::string& getName() const { return name_; }
    
    /**
     * @brief Set the node's human-readable name.
     * @param name New node name
     */
    void setName(const std::string& name) { name_ = name; }
    
    /**
     * @brief Equality comparison operator.
     * @param other Another node to compare with
     * @return true if the nodes have the same ID, false otherwise
     */
    bool operator==(const Node& other) const {
        return id_ == other.id_;
    }
    
    /**
     * @brief Inequality comparison operator.
     * @param other Another node to compare with
     * @return true if the nodes have different IDs, false otherwise
     */
    bool operator!=(const Node& other) const {
        return !(*this == other);
    }
    
    /**
     * @brief Less-than comparison operator for container compatibility.
     * @param other Another node to compare with
     * @return true if this node's ID is lexicographically less than the other's, false otherwise
     */
    bool operator<(const Node& other) const {
        return id_ < other.id_;
    }

private:
    NodeId id_;        ///< Unique identifier for the node
    std::string name_; ///< Human-readable name for the node
};

// Define a shared pointer type for Node
using NodePtr = std::shared_ptr<Node>;

} // namespace graph
} // namespace dijkstra