#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define MAX_LOCATIONS 20

struct Location {
    int x, y;
};

double calculateDistance(struct Location loc1, struct Location loc2) {
    return sqrt((double)((loc1.x - loc2.x) * (loc1.x - loc2.x) + (loc1.y - loc2.y) * (loc1.y - loc2.y)));
}

double findOptimalRouteDP(int n, struct Location locations[], int route[],  float maxDistance) {
    double dp[1 << MAX_LOCATIONS][MAX_LOCATIONS];
    int i, j, k, mask, u, v, currentLocation, nextLocation;
    double distance, minDistance = INT_MAX;

    for (i = 0; i < (1 << n); i++) { // Use (1 << n) as the bitmask size
        for (j = 0; j < n; j++) {
            dp[i][j] = INT_MAX;
        }
    }

    dp[1][0] = 0.0; // Starting from the depot (bitmask 1)

    for (mask = 1; mask < (1 << n); mask++) {
        for (u = 0; u < n; u++) {
            if ((mask & (1 << u)) != 0) {
                for (v = 0; v < n; v++) {
                    if ((mask & (1 << v)) != 0 && u != v) {
                        distance = calculateDistance(locations[u], locations[v]);
                        printf("%lf",distance);
                        if (dp[mask ^ (1 << v)][u] + distance <= maxDistance && dp[mask][u] + distance < dp[mask][v]) {
                            dp[mask][v] = dp[mask ^ (1 << v)][u] + distance;
                        }
                    }
                }
            }
        }
    }

    mask = (1 << n) - 1;
    currentLocation = 0;

    for (i = 1; i < n; i++) {
        distance = calculateDistance(locations[currentLocation], locations[i]);
        if (dp[mask][i] + distance <= maxDistance && dp[mask][i] + distance < minDistance) {
            minDistance = dp[mask][i] + distance;
            route[i] = currentLocation;
        }
    }

    mask ^= (1 << route[n - 1]);
    currentLocation = route[n - 1];

    for (i = n - 2; i >= 1; i--) {
        nextLocation = -1;
        for (j = 0; j < n; j++) {
            if ((mask & (1 << j)) != 0 && (nextLocation == -1 || (dp[mask][j] + calculateDistance(locations[currentLocation], locations[j])) == (dp[mask][nextLocation] + calculateDistance(locations[currentLocation], locations[j])))) {
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
    int n, i;
    struct Location locations[MAX_LOCATIONS];
    int route[MAX_LOCATIONS];
    float maxDistance=0, minDistance=0;

    printf("Enter the number of delivery locations: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_LOCATIONS) {
        printf("Invalid number of locations.\n");
        return 1;
    }

    printf("Enter the coordinates of the depot (x y): ");
    scanf("%d %d", &locations[0].x, &locations[0].y);

    if (locations[0].x < 0 || locations[0].y < 0) {
        printf("Invalid depot coordinates.\n");
        return 1;
    }

    printf("Enter the coordinates of %d delivery locations (x y):\n", n - 1);
  
    for (i = 1; i < n; i++) {
        scanf("%d %d", &locations[i].x, &locations[i].y);
    }
    
    printf("Enter the maximum distance the truck can travel before refueling: ");
    scanf("%f",&maxDistance);
    
    if (maxDistance <= 0) {
        printf("Invalid maximum distance.\n");
        return 1;
    }
    printf("%d",minDistance);
    minDistance = findOptimalRouteDP(n, locations, route, maxDistance);
    
    if (minDistance != INT_MAX) {
        // Successfully found a solution
        printf("Optimal Delivery Route:\n");
        printf("Depot -> ");
        for (i = 1; i < n; i++) {
            printf("Location %d -> ", route[i]);
        }
        printf("Depot\n");
        printf("Total Distance: %lf\n", minDistance);
    } else {
        // No valid route found
        printf("No valid route found within the given constraints.\n");
    }

    return 0;
}