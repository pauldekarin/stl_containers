# s21_containers

## Overview
`s21_containers` is a custom implementation of standard container classes in C++17, developed as part of the School 21 curriculum. The project includes the implementation of various containers, following the principles of the Standard Template Library (STL).

## Features
- Developed in C++17
- Implements list, map, queue, set, stack, and vector
- Includes iterators for container traversal
- Templates for generic programming
- Comprehensive unit tests using GTest
- Adheres to the Google C++ Style Guide

## Containers
The following containers are implemented:

- `s21::list`: Doubly linked list
- `s21::map`: Associative container storing key-value pairs
- `s21::queue`: FIFO data structure
- `s21::set`: Associative container storing unique elements
- `s21::stack`: LIFO data structure
- `s21::vector`: Dynamic array

## Installation
1. Clone the repository:
    ```sh
    git clone https://github.com/pauldekarin/stl_containers.git
    ```
   
2. Navigate to the project directory:
    ```sh
    cd s21_containers
    ```

3. Build the project using Makefile:
    ```sh
    make
    ```

## Usage
To test the library, use the provided Makefile:
  ```sh
  make test
  ```
Clean the build files:

sh
make clean
## Bonus Implementations
Additional containers and methods:

`s21::array`: Fixed-size array

`s21::multiset`: Associative container allowing duplicate elements

## Additional Methods
`insert_many(pos, Args&&... args)`: Inserts multiple elements at the specified position (for list, vector).

`insert_many_back(Args&&... args)`: Appends multiple elements to the end (for list, vector, queue, stack).

`insert_many_front(Args&&... args)`: Inserts multiple elements at the front (for list).

# Requirements
GCC compiler
CMake (optional for advanced configuration)
Google Test framework for unit tests

# License
This project is licensed under the MIT License - see the LICENSE file for details.


