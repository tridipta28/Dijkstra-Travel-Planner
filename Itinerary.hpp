#pragma once

#include <vector>
#include <string>
#include <memory>
#include <chrono>
#include "TravelRoute.hpp"

namespace dijkstra {
namespace travel {

/**
 * @class ItineraryItem
 * @brief Represents a single item in a travel itinerary.
 */
class ItineraryItem {
public:
    enum class ItemType {
        TRAVEL,         ///< Travel segment
        ACCOMMODATION,  ///< Hotel/lodging
        ACTIVITY,       ///< Tourist activity
        MEAL,          ///< Restaurant/meal
        BREAK          ///< Rest/break time
    };
    
    ItineraryItem(ItemType type, const std::string& title, const std::string& description)
        : type_(type), title_(title), description_(description) {}
    
    ItemType getType() const { return type_; }
    const std::string& getTitle() const { return title_; }
    const std::string& getDescription() const { return description_; }
    
    void setDuration(double hours) { duration_ = hours; }
    double getDuration() const { return duration_; }
    
    void setCost(double cost) { cost_ = cost; }
    double getCost() const { return cost_; }
    
    void setLocation(const std::string& location) { location_ = location; }
    const std::string& getLocation() const { return location_; }

private:
    ItemType type_;
    std::string title_;
    std::string description_;
    std::string location_;
    double duration_ = 0.0;  // in hours
    double cost_ = 0.0;      // in currency units
};

/**
 * @class Itinerary
 * @brief Represents a complete travel itinerary.
 */
class Itinerary {
public:
    using ItineraryItemPtr = std::shared_ptr<ItineraryItem>;
    using ItemList = std::vector<ItineraryItemPtr>;
    
    Itinerary() = default;
    explicit Itinerary(const std::string& title) : title_(title) {}
    
    void setTitle(const std::string& title) { title_ = title; }
    const std::string& getTitle() const { return title_; }
    
    void setDescription(const std::string& desc) { description_ = desc; }
    const std::string& getDescription() const { return description_; }
    
    void addItem(ItineraryItemPtr item) { 
        items_.push_back(item);
        updateTotals();
    }
    
    void removeItem(size_t index) {
        if (index < items_.size()) {
            items_.erase(items_.begin() + index);
            updateTotals();
        }
    }
    
    const ItemList& getItems() const { return items_; }
    size_t getItemCount() const { return items_.size(); }
    
    void addRoute(TravelRoutePtr route) { 
        routes_.push_back(route);
        updateTotals();
    }
    
    const std::vector<TravelRoutePtr>& getRoutes() const { return routes_; }
    
    double getTotalCost() const { return totalCost_; }
    double getTotalDuration() const { return totalDuration_; }
    
    bool isEmpty() const { return items_.empty() && routes_.empty(); }

private:
    std::string title_;
    std::string description_;
    ItemList items_;
    std::vector<TravelRoutePtr> routes_;
    double totalCost_ = 0.0;
    double totalDuration_ = 0.0;
    
    void updateTotals() {
        totalCost_ = 0.0;
        totalDuration_ = 0.0;
        
        for (const auto& item : items_) {
            totalCost_ += item->getCost();
            totalDuration_ += item->getDuration();
        }
        
        for (const auto& route : routes_) {
            totalCost_ += route->getTotalCost();
            totalDuration_ += route->getTotalTime();
        }
    }
};

using ItineraryPtr = std::shared_ptr<Itinerary>;

} // namespace travel
} // namespace dijkstra