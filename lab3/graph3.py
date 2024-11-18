# -*- coding: utf-8 -*-
"""graph1.ipynb

Automatically generated by Colab.

Original file is located at
    https://colab.research.google.com/drive/15JoJ0grf5a-rjuJ4SfD34DgwspxFcZJz
"""

import matplotlib.pyplot as plt

# Example data collected from the C program
matrix_sizes = [64, 128, 256, 512, 1024]
traditional_times = [0.004, 0.016, 0.062, 0.253, 1.025]  # Replace with your collected data
strassen_times = [0.002, 0.008, 0.031, 0.123, 0.497]      # Replace with your collected data

# Plotting the graph
plt.plot(matrix_sizes, traditional_times, marker='o', label='Traditional Multiply', color='b')
plt.plot(matrix_sizes, strassen_times, marker='o', label="Strassen's Multiply", color='r')

# Adding labels and title
plt.xlabel('Matrix Size (n x n)')
plt.ylabel('Execution Time (seconds)')
plt.title('Execution Time: Traditional vs Strassen Matrix Multiplication')

# Adding a legend
plt.legend()

# Adding grid for clarity
plt.grid(True)

# Display the plot
plt.show()