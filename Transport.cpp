#include "Transport.hpp"
#include <stdexcept>
#include <unordered_map>
#include <algorithm>

namespace dijkstra {
namespace travel {

/**
 * @class CyclingTransport
 * @brief Cycling transportation mode.
 */
class CyclingTransport : public Transport {
public:
    TransportMode getMode() const override { return TransportMode::CYCLING; }
    std::string getName() const override { return "Cycling"; }
    double getAverageSpeed() const override { return 15.0; } // 15 km/h
    double getCostPerKm() const override { return 0.02; }    // $0.02 per km (maintenance)
    int getComfortRating() const override { return 4; }
    int getEnvironmentalRating() const override { return 9; }
};

/**
 * @class TrainTransport
 * @brief Train transportation mode.
 */
class TrainTransport : public Transport {
public:
    TransportMode getMode() const override { return TransportMode::TRAIN; }
    std::string getName() const override { return "Train"; }
    double getAverageSpeed() const override { return 80.0; } // 80 km/h
    double getCostPerKm() const override { return 0.12; }    // $0.12 per km
    int getComfortRating() const override { return 7; }
    int getEnvironmentalRating() const override { return 8; }
};

/**
 * @class SubwayTransport
 * @brief Subway/Metro transportation mode.
 */
class SubwayTransport : public Transport {
public:
    TransportMode getMode() const override { return TransportMode::SUBWAY; }
    std::string getName() const override { return "Subway/Metro"; }
    double getAverageSpeed() const override { return 35.0; } // 35 km/h
    double getCostPerKm() const override { return 0.10; }    // $0.10 per km
    int getComfortRating() const override { return 6; }
    int getEnvironmentalRating() const override { return 9; }
};

/**
 * @class TaxiTransport
 * @brief Taxi transportation mode.
 */
class TaxiTransport : public Transport {
public:
    TransportMode getMode() const override { return TransportMode::TAXI; }
    std::string getName() const override { return "Taxi"; }
    double getAverageSpeed() const override { return 40.0; } // 40 km/h
    double getCostPerKm() const override { return 1.50; }    // $1.50 per km
    int getComfortRating() const override { return 8; }
    int getEnvironmentalRating() const override { return 4; }
};

/**
 * @class FlightTransport
 * @brief Flight transportation mode.
 */
class FlightTransport : public Transport {
public:
    TransportMode getMode() const override { return TransportMode::FLIGHT; }
    std::string getName() const override { return "Flight"; }
    double getAverageSpeed() const override { return 800.0; } // 800 km/h
    double getCostPerKm() const override { return 0.25; }     // $0.25 per km
    int getComfortRating() const override { return 6; }
    int getEnvironmentalRating() const override { return 2; }
};

TransportPtr TransportFactory::createTransport(TransportMode mode) {
    switch (mode) {
        case TransportMode::WALKING:
            return std::make_shared<WalkingTransport>();
        case TransportMode::CYCLING:
            return std::make_shared<CyclingTransport>();
        case TransportMode::DRIVING:
            return std::make_shared<DrivingTransport>();
        case TransportMode::PUBLIC_BUS:
            return std::make_shared<PublicBusTransport>();
        case TransportMode::TRAIN:
            return std::make_shared<TrainTransport>();
        case TransportMode::SUBWAY:
            return std::make_shared<SubwayTransport>();
        case TransportMode::TAXI:
            return std::make_shared<TaxiTransport>();
        case TransportMode::FLIGHT:
            return std::make_shared<FlightTransport>();
        default:
            throw std::invalid_argument("Unsupported transport mode");
    }
}

std::string TransportFactory::transportModeToString(TransportMode mode) {
    static const std::unordered_map<TransportMode, std::string> modeMap = {
        {TransportMode::WALKING, "walking"},
        {TransportMode::CYCLING, "cycling"},
        {TransportMode::DRIVING, "driving"},
        {TransportMode::PUBLIC_BUS, "public_bus"},
        {TransportMode::TRAIN, "train"},
        {TransportMode::SUBWAY, "subway"},
        {TransportMode::TAXI, "taxi"},
        {TransportMode::FLIGHT, "flight"}
    };
    
    auto it = modeMap.find(mode);
    return (it != modeMap.end()) ? it->second : "unknown";
}

TransportMode TransportFactory::stringToTransportMode(const std::string& str) {
    static const std::unordered_map<std::string, TransportMode> modeMap = {
        {"walking", TransportMode::WALKING},
        {"cycling", TransportMode::CYCLING},
        {"driving", TransportMode::DRIVING},
        {"public_bus", TransportMode::PUBLIC_BUS},
        {"train", TransportMode::TRAIN},
        {"subway", TransportMode::SUBWAY},
        {"taxi", TransportMode::TAXI},
        {"flight", TransportMode::FLIGHT}
    };
    
    // Convert to lowercase for case-insensitive comparison
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    
    auto it = modeMap.find(lowerStr);
    if (it != modeMap.end()) {
        return it->second;
    }
    
    throw std::invalid_argument("Unsupported transport mode string: " + str);
}

} // namespace travel
} // namespace dijkstra