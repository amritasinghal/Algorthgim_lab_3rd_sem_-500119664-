#include <stdio.h>

typedef struct {
    int start;
    int finish;
    int index; // Store the original activity index
} Activity;

// Function to merge two halves
void merge(Activity arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    Activity L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2) {
        if (L[i].finish <= R[j].finish) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Function to implement Merge Sort
void mergeSort(Activity arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}


void activitySelection(Activity activities[], int n) {
    
    mergeSort(activities, 0, n - 1);

    printf("Selected Activities:\n");

    
    int i = 0;
    printf("Activity %d (Start: %d, Finish: %d)\n", activities[i].index + 1, activities[i].start, activities[i].finish);

    
    for (int j = 1; j < n; j++) {

        if (activities[j].start >= activities[i].finish) {
            printf("Activity %d (Start: %d, Finish: %d)\n", activities[j].index + 1, activities[j].start, activities[j].finish);
            i = j; 
        }
    }
}

int main() {
    Activity activities[] = {
        {5, 9}, {1, 2}, {3, 4}, {0, 6}, {5, 7}, {8, 9}
    };
    int n = sizeof(activities) / sizeof(activities[0]);

    
    for (int i = 0; i < n; i++) {
        activities[i].index = i; 

    activitySelection(activities, n);

    return 0;
}
}