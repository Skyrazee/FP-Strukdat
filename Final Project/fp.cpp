#include <iostream>
#include <list>
#include <vector>
#include <string>

using namespace std;

class MapElement {
public:
    virtual ~MapElement() {}

    virtual void display() const = 0;
};

class Location {
public:
    Location(int id, const string& name, int x, int y) : id(id), name(name), x(x), y(y) {}

    int getID() const {
        return id;
    }

    const string& getName() const {
        return name;
    }

private:
    int id;
    string name;
    int x;
    int y;
};

class MapNode : public MapElement {
public:
    MapNode(const Location& loc) : location(loc) {}

    void display() const override {
        cout << "Node: " << location.getName() << " (" << location.getID() << ")" << endl;
    }

private:
    Location location;
};

class MapEdge : public MapElement {
public:
    MapEdge(int sourceID, int destinationID) : sourceID(sourceID), destinationID(destinationID) {}

    void display() const override {
        cout << "Edge: " << sourceID << " -> " << destinationID << endl;
    }

private:
    int sourceID;
    int destinationID;
};

class Map {
public:
    Map(int numberOfLocations) {
        initializeAdjMatrix(numberOfLocations);
    }

    ~Map() {
        for (int i = 0; i < numberOfLocations; ++i) {
            delete[] adjacencyMatrix[i];
        }
        delete[] adjacencyMatrix;

        for (auto& elem : mapElements) {
            delete elem;
        }
    }

    void addLocation(const Location& location) {
        locations.push_back(location);
        mapElements.push_back(new MapNode(location));
    }

    void addEdge(int sourceID, int destinationID) {
        adjacencyMatrix[sourceID][destinationID] = 1;
        adjacencyMatrix[destinationID][sourceID] = 1;
        mapElements.push_back(new MapEdge(sourceID, destinationID));
    }

    void displayMap() const {
        for (const auto& element : mapElements) {
            element->display();
        }
    }

private:
    void initializeAdjMatrix(int numberOfLocations) {
        this->numberOfLocations = numberOfLocations;
        adjacencyMatrix = new int*[numberOfLocations];
        for (int i = 0; i < numberOfLocations; ++i) {
            adjacencyMatrix[i] = new int[numberOfLocations];
            for (int j = 0; j < numberOfLocations; ++j) {
                adjacencyMatrix[i][j] = 0;
            }
        }
    }

    int numberOfLocations;
    int** adjacencyMatrix;
    vector<Location> locations;
    vector<MapElement*> mapElements;
};

int main() {
    int numLocations;
    cout << "Enter the number of locations: ";
    cin >> numLocations;

    Map myMap(numLocations);

    // Input locations
    for (int i = 0; i < numLocations; ++i) {
        int id, x, y;
        string name;
        cout << "Enter details for location " << i << ":" << endl;
        cout << "ID: ";
        cin >> id;
        cout << "Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "X Coordinate: ";
        cin >> x;
        cout << "Y Coordinate: ";
        cin >> y;

        Location location(id, name, x, y);
        myMap.addLocation(location);
    }

    // Input connections/edges
    int numEdges;
    cout << "Enter the number of connections: ";
    cin >> numEdges;

    for (int i = 0; i < numEdges; ++i) {
        int sourceID, destinationID;
        cout << "Enter connection " << i << " (sourceID -> destinationID): ";
        cin >> sourceID >> destinationID;
        myMap.addEdge(sourceID, destinationID);
    }

    cout << endl;
    cout << "Map Elements" << endl;
    myMap.displayMap();

    return 0;
}