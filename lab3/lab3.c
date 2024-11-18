#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to allocate matrix
int** allocate_matrix(int size) {
    int** mat = (int**)malloc(size * sizeof(int*));  // Corrected memory allocation for row pointers
    for (int i = 0; i < size; i++) {
        mat[i] = (int*)malloc(size * sizeof(int));   // Allocate memory for each row
    }
    return mat;
}

// Function to free matrix
void free_matrix(int** mat, int size) {
    for (int i = 0; i < size; i++) {
        free(mat[i]);
    }
    free(mat);
}

// Function to fill matrix with random values
void fill_matrix(int** mat, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            mat[i][j] = rand() % 10;
        }
    }
}

// Traditional matrix multiplication (In-place for result)
void traditional_multiply(int** A, int** B, int** C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = 0;
            for (int k = 0; k < size; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Strassen's matrix multiplication (Recursive)
void strassen_multiply(int** A, int** B, int** C, int size) {
    if (size == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int halfSize = size / 2;

    // Allocate memory for submatrices (We reuse the same memory for all submatrices to minimize space)
    int** temp1 = allocate_matrix(halfSize);
    int** temp2 = allocate_matrix(halfSize);

    // Reuse parts of matrices A and B for submatrices
    int** A11 = A;
    int** A12 = A;
    int** A21 = A + halfSize;
    int** A22 = A + halfSize;

    int** B11 = B;
    int** B12 = B;
    int** B21 = B + halfSize;
    int** B22 = B + halfSize;

    // Reuse parts of matrix C for result submatrices
    int** C11 = C;
    int** C12 = C;
    int** C21 = C + halfSize;
    int** C22 = C + halfSize;

    // M1 = (A11 + A22) * (B11 + B22)
    for (int i = 0; i < halfSize; i++) {
        for (int j = 0; j < halfSize; j++) {
            temp1[i][j] = A11[i][j] + A22[i][j];
            temp2[i][j] = B11[i][j] + B22[i][j];
        }
    }
    strassen_multiply(temp1, temp2, C11, halfSize);

    // M2 = (A21 + A22) * B11
    for (int i = 0; i < halfSize; i++) {
        for (int j = 0; j < halfSize; j++) {
            temp1[i][j] = A21[i][j] + A22[i][j];
        }
    }
    strassen_multiply(temp1, B11, C21, halfSize);

    // M3 = A11 * (B12 - B22)
    for (int i = 0; i < halfSize; i++) {
        for (int j = 0; j < halfSize; j++) {
            temp1[i][j] = B12[i][j] - B22[i][j];
        }
    }
    strassen_multiply(A11, temp1, C12, halfSize);

    // M4 = A22 * (B21 - B11)
    for (int i = 0; i < halfSize; i++) {
        for (int j = 0; j < halfSize; j++) {
            temp1[i][j] = B21[i][j] - B11[i][j];
        }
    }
    strassen_multiply(A22, temp1, C22, halfSize);

    // M5 = (A11 + A12) * B22
    for (int i = 0; i < halfSize; i++) {
        for (int j = 0; j < halfSize; j++) {
            temp1[i][j] = A11[i][j] + A12[i][j];
        }
    }
    strassen_multiply(temp1, B22, C12, halfSize);

    // M6 = (A21 - A11) * (B11 + B12)
    for (int i = 0; i < halfSize; i++) {
        for (int j = 0; j < halfSize; j++) {
            temp1[i][j] = A21[i][j] - A11[i][j];
            temp2[i][j] = B11[i][j] + B12[i][j];
        }
    }
    strassen_multiply(temp1, temp2, C21, halfSize);

    // M7 = (A12 - A22) * (B21 + B22)
    for (int i = 0; i < halfSize; i++) {
        for (int j = 0; j < halfSize; j++) {
            temp1[i][j] = A12[i][j] - A22[i][j];
            temp2[i][j] = B21[i][j] + B22[i][j];
        }
    }
    strassen_multiply(temp1, temp2, C11, halfSize);

    // Free temporary matrices
    free_matrix(temp1, halfSize);
    free_matrix(temp2, halfSize);
}

// Timing helper function
#ifdef _WIN32
#include <windows.h>
double get_time() {
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
    return (double)start.QuadPart / frequency.QuadPart;
}
#else
double get_time() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec * 1e-9;
}
#endif

// Main function
int main() {
    int size;

    printf("Enter the size of the square matrix: ");
    scanf("%d", &size);

    srand(time(NULL));

    printf("Matrix size: %d x %d\n", size, size);

    int** A = allocate_matrix(size);
    int** B = allocate_matrix(size);
    int** C = allocate_matrix(size);

    fill_matrix(A, size);
    fill_matrix(B, size);

    double start, end;

    // Traditional Multiplication
    start = get_time();
    traditional_multiply(A, B, C, size);
    end = get_time();
    printf("Traditional Multiply: %f seconds\n", end - start);

    // Strassen's Multiplication
    start = get_time();
    strassen_multiply(A, B, C, size);
    end = get_time();
    printf("Strassen Multiply: %f seconds\n", end - start);

    // Free allocated memory
    free_matrix(A, size);
    free_matrix(B, size);
    free_matrix(C, size);

    return 0;
}
