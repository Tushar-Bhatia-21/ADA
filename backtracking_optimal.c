#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

#define MAX_LOCATIONS 20  // Maximum number of delivery locations

// Structure to represent a location with x and y coordinates
struct Location {
    int x, y;
};

// Function to calculate the Euclidean distance between two locations
double calculateDistance(struct Location loc1, struct Location loc2) {
    return sqrt((double)((loc1.x - loc2.x) * (loc1.x - loc2.x) + (loc1.y - loc2.y) * (loc1.y - loc2.y)));
}

// Function to find the optimal delivery route using backtracking
void findOptimalRoute(int n, struct Location locations[MAX_LOCATIONS], int route[MAX_LOCATIONS], bool visited[MAX_LOCATIONS], int currentLocation, double currentDistance, double* minDistance, int* bestRoute, double maxDistance) {
    if (currentDistance > *minDistance) {
        // Pruning: If the current route is longer than the minimum distance found so far, backtrack.
        return;
    }

    if (currentLocation == n) {
        // If all locations are visited, check if this route is better than the current best.
        if (currentDistance < *minDistance) {
            *minDistance = currentDistance;
            for (int i = 0; i < n; i++) {
                bestRoute[i] = route[i];
            }
        }
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            visited[i] = true;
            route[currentLocation] = i;

            double newDistance = currentDistance + (currentLocation == 0 ? calculateDistance(locations[0], locations[i]) : calculateDistance(locations[route[currentLocation - 1]], locations[i]));

            if (newDistance <= maxDistance) {
                findOptimalRoute(n, locations, route, visited, currentLocation + 1, newDistance, minDistance, bestRoute, maxDistance);
            }

            visited[i] = false;
        }
    }
}

int main() {
    int n; // Number of delivery locations (including the depot)
    printf("Enter the number of delivery locations: ");
    scanf("%d", &n);

    struct Location locations[MAX_LOCATIONS];
    int route[MAX_LOCATIONS];  // Stores the current route being explored
    bool visited[MAX_LOCATIONS] = {false};
    double minDistance = INT_MAX;  // Initially set to a large value
    int bestRoute[MAX_LOCATIONS];
    double maxDistance; // Maximum distance constraint

    printf("Enter the coordinates of the depot (x y): ");
    scanf("%d %d", &locations[0].x, &locations[0].y);

    printf("Enter the coordinates of %d delivery locations (x y):\n", n - 1);
    for (int i = 1; i < n; i++) {
        scanf("%d %d", &locations[i].x, &locations[i].y);
    }

    printf("Enter the maximum distance the truck can travel before refueling: ");
    scanf("%lf", &maxDistance);

    findOptimalRoute(n, locations, route, visited, 0, 0.0, &minDistance, bestRoute, maxDistance);

    printf("Optimal Delivery Route:\n");
    printf("Depot -> ");
    for (int i = 0; i < n - 1; i++) {
        printf("Location %d -> ", bestRoute[i] + 1); // Add 1 to convert to 1-based index
    }
    printf("Depot\n");
    printf("Total Distance: %.2lf\n", minDistance);

    return 0;
}
