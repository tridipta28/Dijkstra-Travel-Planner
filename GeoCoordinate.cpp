#include "GeoCoordinate.hpp"
#include <sstream>
#include <stdexcept>
#include <iomanip>

namespace dijkstra {
namespace geo {

double GeoCoordinate::distanceTo(const GeoCoordinate& other) const {
    // Haversine formula for calculating great-circle distances
    double lat1Rad = toRadians(latitude_);
    double lon1Rad = toRadians(longitude_);
    double lat2Rad = toRadians(other.latitude_);
    double lon2Rad = toRadians(other.longitude_);
    
    double deltaLat = lat2Rad - lat1Rad;
    double deltaLon = lon2Rad - lon1Rad;
    
    double a = std::sin(deltaLat / 2) * std::sin(deltaLat / 2) +
               std::cos(lat1Rad) * std::cos(lat2Rad) *
               std::sin(deltaLon / 2) * std::sin(deltaLon / 2);
    
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
    
    return EARTH_RADIUS_KM * c;
}

double GeoCoordinate::bearingTo(const GeoCoordinate& other) const {
    double lat1Rad = toRadians(latitude_);
    double lat2Rad = toRadians(other.latitude_);
    double deltaLonRad = toRadians(other.longitude_ - longitude_);
    
    double y = std::sin(deltaLonRad) * std::cos(lat2Rad);
    double x = std::cos(lat1Rad) * std::sin(lat2Rad) -
               std::sin(lat1Rad) * std::cos(lat2Rad) * std::cos(deltaLonRad);
    
    double bearingRad = std::atan2(y, x);
    double bearingDeg = toDegrees(bearingRad);
    
    // Normalize to 0-360 degrees
    return std::fmod(bearingDeg + 360.0, 360.0);
}

bool GeoCoordinate::isValid() const {
    return latitude_ >= -90.0 && latitude_ <= 90.0 &&
           longitude_ >= -180.0 && longitude_ <= 180.0;
}

std::string GeoCoordinate::toString() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(6) << latitude_ << "," << longitude_;
    return oss.str();
}

GeoCoordinate GeoCoordinate::fromString(const std::string& str) {
    std::istringstream iss(str);
    std::string latStr, lonStr;
    
    if (!std::getline(iss, latStr, ',') || !std::getline(iss, lonStr)) {
        throw std::invalid_argument("Invalid coordinate string format");
    }
    
    try {
        double lat = std::stod(latStr);
        double lon = std::stod(lonStr);
        return GeoCoordinate(lat, lon);
    } catch (const std::exception&) {
        throw std::invalid_argument("Invalid numeric values in coordinate string");
    }
}

bool GeoCoordinate::operator==(const GeoCoordinate& other) const {
    return std::abs(latitude_ - other.latitude_) < EPSILON &&
           std::abs(longitude_ - other.longitude_) < EPSILON;
}

void GeoCoordinate::validate() {
    if (!isValid()) {
        throw std::invalid_argument("Invalid coordinate values");
    }
}

} // namespace geo
} // namespace dijkstra