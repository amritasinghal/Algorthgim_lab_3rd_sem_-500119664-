#include <stdio.h>
#include <stdlib.h>  
#include <time.h>
 
// Function to generate a sorted random array
void generate_sorted_array(int arr[], int n) {
   for (int i = 0; i < n; i++) {
       arr[i] = rand() % 1000;
   }
 
   // Sort the array  
   for (int i = 0; i < n - 1; i++) {
       for (int j = 0; j < n - i - 1; j++) {
           if (arr[j] > arr[j + 1]) {
               int temp = arr[j];
               arr[j] = arr[j + 1];
               arr[j + 1] = temp;
           }
       }
   }
}
 
// Function to perform binary search
int binary_search(int arr[], int low, int high, int value) {
   if (low > high) {
       return -1;
   }
 
   int mid = (low + high) / 2;
 
   if (arr[mid] == value) {  
       return mid;
   }
   else if (arr[mid] > value) {  
       return binary_search(arr, low, mid - 1, value);
   }
   else {  
       return binary_search(arr, mid + 1, high, value);
   }
}
 
int main() {
   srand(time(NULL));
 
   int n;
   printf("Enter the size of the array: ");
   scanf("%d", &n);
 
   int arr[n];
   generate_sorted_array(arr, n);
 
   int value;
   printf("Enter the value to search: ");
   scanf("%d", &value);
   //Start time
   clock_t start_time = clock();
   int result = binary_search(arr, 0, n - 1, value);
   // End timing
   clock_t end_time = clock();
   if (result != -1) {
       printf("Value %d found at index %d.\n", value, result);
   } else {
       printf("Value %d not found.\n", value);
   }
   
   // Calculate the time
   double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
   printf("Execution time: %f seconds\n", time_taken);
   return 0;
}