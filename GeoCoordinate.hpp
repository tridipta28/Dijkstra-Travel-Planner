#pragma once

#include <cmath>
#include <string>

namespace dijkstra {
namespace geo {

/**
 * @class GeoCoordinate
 * @brief Represents a geographic coordinate with latitude and longitude.
 * 
 * This class provides methods for coordinate manipulation and distance calculations
 * using the Haversine formula for great-circle distances.
 */
class GeoCoordinate {
public:
    /**
     * @brief Default constructor initializing to origin (0, 0).
     */
    GeoCoordinate() : latitude_(0.0), longitude_(0.0) {}
    
    /**
     * @brief Constructs a coordinate with given latitude and longitude.
     * @param latitude Latitude in degrees (-90 to 90)
     * @param longitude Longitude in degrees (-180 to 180)
     */
    GeoCoordinate(double latitude, double longitude)
        : latitude_(latitude), longitude_(longitude) {
        validate();
    }
    
    /**
     * @brief Get the latitude in degrees.
     * @return Latitude value
     */
    double getLatitude() const { return latitude_; }
    
    /**
     * @brief Set the latitude in degrees.
     * @param latitude New latitude value (-90 to 90)
     */
    void setLatitude(double latitude) {
        latitude_ = latitude;
        validate();
    }
    
    /**
     * @brief Get the longitude in degrees.
     * @return Longitude value
     */
    double getLongitude() const { return longitude_; }
    
    /**
     * @brief Set the longitude in degrees.
     * @param longitude New longitude value (-180 to 180)
     */
    void setLongitude(double longitude) {
        longitude_ = longitude;
        validate();
    }
    
    /**
     * @brief Calculate the distance to another coordinate using Haversine formula.
     * @param other Another coordinate
     * @return Distance in kilometers
     */
    double distanceTo(const GeoCoordinate& other) const;
    
    /**
     * @brief Calculate the bearing to another coordinate.
     * @param other Another coordinate
     * @return Bearing in degrees (0-360)
     */
    double bearingTo(const GeoCoordinate& other) const;
    
    /**
     * @brief Check if this coordinate is valid.
     * @return true if valid, false otherwise
     */
    bool isValid() const;
    
    /**
     * @brief Convert to string representation.
     * @return String in format "lat,lng"
     */
    std::string toString() const;
    
    /**
     * @brief Parse coordinate from string.
     * @param str String in format "lat,lng"
     * @return GeoCoordinate object
     */
    static GeoCoordinate fromString(const std::string& str);
    
    /**
     * @brief Equality comparison operator.
     * @param other Another coordinate
     * @return true if coordinates are approximately equal
     */
    bool operator==(const GeoCoordinate& other) const;
    
    /**
     * @brief Inequality comparison operator.
     * @param other Another coordinate
     * @return true if coordinates are not approximately equal
     */
    bool operator!=(const GeoCoordinate& other) const {
        return !(*this == other);
    }

private:
    double latitude_;   ///< Latitude in degrees
    double longitude_;  ///< Longitude in degrees
    
    /**
     * @brief Validate coordinate values.
     */
    void validate();
    
    /**
     * @brief Convert degrees to radians.
     * @param degrees Angle in degrees
     * @return Angle in radians
     */
    static double toRadians(double degrees) {
        return degrees * M_PI / 180.0;
    }
    
    /**
     * @brief Convert radians to degrees.
     * @param radians Angle in radians
     * @return Angle in degrees
     */
    static double toDegrees(double radians) {
        return radians * 180.0 / M_PI;
    }
    
    static constexpr double EARTH_RADIUS_KM = 6371.0; ///< Earth radius in kilometers
    static constexpr double EPSILON = 1e-9; ///< Precision for floating point comparison
};

} // namespace geo
} // namespace dijkstra