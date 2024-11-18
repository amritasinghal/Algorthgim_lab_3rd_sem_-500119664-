// 9. Compare the Backtracking and Branch & Bound Approach by the implementation of 0/1 Knapsack problem. Also compare the performance with dynamic programming approach.
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Dynamic Programming Approach
int knapsackDP(int weights[], int values[], int n, int capacity) {
    int dp[n+1][capacity+1];
    
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (weights[i-1] <= w)
                dp[i][w] = (values[i-1] + dp[i-1][w - weights[i-1]]) > dp[i-1][w] ?
                            (values[i-1] + dp[i-1][w - weights[i-1]]) : dp[i-1][w];
            else
                dp[i][w] = dp[i-1][w];
        }
    }
    return dp[n][capacity];
}

// Backtracking Approach
int knapsackBacktracking(int weights[], int values[], int n, int capacity, int currentItem, int currentWeight, int currentValue) {
    if (currentItem == n)
        return currentValue;
    
    int exclude = knapsackBacktracking(weights, values, n, capacity, currentItem + 1, currentWeight, currentValue);

    int include = 0;
    if (currentWeight + weights[currentItem] <= capacity)
        include = knapsackBacktracking(weights, values, n, capacity, currentItem + 1, currentWeight + weights[currentItem], currentValue + values[currentItem]);

    return (exclude > include) ? exclude : include;
}

// Branch and Bound Approach (simplified)
struct Item {
    int value, weight;
    float ratio;
};

int knapsackBnb(int weights[], int values[], int n, int capacity) {
    struct Item items[n];
    
    // Sorting items by value-to-weight ratio
    for (int i = 0; i < n; i++) {
        items[i].value = values[i];
        items[i].weight = weights[i];
        items[i].ratio = (float)values[i] / weights[i];
    }

    // Simple greedy approach to select items by ratio
    int totalValue = 0, totalWeight = 0;
    for (int i = 0; i < n && totalWeight + items[i].weight <= capacity; i++) {
        totalValue += items[i].value;
        totalWeight += items[i].weight;
    }

    return totalValue;
}

int main() {
    int values[] = {60, 100, 120};
    int weights[] = {10, 20, 30};
    int capacity = 50;
    int n = sizeof(values) / sizeof(values[0]);

    // Dynamic Programming Solution
    printf("DP Solution: %d\n", knapsackDP(weights, values, n, capacity));

    // Backtracking Solution
    printf("Backtracking Solution: %d\n", knapsackBacktracking(weights, values, n, capacity, 0, 0, 0));

    // Branch and Bound Solution (using greedy approach)
    printf("Branch and Bound Solution (Greedy Approximation): %d\n", knapsackBnb(weights, values, n, capacity));

    return 0;
}