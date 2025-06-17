#include "JsonHandler.hpp"
#include <fstream>
#include <stdexcept>

namespace dijkstra {
namespace data {

nlohmann::json JsonHandler::graphToJson(const graph::Graph& graph) {
    nlohmann::json result;
    
    // Serialize nodes
    nlohmann::json nodesArray = nlohmann::json::array();
    for (const auto& node : graph.getAllNodes()) {
        nlohmann::json nodeJson;
        nodeJson["id"] = node->getId();
        nodeJson["name"] = node->getName();
        nodesArray.push_back(nodeJson);
    }
    result["nodes"] = nodesArray;
    
    // Serialize edges
    nlohmann::json edgesArray = nlohmann::json::array();
    for (const auto& edge : graph.getAllEdges()) {
        nlohmann::json edgeJson;
        edgeJson["id"] = edge->getId();
        edgeJson["source"] = edge->getSource()->getId();
        edgeJson["destination"] = edge->getDestination()->getId();
        edgeJson["weight"] = edge->getWeight();
        edgeJson["time_weight"] = edge->getTimeWeight();
        edgeJson["cost_weight"] = edge->getCostWeight();
        edgesArray.push_back(edgeJson);
    }
    result["edges"] = edgesArray;
    
    return result;
}

graph::Graph JsonHandler::jsonToGraph(const nlohmann::json& json) {
    graph::Graph graph;
    
    // Load nodes
    if (json.contains("nodes") && json["nodes"].is_array()) {
        for (const auto& nodeJson : json["nodes"]) {
            auto node = std::make_shared<graph::Node>(
                nodeJson["id"].get<std::string>(),
                nodeJson.value("name", "")
            );
            graph.addNode(node);
        }
    }
    
    // Load edges
    if (json.contains("edges") && json["edges"].is_array()) {
        for (const auto& edgeJson : json["edges"]) {
            auto sourceNode = graph.getNode(edgeJson["source"].get<std::string>());
            auto destNode = graph.getNode(edgeJson["destination"].get<std::string>());
            
            if (sourceNode && destNode) {
                auto edge = std::make_shared<graph::Edge>(
                    edgeJson["id"].get<std::string>(),
                    sourceNode,
                    destNode,
                    edgeJson["weight"].get<double>()
                );
                
                if (edgeJson.contains("time_weight")) {
                    edge->setTimeWeight(edgeJson["time_weight"].get<double>());
                }
                if (edgeJson.contains("cost_weight")) {
                    edge->setCostWeight(edgeJson["cost_weight"].get<double>());
                }
                
                graph.addEdge(edge);
            }
        }
    }
    
    return graph;
}

nlohmann::json JsonHandler::routeToJson(const travel::TravelRoute& route) {
    nlohmann::json result;
    
    result["route_id"] = route.getRouteId();
    result["description"] = route.getDescription();
    result["total_distance"] = route.getTotalDistance();
    result["total_time"] = route.getTotalTime();
    result["total_cost"] = route.getTotalCost();
    
    // Serialize segments
    nlohmann::json segmentsArray = nlohmann::json::array();
    for (const auto& segment : route.getSegments()) {
        nlohmann::json segmentJson;
        segmentJson["from_location"] = segment->getFromLocation();
        segmentJson["to_location"] = segment->getToLocation();
        segmentJson["from_coordinate"] = {
            {"latitude", segment->getFromCoordinate().getLatitude()},
            {"longitude", segment->getFromCoordinate().getLongitude()}
        };
        segmentJson["to_coordinate"] = {
            {"latitude", segment->getToCoordinate().getLatitude()},
            {"longitude", segment->getToCoordinate().getLongitude()}
        };
        segmentJson["transport_mode"] = travel::TransportFactory::transportModeToString(
            segment->getTransport()->getMode());
        segmentJson["distance"] = segment->getDistance();
        segmentJson["travel_time"] = segment->getTravelTime();
        segmentJson["cost"] = segment->getCost();
        segmentJson["notes"] = segment->getNotes();
        
        segmentsArray.push_back(segmentJson);
    }
    result["segments"] = segmentsArray;
    
    return result;
}

travel::TravelRoute JsonHandler::jsonToRoute(const nlohmann::json& json) {
    travel::TravelRoute route(json.value("route_id", ""));
    route.setDescription(json.value("description", ""));
    
    if (json.contains("segments") && json["segments"].is_array()) {
        for (const auto& segmentJson : json["segments"]) {
            geo::GeoCoordinate fromCoord(
                segmentJson["from_coordinate"]["latitude"].get<double>(),
                segmentJson["from_coordinate"]["longitude"].get<double>()
            );
            geo::GeoCoordinate toCoord(
                segmentJson["to_coordinate"]["latitude"].get<double>(),
                segmentJson["to_coordinate"]["longitude"].get<double>()
            );
            
            auto transportMode = travel::TransportFactory::stringToTransportMode(
                segmentJson["transport_mode"].get<std::string>());
            auto transport = travel::TransportFactory::createTransport(transportMode);
            
            auto segment = std::make_shared<travel::RouteSegment>(
                segmentJson["from_location"].get<std::string>(),
                segmentJson["to_location"].get<std::string>(),
                fromCoord,
                toCoord,
                transport
            );
            
            if (segmentJson.contains("notes")) {
                segment->setNotes(segmentJson["notes"].get<std::string>());
            }
            
            route.addSegment(segment);
        }
    }
    
    return route;
}

nlohmann::json JsonHandler::parseJson(const std::string& jsonStr) {
    try {
        return nlohmann::json::parse(jsonStr);
    } catch (const nlohmann::json::parse_error& e) {
        throw std::runtime_error("Failed to parse JSON: " + std::string(e.what()));
    }
}

std::string JsonHandler::serializeJson(const nlohmann::json& json, bool pretty) {
    return pretty ? json.dump(4) : json.dump();
}

nlohmann::json JsonHandler::readJsonFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filePath);
    }
    
    nlohmann::json json;
    try {
        file >> json;
    } catch (const nlohmann::json::parse_error& e) {
        throw std::runtime_error("Failed to parse JSON file " + filePath + ": " + std::string(e.what()));
    }
    
    return json;
}

bool JsonHandler::writeJsonFile(const nlohmann::json& json, const std::string& filePath, bool pretty) {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        return false;
    }
    
    try {
        file << (pretty ? json.dump(4) : json.dump());
        return true;
    } catch (const std::exception&) {
        return false;
    }
}

} // namespace data
} // namespace dijkstra