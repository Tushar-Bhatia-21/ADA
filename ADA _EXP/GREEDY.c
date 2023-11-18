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

// Function to find the nearest unvisited location from the current location
int findNearestUnvisited(int n, struct Location locations[MAX_LOCATIONS], bool visited[MAX_LOCATIONS], int currentLocation) {
    int nearest = -1;
    double minDistance = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (!visited[i] && i != currentLocation) {
            double distance = calculateDistance(locations[currentLocation], locations[i]);
            if (distance < minDistance) {
                minDistance = distance;
                nearest = i;
            }
        }
    }

    return nearest;
}

// Function to find the optimal delivery route using a greedy approach with a fuel constraint
void findOptimalRoute(int n, struct Location locations[MAX_LOCATIONS], int route[MAX_LOCATIONS], double* minDistance, double maxDistance) {
    bool visited[MAX_LOCATIONS] = {false};
    int currentLocation = 0;  // Start from the depot
    visited[currentLocation] = true;
    route[0] = currentLocation;

    double currentFuel = maxDistance;
    int numLocationsVisited = 1;

    while (numLocationsVisited < n) {
        int nearest = findNearestUnvisited(n, locations, visited, currentLocation);

        if (nearest == -1) {
            // If no unvisited locations remain, check if there's enough fuel to return to the depot
            double distanceToDepot = calculateDistance(locations[currentLocation], locations[0]);
            if (distanceToDepot > currentFuel) {
                // Print a message indicating that it's not possible to return to the depot
                printf("Unable to return to the depot due to insufficient fuel. Fuel remaining: %.2lf\n", currentFuel);
                return;
            }
            *minDistance += distanceToDepot;
            currentLocation = 0;
            currentFuel = maxDistance;
        } else {
            double distance = calculateDistance(locations[currentLocation], locations[nearest]);

            if (distance > currentFuel) {
                // If the distance to the nearest location exceeds the remaining fuel, return to the depot
                *minDistance += calculateDistance(locations[currentLocation], locations[0]);
                currentLocation = 0;
                currentFuel = maxDistance;
            } else {
                visited[nearest] = true;
                route[numLocationsVisited] = nearest;
                *minDistance += distance;
                currentLocation = nearest;
                currentFuel -= distance;
                numLocationsVisited++;
            }
        }
    }

    // After visiting all locations, check if there's enough fuel to return to the depot
    double distanceToDepot = calculateDistance(locations[currentLocation], locations[0]);
    if (distanceToDepot > currentFuel) {
        // Print a message indicating that it's not possible to return to the depot
        printf("Unable to return to the depot due to insufficient fuel. Fuel remaining: %.2lf\n", currentFuel);
    } else {
        // Return to the depot and update the total distance
        *minDistance += distanceToDepot;
        currentLocation = 0;
    }
}

int main() {
    int flg=0;
    int n; // Number of delivery locations (including the depot)
    printf("Enter the number of delivery locations: ");
    scanf("%d", &n);

    struct Location locations[MAX_LOCATIONS];
    int route[MAX_LOCATIONS];  // Stores the current route
    double minDistance = 0.0;  // Initially set to 0
    double maxDistance; // Maximum distance constraint

    printf("Enter the coordinates of the depot (x y): ");
    scanf("%d %d", &locations[0].x, &locations[0].y);

    printf("Enter the coordinates of %d delivery locations (x y):\n", n - 1);
    for (int i = 1; i < n; i++) {
        scanf("%d %d", &locations[i].x, &locations[i].y);
    }

    printf("Enter the maximum distance the truck can travel before refueling: ");
    scanf("%lf", &maxDistance);
    if(maxDistance <= 0) {
        printf("Invalid maximum distance.\n");
        return 0;
    }
    if(n <= 0) {
        printf("Invalid number of locations.\n");
        return 0;
    }
    if(locations[0].x < 0 || locations[0].y < 0) {
        printf("Invalid depot coordinates.\n");
        return 0;
    }
    for(int i=0;i<n;i++)
    {
        if(maxDistance<locations[i].x || maxDistance<locations[i].y)
        {
            printf("Maximum distance is insufficient");
            exit(0);
        }
    }

    findOptimalRoute(n, locations, route, &minDistance, maxDistance);

    if (route[0] == 0) 
    {   if(flg==0)
        {
        printf("Optimal Delivery Route:\n");
        printf("Depot -> ");
        for (int i = 0; i < n-1; i++) {
            printf("Location %d -> ", route[i] + 1); // Add 1 to convert to 1-based index
        }
        printf("Depot\n");
        printf("Total Distance: %.2lf\n", minDistance);
        flg=1;
        }
        // Successfully returned to the depot
    }
    
    else
    {
        printf("Unable to return to the depot due to insufficient fuel. Fuel remaining: %.2lf\n", maxDistance);
        
    }

    return 0;
}