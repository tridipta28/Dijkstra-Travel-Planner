#pragma once

#include <string>
#include <vector>
#include <memory>
#include "../graph/Graph.hpp"
#include "../graph/PathFinder.hpp"
#include "../travel/TravelRoute.hpp"
#include "../travel/Itinerary.hpp"

namespace dijkstra {
namespace ui {

/**
 * @class CommandLineUI
 * @brief Command-line interface for the Dijkstra Travel Planner.
 */
class CommandLineUI {
public:
    CommandLineUI();
    ~CommandLineUI() = default;
    
    /**
     * @brief Run the main application loop.
     */
    void run();

private:
    graph::Graph graph_;
    std::unique_ptr<graph::PathFinder> pathFinder_;
    
    /**
     * @brief Display the main menu.
     */
    void displayMainMenu();
    
    /**
     * @brief Load sample data into the graph.
     */
    void loadSampleData();
    
    /**
     * @brief Load data from a JSON file.
     */
    void loadDataFromFile();
    
    /**
     * @brief Save current data to a JSON file.
     */
    void saveDataToFile();
    
    /**
     * @brief Find and display the shortest path between two locations.
     */
    void findShortestPath();
    
    /**
     * @brief Create a new travel route.
     */
    void createTravelRoute();
    
    /**
     * @brief Create a new itinerary.
     */
    void createItinerary();
    
    /**
     * @brief Display all available locations.
     */
    void displayLocations();
    
    /**
     * @brief Display graph statistics.
     */
    void displayStatistics();
    
    /**
     * @brief Get user input for optimization mode.
     * @return Selected optimization mode
     */
    graph::PathFinder::OptimizationMode getOptimizationMode();
    
    /**
     * @brief Get user input for transportation mode.
     * @return Selected transportation mode
     */
    travel::TransportMode getTransportMode();
    
    /**
     * @brief Get a string input from the user.
     * @param prompt Prompt to display
     * @return User input string
     */
    std::string getStringInput(const std::string& prompt);
    
    /**
     * @brief Get an integer input from the user.
     * @param prompt Prompt to display
     * @return User input integer
     */
    int getIntInput(const std::string& prompt);
    
    /**
     * @brief Get a double input from the user.
     * @param prompt Prompt to display
     * @return User input double
     */
    double getDoubleInput(const std::string& prompt);
    
    /**
     * @brief Display a separator line.
     */
    void displaySeparator();
    
    /**
     * @brief Pause and wait for user input.
     */
    void pauseForUser();
};

} // namespace ui
} // namespace dijkstra