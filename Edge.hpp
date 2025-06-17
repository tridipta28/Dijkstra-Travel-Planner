#pragma once

#include <memory>
#include "Node.hpp"

namespace dijkstra {
namespace graph {

/**
 * @class Edge
 * @brief Represents an edge in the graph structure.
 * 
 * An edge connects two nodes and can have multiple weights representing different criteria
 * such as distance, time, cost, etc. This allows for multi-criteria path finding.
 */
class Edge {
public:
    using EdgeId = std::string;
    using Weight = double;
    
    /**
     * @brief Default constructor.
     */
    Edge() = default;
    
    /**
     * @brief Constructs an edge with source, destination, and weight.
     * @param id Unique identifier for the edge
     * @param source Pointer to the source node
     * @param destination Pointer to the destination node
     * @param weight Primary weight of the edge (e.g., distance)
     */
    Edge(const EdgeId& id, NodePtr source, NodePtr destination, Weight weight)
        : id_(id), source_(source), destination_(destination), weight_(weight) {}
    
    /**
     * @brief Virtual destructor for polymorphic behavior.
     */
    virtual ~Edge() = default;
    
    /**
     * @brief Get the edge's unique identifier.
     * @return The edge ID
     */
    const EdgeId& getId() const { return id_; }
    
    /**
     * @brief Set the edge's unique identifier.
     * @param id New edge ID
     */
    void setId(const EdgeId& id) { id_ = id; }
    
    /**
     * @brief Get the source node of the edge.
     * @return Pointer to the source node
     */
    NodePtr getSource() const { return source_; }
    
    /**
     * @brief Set the source node of the edge.
     * @param source Pointer to the new source node
     */
    void setSource(NodePtr source) { source_ = source; }
    
    /**
     * @brief Get the destination node of the edge.
     * @return Pointer to the destination node
     */
    NodePtr getDestination() const { return destination_; }
    
    /**
     * @brief Set the destination node of the edge.
     * @param destination Pointer to the new destination node
     */
    void setDestination(NodePtr destination) { destination_ = destination; }
    
    /**
     * @brief Get the primary weight of the edge.
     * @return The primary weight value
     */
    Weight getWeight() const { return weight_; }
    
    /**
     * @brief Set the primary weight of the edge.
     * @param weight New primary weight value
     */
    void setWeight(Weight weight) { weight_ = weight; }
    
    /**
     * @brief Get the secondary weight of the edge (e.g., time).
     * @return The secondary weight value
     */
    Weight getTimeWeight() const { return timeWeight_; }
    
    /**
     * @brief Set the secondary weight of the edge (e.g., time).
     * @param timeWeight New secondary weight value
     */
    void setTimeWeight(Weight timeWeight) { timeWeight_ = timeWeight; }
    
    /**
     * @brief Get the tertiary weight of the edge (e.g., cost).
     * @return The tertiary weight value
     */
    Weight getCostWeight() const { return costWeight_; }
    
    /**
     * @brief Set the tertiary weight of the edge (e.g., cost).
     * @param costWeight New tertiary weight value
     */
    void setCostWeight(Weight costWeight) { costWeight_ = costWeight; }
    
    /**
     * @brief Equality comparison operator.
     * @param other Another edge to compare with
     * @return true if the edges have the same ID, false otherwise
     */
    bool operator==(const Edge& other) const {
        return id_ == other.id_;
    }
    
    /**
     * @brief Inequality comparison operator.
     * @param other Another edge to compare with
     * @return true if the edges have different IDs, false otherwise
     */
    bool operator!=(const Edge& other) const {
        return !(*this == other);
    }
    
    /**
     * @brief Less-than comparison operator for container compatibility.
     * @param other Another edge to compare with
     * @return true if this edge's ID is lexicographically less than the other's, false otherwise
     */
    bool operator<(const Edge& other) const {
        return id_ < other.id_;
    }

private:
    EdgeId id_;                ///< Unique identifier for the edge
    NodePtr source_;           ///< Pointer to the source node
    NodePtr destination_;      ///< Pointer to the destination node
    Weight weight_ = 0.0;      ///< Primary weight of the edge (e.g., distance)
    Weight timeWeight_ = 0.0;  ///< Secondary weight of the edge (e.g., time)
    Weight costWeight_ = 0.0;  ///< Tertiary weight of the edge (e.g., cost)
};

// Define a shared pointer type for Edge
using EdgePtr = std::shared_ptr<Edge>;

} // namespace graph
} // namespace dijkstra