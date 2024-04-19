# NumPy++ Array Class
This is an implementation of a NumPy-like array class called NumpyArray in C++. It provides various functionalities for creating, manipulating, and performing operations on multi-dimensional arrays.

## Features
Create arrays with specified dimensions or from existing data
Access and modify array elements using overloaded operator()
Reshape and resize arrays
Concatenate arrays along specified axes or vertically/horizontally stack them
Split arrays into multiple arrays along a specified axis
Flip, roll, transpose, and swap axes of arrays
Remove singleton dimensions from arrays

## Files
### numpy++.hpp
This header file contains the declaration of the NumpyArray class. It includes the necessary headers (vector, iostream, and algorithm) and defines the class with the following members:


data3D: A vector of vectors of vectors to store the array data
rows: Number of rows
cols: Number of columns
depth: Number of dimensions
Public members:

Constructors
Overloaded operator() for accessing and modifying array elements
shape() function to get the number of rows or columns
reshape() and resize() functions to change the shape and size of the array
Various utility functions like concatenate(), vstack(), hstack(), split(), flip(), roll(), transpose(), swapaxes(), squeeze(), and an overloaded operator<< for printing the array

### numpy++.cpp
This file contains the implementation of the member functions declared in the numpy++.hpp header file. It includes the definitions of the constructors, operator() functions, shape() function, reshape() and resize() functions, and various other utility functions like concatenate(), vstack(), hstack(), split(), flip(), roll(), transpose(), swapaxes(), squeeze(), and the overloaded operator<< function.

## Usage
Include the numpy++.hpp header file in your C++ program.
Create instances of the NumpyArray class using the provided constructors.
Perform desired operations on the arrays using the member functions.

## Example:

```cpp
#include <iostream>
#include "numpy++.hpp"

int main() {
    // Create a 2x3 array
    NumpyArray arr(2, 3);
    arr(0, 0) = 0; arr(0, 1) = 1; arr(0, 2) = 2;
    arr(1, 0) = 3; arr(1, 1) = 4; arr(1, 2) = 5;

    std::cout << "Original array:\n" << arr << std::endl;

    // Reshape the array
    arr.reshape(3, 2);
    std::cout << "Reshaped array:\n" << arr << std::endl;

    // Resize the array
    arr.resize(2, 3);
    std::cout << "Resized array:\n" << arr << std::endl;

// more....
    return 0;
}
```
