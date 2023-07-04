# Jan_Dil_Virus_Game

# VirusGame Development

## Introduction
This project involves the development of a game called VirusGame using C++ and SDL (Simple DirectMedia Layer) for graphics rendering. The game involves controlling a player object and avoiding viruses that spawn randomly on the screen.

## Project Files

### 1. VirusGame.cpp
Use STL Vector in the code.
Remove the redundancy.

### 7. HandleEvents.h
This header file defines the EventHandler namespace, which provides functions for handling user input events, such as keyboard input and window events.

## Code Refactoring
The initial code provided in the project was refactored to improve readability, maintainability, and performance. Some notable changes include:

- Splitting the main game loop into separate functions to improve code organization.
- Using header files to declare classes, functions, and constants for better modularity.
- Utilizing STL algorithms, such as `std::for_each`, to replace manual for loops for iterating over game objects.
- Parallelizing the loop using OpenMP directives (`#pragma omp parallel for`) to potentially improve performance by leveraging parallel execution.

## Time Complexity Optimization
The time complexity of the game loop largely depends on the number of units (viruses) present in the game. Assuming there are `n` units:

- The manual for loop iteration over the units has a time complexity of O(n), as it iterates over each unit once.

- The `std::for_each` algorithm version also has a time complexity of O(n), as it performs an operation on each unit once.

- The parallelized loop using OpenMP (with `#pragma omp parallel for`) divides the iterations among multiple threads, potentially reducing the overall time taken. The time complexity remains O(n), but the execution time may be reduced due to parallel execution.

## Conclusion
The VirusGame project involved the development of a game using C++ and SDL. The code was refactored to improve organization, readability, and performance. The game loop was split into separate functions, and STL algorithms and OpenMP parallelization were used to enhance the code. The time complexity of the game loop depends on the number of units, with the refactored versions retaining the same time complexity as the original code.

