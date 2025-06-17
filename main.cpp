#include <iostream>
#include <memory>
#include <vector>
#include <string>

// Include all necessary headers
#include "graph/Graph.hpp"
#include "graph/PathFinder.hpp"
#include "geo/GeoCoordinate.hpp"
#include "travel/Transport.hpp"
#include "travel/TravelRoute.hpp"
#include "travel/Itinerary.hpp"
#include "data/JsonHandler.hpp"

using namespace dijkstra;

/**
 * @brief Demonstrates the basic functionality of the Dijkstra Travel Planner.
 */
class TravelPlannerDemo {
public:
    void run() {
        std::cout << "=== Dijkstra Travel Planner Demo ===" << std::endl;
        
        // Create sample locations with coordinates
        setupSampleData();
        
        // Demonstrate path finding
        demonstratePathFinding();
        
        // Demonstrate route planning
        demonstrateRouteCreation();
        
        // Demonstrate itinerary generation
        demonstrateItineraryCreation();
        
        std::cout << "\n=== Demo Complete ===" << std::endl;
    }

private:
    graph::Graph graph_;
    
    void setupSampleData() {
        std::cout << "\n--- Setting up sample data ---" << std::endl;
        
        // Create nodes for major cities
        auto newYork = std::make_shared<graph::Node>("NYC", "New York City");
        auto boston = std::make_shared<graph::Node>("BOS", "Boston");
        auto philadelphia = std::make_shared<graph::Node>("PHL", "Philadelphia");
        auto washington = std::make_shared<graph::Node>("DC", "Washington DC");
        
        // Add nodes to graph
        graph_.addNode(newYork);
        graph_.addNode(boston);
        graph_.addNode(philadelphia);
        graph_.addNode(washington);
        
        // Create edges with distances
        auto edge1 = std::make_shared<graph::Edge>("NYC-BOS", newYork, boston, 306.0);
        edge1->setTimeWeight(4.5);  // 4.5 hours by car
        edge1->setCostWeight(50.0); // $50 travel cost
        
        auto edge2 = std::make_shared<graph::Edge>("NYC-PHL", newYork, philadelphia, 153.0);
        edge2->setTimeWeight(2.0);
        edge2->setCostWeight(25.0);
        
        auto edge3 = std::make_shared<graph::Edge>("PHL-DC", philadelphia, washington, 225.0);
        edge3->setTimeWeight(3.0);
        edge3->setCostWeight(35.0);
        
        auto edge4 = std::make_shared<graph::Edge>("BOS-NYC", boston, newYork, 306.0);
        edge4->setTimeWeight(4.5);
        edge4->setCostWeight(50.0);
        
        // Add edges to graph
        graph_.addEdge(edge1);
        graph_.addEdge(edge2);
        graph_.addEdge(edge3);
        graph_.addEdge(edge4);
        
        std::cout << "Created graph with " << graph_.getNodeCount() 
                  << " nodes and " << graph_.getEdgeCount() << " edges" << std::endl;
    }
    
    void demonstratePathFinding() {
        std::cout << "\n--- Demonstrating path finding ---" << std::endl;
        
        graph::PathFinder pathFinder(graph_);
        
        // Find shortest path from NYC to DC
        auto result = pathFinder.findShortestPath("NYC", "DC", 
                                                 graph::PathFinder::OptimizationMode::DISTANCE);
        
        if (result.isFound()) {
            std::cout << "Shortest path from NYC to DC:" << std::endl;
            const auto& path = result.getPath();
            for (size_t i = 0; i < path.size(); ++i) {
                std::cout << "  " << path[i];
                if (i < path.size() - 1) std::cout << " -> ";
            }
            std::cout << std::endl;
            std::cout << "Total distance: " << result.getTotalDistance() << " km" << std::endl;
            std::cout << "Total time: " << result.getTotalTime() << " hours" << std::endl;
            std::cout << "Total cost: $" << result.getTotalCost() << std::endl;
        } else {
            std::cout << "No path found from NYC to DC" << std::endl;
        }
    }
    
    void demonstrateRouteCreation() {
        std::cout << "\n--- Demonstrating route creation ---" << std::endl;
        
        // Create coordinates for cities
        geo::GeoCoordinate nycCoord(40.7128, -74.0060);
        geo::GeoCoordinate phillyCoord(39.9526, -75.1652);
        
        // Create transport mode
        auto drivingTransport = travel::TransportFactory::createTransport(
            travel::TransportMode::DRIVING);
        
        // Create a route segment
        auto segment = std::make_shared<travel::RouteSegment>(
            "New York City", "Philadelphia",
            nycCoord, phillyCoord,
            drivingTransport
        );
        
        // Create a travel route
        travel::TravelRoute route("NYC-PHL-Route");
        route.setDescription("Drive from NYC to Philadelphia");
        route.addSegment(segment);
        
        std::cout << "Created route: " << route.getDescription() << std::endl;
        std::cout << "Distance: " << route.getTotalDistance() << " km" << std::endl;
        std::cout << "Time: " << route.getTotalTime() << " hours" << std::endl;
        std::cout << "Cost: $" << route.getTotalCost() << std::endl;
    }
    
    void demonstrateItineraryCreation() {
        std::cout << "\n--- Demonstrating itinerary creation ---" << std::endl;
        
        travel::Itinerary itinerary("East Coast Trip");
        itinerary.setDescription("A wonderful trip through the East Coast");
        
        // Add some activities
        auto hotel = std::make_shared<travel::ItineraryItem>(
            travel::ItineraryItem::ItemType::ACCOMMODATION,
            "Hotel Stay in NYC",
            "Luxury hotel in Manhattan"
        );
        hotel->setDuration(24.0);  // 1 day
        hotel->setCost(200.0);     // $200
        hotel->setLocation("New York City");
        
        auto activity = std::make_shared<travel::ItineraryItem>(
            travel::ItineraryItem::ItemType::ACTIVITY,
            "Visit Statue of Liberty",
            "Ferry ride and tour of the famous statue"
        );
        activity->setDuration(4.0);   // 4 hours
        activity->setCost(50.0);      // $50
        activity->setLocation("New York City");
        
        itinerary.addItem(hotel);
        itinerary.addItem(activity);
        
        std::cout << "Created itinerary: " << itinerary.getTitle() << std::endl;
        std::cout << "Total duration: " << itinerary.getTotalDuration() << " hours" << std::endl;
        std::cout << "Total cost: $" << itinerary.getTotalCost() << std::endl;
        std::cout << "Number of items: " << itinerary.getItemCount() << std::endl;
    }
};

int main() {
    try {
        TravelPlannerDemo demo;
        demo.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}