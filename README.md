# ✈️ FlightSearch

> A C++ flight route search engine that models cities and flights as a graph — find your way from A to B, fast.

## Overview

FlightSearch takes a network of cities and flight connections and lets you query routes between them — think of it as a mini flight-booking search engine running under the hood. Cities and flights are loaded from data files, structured into a graph, and traversed to answer real search requests.

Built as a project, this was a chance to get hands-on with graph representations, custom data types, and file-driven program design in C++.

## ✨ Features

- 🌍 **City & flight modeling** — cities and routes are loaded from structured `.dat` files and represented as a graph
- 🔍 **Route search** — find valid paths between cities based on real flight connections
- 📄 **Request-driven queries** — batch search requests read from `requests.dat` for repeatable testing
- 🧩 **Custom type system** — dedicated `type.h` / `type.cpp` define the core data structures used throughout
- ⚙️ **Clean modular structure** — logic split across `flightMap`, `type`, and `main` for readability and easy extension

## 🗂️ Project Structure
FlightSearch/
─ main.cpp # Program entry point
─ flightMap.h/.cpp # Graph structure — cities, flights, and search logic
─ type.h/.cpp # Custom data types used across the project
─ cities.dat # City data
─ flights.dat # Flight connection data
─ requests.dat # Sample search requests
─ flight # Compiled executable

## 🛠️ Built With

- **C++**
- Custom graph data structures (no external libraries)

## 🚀 Getting Started

### Prerequisites
- A C++ compiler (g++ or similar)

### Build

```bash
g++ -o flight main.cpp flightMap.cpp type.cpp
```

### Run

```bash
./flight
```

The program reads from `cities.dat`, `flights.dat`, and `requests.dat` to process flight search queries.

## 📌 Notes

- Modeled an airline network graph using an Adjacency List to parse and map scheduled flight databases
- Developed a backtracking Depth-First Search (DFS) algorithm to dynamically generate valid, cycle-free multi-city travel itineraries and calculate total costs
- Utilized modern C++ features — including lambdas, operator overloading, and deep copies — to decouple data management

## 👤 Author

**Arun Baraili**
