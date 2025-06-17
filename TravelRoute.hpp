#pragma once

#include <vector>
#include <string>
#include <memory>
#include <chrono>
#include "../geo/GeoCoordinate.hpp"
#include "Transport.hpp"

namespace dijkstra {
namespace travel {

/**
 * @class RouteSegment
 * @brief Represents a single segment of a travel route.
 */
class RouteSegment {
public:
    RouteSegment(const std::string& fromLocation,
                 const std::string& toLocation,
                 const geo::GeoCoordinate& fromCoord,
                 const geo::GeoCoordinate& toCoord,
                 TransportPtr transport)
        : fromLocation_(fromLocation)
        , toLocation_(toLocation)
        , fromCoordinate_(fromCoord)
        , toCoordinate_(toCoord)
        , transport_(transport)
        , distance_(fromCoord.distanceTo(toCoord))
        , travelTime_(transport->calculateTravelTime(distance_))
        , cost_(transport->calculateTravelCost(distance_)) {}
    
    const std::string& getFromLocation() const { return fromLocation_; }
    const std::string& getToLocation() const { return toLocation_; }
    const geo::GeoCoordinate& getFromCoordinate() const { return fromCoordinate_; }
    const geo::GeoCoordinate& getToCoordinate() const { return toCoordinate_; }
    TransportPtr getTransport() const { return transport_; }
    double getDistance() const { return distance_; }
    double getTravelTime() const { return travelTime_; }
    double getCost() const { return cost_; }
    
    void setNotes(const std::string& notes) { notes_ = notes; }
    const std::string& getNotes() const { return notes_; }

private:
    std::string fromLocation_;
    std::string toLocation_;
    geo::GeoCoordinate fromCoordinate_;
    geo::GeoCoordinate toCoordinate_;
    TransportPtr transport_;
    double distance_;    // in km
    double travelTime_;  // in hours
    double cost_;        // in currency units
    std::string notes_;
};

/**
 * @class TravelRoute
 * @brief Represents a complete travel route with multiple segments.
 */
class TravelRoute {
public:
    using RouteSegmentPtr = std::shared_ptr<RouteSegment>;
    using SegmentList = std::vector<RouteSegmentPtr>;
    
    TravelRoute() = default;
    explicit TravelRoute(const std::string& routeId) : routeId_(routeId) {}
    
    void addSegment(RouteSegmentPtr segment) {
        segments_.push_back(segment);
        updateTotals();
    }
    
    void removeSegment(size_t index) {
        if (index < segments_.size()) {
            segments_.erase(segments_.begin() + index);
            updateTotals();
        }
    }
    
    const SegmentList& getSegments() const { return segments_; }
    size_t getSegmentCount() const { return segments_.size(); }
    
    double getTotalDistance() const { return totalDistance_; }
    double getTotalTime() const { return totalTime_; }
    double getTotalCost() const { return totalCost_; }
    
    const std::string& getRouteId() const { return routeId_; }
    void setRouteId(const std::string& id) { routeId_ = id; }
    
    const std::string& getDescription() const { return description_; }
    void setDescription(const std::string& desc) { description_ = desc; }
    
    bool isEmpty() const { return segments_.empty(); }
    
    /**
     * @brief Get the starting location of the route.
     * @return Starting location name
     */
    std::string getStartLocation() const {
        return segments_.empty() ? "" : segments_[0]->getFromLocation();
    }
    
    /**
     * @brief Get the ending location of the route.
     * @return Ending location name
     */
    std::string getEndLocation() const {
        return segments_.empty() ? "" : segments_.back()->getToLocation();
    }
    
    /**
     * @brief Calculate route efficiency score (distance/time ratio).
     * @return Efficiency score
     */
    double getEfficiencyScore() const {
        return totalTime_ > 0 ? totalDistance_ / totalTime_ : 0.0;
    }

private:
    std::string routeId_;
    std::string description_;
    SegmentList segments_;
    double totalDistance_ = 0.0;
    double totalTime_ = 0.0;
    double totalCost_ = 0.0;
    
    void updateTotals() {
        totalDistance_ = 0.0;
        totalTime_ = 0.0;
        totalCost_ = 0.0;
        
        for (const auto& segment : segments_) {
            totalDistance_ += segment->getDistance();
            totalTime_ += segment->getTravelTime();
            totalCost_ += segment->getCost();
        }
    }
};

using TravelRoutePtr = std::shared_ptr<TravelRoute>;

} // namespace travel
} // namespace dijkstra