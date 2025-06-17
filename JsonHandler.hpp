#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "../graph/Graph.hpp"
#include "../travel/TravelRoute.hpp"
#include "../travel/Itinerary.hpp"

namespace dijkstra {
namespace data {

/**
 * @class JsonHandler
 * @brief Handles JSON data serialization and deserialization.
 */
class JsonHandler {
public:
    /**
     * @brief Convert a graph to JSON.
     * @param graph The graph to convert
     * @return JSON representation
     */
    static nlohmann::json graphToJson(const graph::Graph& graph);
    
    /**
     * @brief Convert JSON to a graph.
     * @param json JSON representation
     * @return Constructed graph
     */
    static graph::Graph jsonToGraph(const nlohmann::json& json);
    
    /**
     * @brief Convert a travel route to JSON.
     * @param route The route to convert
     * @return JSON representation
     */
    static nlohmann::json routeToJson(const travel::TravelRoute& route);
    
    /**
     * @brief Convert JSON to a travel route.
     * @param json JSON representation
     * @return Constructed travel route
     */
    static travel::TravelRoute jsonToRoute(const nlohmann::json& json);
    
    /**
     * @brief Convert an itinerary to JSON.
     * @param itinerary The itinerary to convert
     * @return JSON representation
     */
    static nlohmann::json itineraryToJson(const travel::Itinerary& itinerary);
    
    /**
     * @brief Convert JSON to an itinerary.
     * @param json JSON representation
     * @return Constructed itinerary
     */
    static travel::Itinerary jsonToItinerary(const nlohmann::json& json);
    
    /**
     * @brief Parse a JSON string.
     * @param jsonStr JSON string
     * @return Parsed JSON object
     */
    static nlohmann::json parseJson(const std::string& jsonStr);
    
    /**
     * @brief Serialize JSON to string.
     * @param json JSON object
     * @param pretty Whether to use pretty formatting
     * @return JSON string
     */
    static std::string serializeJson(const nlohmann::json& json, bool pretty = true);
    
    /**
     * @brief Read JSON from a file.
     * @param filePath Path to the JSON file
     * @return Parsed JSON object
     */
    static nlohmann::json readJsonFile(const std::string& filePath);
    
    /**
     * @brief Write JSON to a file.
     * @param json JSON object
     * @param filePath Path to the output file
     * @param pretty Whether to use pretty formatting
     * @return true if successful, false otherwise
     */
    static bool writeJsonFile(const nlohmann::json& json, const std::string& filePath, bool pretty = true);
};

} // namespace data
} // namespace dijkstra