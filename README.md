# Dijkstra Travel Planner - Project Structure

## Overview
This project implements an advanced travel planning system using Dijkstra's algorithm for optimal route finding. The system supports multiple types of transportation, various constraints, and provides comprehensive travel itineraries.

## Key Features
- Multi-criteria path optimization
- Support for different transportation modes
- GPS coordinate handling and mapping
- Custom route constraints (time, budget, preferences)
- Advanced user interface for travel planning
- JSON import/export for travel data
- Detailed itinerary generation

## Project Architecture
The project follows a modular design with the following components:

### Core Components
1. **Graph System**: Implementation of directed weighted graph and Dijkstra's algorithm
2. **GeoCoordinate System**: Handling of geographic coordinates and distances
3. **Transportation System**: Models for different transportation modes
4. **Route Planning**: Advanced path-finding with multiple constraints
5. **Data Management**: JSON-based data storage and retrieval
6. **User Interface**: Command-line interface for interaction

### File Structure
```
├── include/                     # Header files
│   ├── graph/                   # Graph implementation
│   │   ├── Graph.hpp            # Graph data structure
│   │   ├── Node.hpp             # Node representation
│   │   ├── Edge.hpp             # Edge representation
│   │   └── PathFinder.hpp       # Dijkstra algorithm implementation
│   ├── geo/                     # Geographic data handling
│   │   ├── GeoCoordinate.hpp    # GPS coordinate representation
│   │   ├── Distance.hpp         # Distance calculation utilities
│   │   └── LocationManager.hpp  # Location management
│   ├── travel/                  # Travel-specific components
│   │   ├── Transport.hpp        # Transportation mode base class
│   │   ├── TravelRoute.hpp      # Route representation
│   │   ├── Itinerary.hpp        # Travel itinerary
│   │   └── TravelConstraints.hpp # Constraints for travel
│   ├── data/                    # Data management
│   │   ├── DataManager.hpp      # Data import/export
│   │   ├── JsonHandler.hpp      # JSON processing
│   │   └── FileIO.hpp           # File operations
│   └── ui/                      # User interface
│       ├── CommandLineUI.hpp    # Command-line interface
│       └── UIManager.hpp        # UI management
├── src/                         # Implementation files
│   ├── graph/                   # Graph implementation
│   ├── geo/                     # Geographic data handling
│   ├── travel/                  # Travel-specific components
│   ├── data/                    # Data management
│   ├── ui/                      # User interface
│   └── main.cpp                 # Main application entry point
├── data/                        # Sample data files
│   ├── locations.json           # Sample location data
│   ├── transportation.json      # Sample transportation data
│   └── sample_routes.json       # Sample routes
├── tests/                       # Unit tests
├── CMakeLists.txt               # CMake build configuration
└── README.md                    # Project documentation
```

## Building and Running
The project uses CMake for build management. To build the project:

```bash
mkdir build
cd build
cmake ..
make
```

To run the application:
```bash
./dijkstra_travel_planner
```

## Dependencies
- C++17 or higher
- nlohmann/json library for JSON processing
- CMake 3.15 or higher for building