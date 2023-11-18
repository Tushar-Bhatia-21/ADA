#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <cfloat>
#define MAX_LOCATIONS 20

struct Location {
    int x, y;
};

double calculateDistance(Location loc1, Location loc2) {
    return sqrt(static_cast<double>((loc1.x - loc2.x) * (loc1.x - loc2.x) + (loc1.y - loc2.y) * (loc1.y - loc2.y)));
}

double findOptimalRouteDP(int n, std::vector<Location>& locations, std::vector<int>& route, double maxDistance) {
    std::vector<std::vector<double>> dp(1 << MAX_LOCATIONS, std::vector<double>(MAX_LOCATIONS, DBL_MAX));

    dp[1][0] = 0.0; // Starting from the depot (bitmask 1)

    for (int mask = 1; mask < (1 << n); mask++) {
        for (int u = 0; u < n; u++) {
            if ((mask & (1 << u)) != 0) {
                for (int v = 0; v < n; v++) {
                    if ((mask & (1 << v)) != 0 && u != v) {
                        double distance = calculateDistance(locations[u], locations[v]);
                        if (dp[mask ^ (1 << v)][u] + distance <= maxDistance && dp[mask][u] + distance < dp[mask][v]) {
                            dp[mask][v] = dp[mask][u] + distance;
                        }
                    }
                }
            }
        }
    }

    double minDistance = DBL_MAX;
    int mask = (1 << n) - 1;

    for (int i = 1; i < n; i++) {
        double distance = calculateDistance(locations[0], locations[i]);
        if (dp[mask][i] + distance <= maxDistance && dp[mask][i] + distance < minDistance) {
            minDistance = dp[mask][i] + distance;
            route[i] = 0; // Start from the depot
        }
    }

    if (minDistance == DBL_MAX) {
        return minDistance;
    }

    // Reconstruct the route
    int currentLocation = 0;
    mask ^= (1 << route[n - 1]);

    for (int i = n - 2; i >= 1; i--) {
        int nextLocation = -1;
        for (int j = 1; j < n; j++) {
            if ((mask & (1 << j)) != 0 &&
                (nextLocation == -1 || dp[mask][j] + calculateDistance(locations[currentLocation], locations[j]) == dp[mask][nextLocation] + calculateDistance(locations[currentLocation], locations[nextLocation]))) {
                nextLocation = j;
            }
        }
        route[i] = nextLocation;
        mask ^= (1 << nextLocation);
        currentLocation = nextLocation;
    }

    return minDistance;
}

int main() {
    int n;
    std::cout << "Enter the number of delivery locations: ";
    std::cin >> n;

    if (n <= 0 || n > MAX_LOCATIONS) {
        std::cout << "Invalid number of locations." << std::endl;
        return 1;
    }

    std::vector<Location> locations(n);
    std::vector<int> route(n);
    double maxDistance;

    std::cout << "Enter the coordinates of the depot (x y): ";
    std::cin >> locations[0].x >> locations[0].y;

    if (locations[0].x < 0 || locations[0].y < 0) {
        std::cout << "Invalid depot coordinates." << std::endl;
        return 1;
    }

    std::cout << "Enter the coordinates of " << n - 1 << " delivery locations (x y):" << std::endl;
    for (int i = 1; i < n; i++) {
        std::cin >> locations[i].x >> locations[i].y;
    }

    std::cout << "Enter the maximum distance the truck can travel before refueling: ";
    std::cin >> maxDistance;

    if (maxDistance <= 0) {
        std::cout << "Invalid maximum distance." << std::endl;
        return 1;
    }

    double minDistance = findOptimalRouteDP(n, locations, route, maxDistance);

    if (minDistance != DBL_MAX) {
        // Successfully found a solution
        std::cout << "Optimal Delivery Route:" << std::endl;
        std::cout << "Depot -> ";
        for (int i = 1; i < n; i++) {
            std::cout << "Location " << route[i] << " -> ";
        }
        std::cout << "Depot" << std::endl;
        std::cout << "Total Distance: " << minDistance << std::endl;
    } else {
        // No valid route found
        std::cout << "No valid route found within the given constraints." << std::endl;
    }

    return 0;
}
