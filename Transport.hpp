#pragma once

#include <string>
#include <memory>

namespace dijkstra {
namespace travel {

/**
 * @enum TransportMode
 * @brief Enumeration of different transportation modes.
 */
enum class TransportMode {
    WALKING,    ///< Walking
    CYCLING,    ///< Cycling/Biking
    DRIVING,    ///< Car/Driving
    PUBLIC_BUS, ///< Public bus
    TRAIN,      ///< Train/Rail
    SUBWAY,     ///< Subway/Metro
    TAXI,       ///< Taxi/Rideshare
    FLIGHT      ///< Flight/Airplane
};

/**
 * @class Transport
 * @brief Base class for transportation modes.
 * 
 * This class defines the interface for different transportation methods
 * and provides common functionality for travel planning.
 */
class Transport {
public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~Transport() = default;
    
    /**
     * @brief Get the transportation mode.
     * @return The transport mode
     */
    virtual TransportMode getMode() const = 0;
    
    /**
     * @brief Get the name of the transportation mode.
     * @return String representation of the mode
     */
    virtual std::string getName() const = 0;
    
    /**
     * @brief Get the average speed in km/h.
     * @return Average speed
     */
    virtual double getAverageSpeed() const = 0;
    
    /**
     * @brief Get the cost per kilometer.
     * @return Cost per km
     */
    virtual double getCostPerKm() const = 0;
    
    /**
     * @brief Get the comfort rating (1-10).
     * @return Comfort rating
     */
    virtual int getComfortRating() const = 0;
    
    /**
     * @brief Get the environmental rating (1-10, 10 being most eco-friendly).
     * @return Environmental rating
     */
    virtual int getEnvironmentalRating() const = 0;
    
    /**
     * @brief Calculate travel time for a given distance.
     * @param distanceKm Distance in kilometers
     * @return Travel time in hours
     */
    virtual double calculateTravelTime(double distanceKm) const {
        return distanceKm / getAverageSpeed();
    }
    
    /**
     * @brief Calculate travel cost for a given distance.
     * @param distanceKm Distance in kilometers
     * @return Travel cost
     */
    virtual double calculateTravelCost(double distanceKm) const {
        return distanceKm * getCostPerKm();
    }
};

/**
 * @class WalkingTransport
 * @brief Walking transportation mode.
 */
class WalkingTransport : public Transport {
public:
    TransportMode getMode() const override { return TransportMode::WALKING; }
    std::string getName() const override { return "Walking"; }
    double getAverageSpeed() const override { return 5.0; } // 5 km/h
    double getCostPerKm() const override { return 0.0; }    // Free
    int getComfortRating() const override { return 3; }
    int getEnvironmentalRating() const override { return 10; }
};

/**
 * @class DrivingTransport
 * @brief Driving/Car transportation mode.
 */
class DrivingTransport : public Transport {
public:
    TransportMode getMode() const override { return TransportMode::DRIVING; }
    std::string getName() const override { return "Driving"; }
    double getAverageSpeed() const override { return 60.0; } // 60 km/h
    double getCostPerKm() const override { return 0.15; }    // $0.15 per km
    int getComfortRating() const override { return 8; }
    int getEnvironmentalRating() const override { return 3; }
};

/**
 * @class PublicBusTransport
 * @brief Public bus transportation mode.
 */
class PublicBusTransport : public Transport {
public:
    TransportMode getMode() const override { return TransportMode::PUBLIC_BUS; }
    std::string getName() const override { return "Public Bus"; }
    double getAverageSpeed() const override { return 25.0; } // 25 km/h
    double getCostPerKm() const override { return 0.08; }    // $0.08 per km
    int getComfortRating() const override { return 5; }
    int getEnvironmentalRating() const override { return 8; }
};

// Define shared pointer types for Transport classes
using TransportPtr = std::shared_ptr<Transport>;

/**
 * @class TransportFactory
 * @brief Factory class for creating transport instances.
 */
class TransportFactory {
public:
    /**
     * @brief Create a transport instance based on mode.
     * @param mode The transport mode
     * @return Shared pointer to the transport instance
     */
    static TransportPtr createTransport(TransportMode mode);
    
    /**
     * @brief Get string representation of transport mode.
     * @param mode The transport mode
     * @return String representation
     */
    static std::string transportModeToString(TransportMode mode);
    
    /**
     * @brief Parse transport mode from string.
     * @param str String representation
     * @return Transport mode
     */
    static TransportMode stringToTransportMode(const std::string& str);
};

} // namespace travel
} // namespace dijkstra