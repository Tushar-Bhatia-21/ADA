#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define MAX_LOCATIONS 100

typedef struct {
    double x, y;
} Point;

Point locations[MAX_LOCATIONS];
int visited[MAX_LOCATIONS];
double best_cost = DBL_MAX;
int best_route[MAX_LOCATIONS];
int n;
double max_distance, fuel_capacity, fuel_consumption;

double euclidean_distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double lower_bound(int current_location, int visited_count, double current_fuel) {
    // Calculate the lower bound based on the minimum distance to the nearest unvisited location.
    double min_distance = DBL_MAX;
    for (int next_location = 0; next_location < n; next_location++) {
        if (!visited[next_location] && next_location != current_location) {
            double distance_to_next = euclidean_distance(locations[current_location], locations[next_location]);
            if (distance_to_next < min_distance) {
                min_distance = distance_to_next;
            }
        }
    }
    return min_distance + (min_distance / fuel_consumption) * fuel_capacity;
}

void branch_and_bound(int current_location, double current_cost, int visited_count, double current_fuel) {
    if (visited_count == n) {
        // All locations visited.
        if (current_cost < best_cost) {
            best_cost = current_cost;
            for (int i = 0; i < n; i++) {
                best_route[i] = visited[i];
            }
        }
        return;
    }

    for (int next_location = 0; next_location < n; next_location++) {
        if (!visited[next_location]) {
            double distance_to_next = euclidean_distance(locations[current_location], locations[next_location]);
            double fuel_needed = distance_to_next / fuel_consumption;

            if (current_fuel - fuel_needed >= 0) {
                visited[next_location] = 1;
                branch_and_bound(next_location, current_cost + distance_to_next, visited_count + 1, current_fuel - fuel_needed + fuel_capacity);
                visited[next_location] = 0;
            }
        }
    }
}

int main() {
    printf("Enter the number of locations: ");
    scanf("%d", &n);

    printf("Enter the maximum distance the truck can travel on a full tank: ");
    scanf("%lf", &max_distance);

    printf("Enter the fuel consumption rate (distance per unit of fuel): ");
    scanf("%lf", &fuel_consumption);

    printf("Enter the fuel capacity of the truck: ");
    scanf("%lf", &fuel_capacity);

    printf("Enter the locations (x y coordinates):\n");
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &locations[i].x, &locations[i].y);
    }

    visited[0] = 1;
    branch_and_bound(0, 0.0, 1, fuel_capacity);

    printf("Optimal Route: Depot");
    for (int i = 0; i < n; i++) {
        printf(" -> %d", i+1);
    }
    printf(" -> Depot\n");
    printf("Optimal Cost: %lf\n", best_cost);

    return 0;
}
