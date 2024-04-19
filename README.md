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

    // Create a numpy arr
    NumpyArray arr(2, 3);
    int count = 0;
    for (int i = 0; i < arr.shape(0); ++i) {
        for (int j = 0; j < arr.shape(1); ++j) {
            arr(i, j) = count++;
        }
    }

    // print original arr
    std::cout << "Original array:" << std::endl;
    std::cout << arr << std::endl;

    // reshape 
    arr.reshape(3, 2);
    std::cout << "Reshaped array:" << std::endl;
    std::cout << arr << std::endl;

    // resize
    arr.resize(2, 3);
    std::cout << "Resized array:" << std::endl;
    std::cout << arr << std::endl;

    // create another arr
    NumpyArray arr2(2, 3);
    for (int i = 0; i < arr2.shape(0); ++i) {
        for (int j = 0; j < arr2.shape(1); ++j) {
            arr2(i, j) = i * arr2.shape(1) + j + 6;
        }
    }
    std::cout << "Second array:" << std::endl;
    std::cout << arr2 << std::endl;

    // Concat arrays
    NumpyArray concatenated = NumpyArray::concatenate(arr, arr2, 0);
    std::cout << "Concatenated array along axis 0:" << std::endl;
    std::cout << concatenated << std::endl;

    //  vertically stack both arrs
    NumpyArray vstacked = NumpyArray::vstack(arr, arr2);
    std::cout << "Vertically stacked array:" << std::endl;
    std::cout << vstacked << std::endl;

    // -||- horizontally
    NumpyArray hstacked = NumpyArray::hstack(arr, arr2);
    std::cout << "Horizontally stacked array:" << std::endl;
    std::cout << hstacked << std::endl;

    // Spliit arr
    std::vector<NumpyArray> splitted = arr.split(0, 2);
    std::cout << "Split array along axis 0:" << std::endl;
    for (const auto& arr : splitted) {
        std::cout << arr << std::endl;
    }

    // now flip it
    arr.flip(0);
    std::cout << "Flipped array along axis 0:" << std::endl;
    std::cout << arr << std::endl;

    // roll it baby
    arr.roll(1, 1);
    std::cout << "Rolled array along axis 1:" << std::endl;
    std::cout << arr << std::endl;

    // transpose
    NumpyArray transposed = arr.transpose();
    std::cout << "Transposed array:" << std::endl;
    std::cout << transposed << std::endl;

    // swap the azes
    NumpyArray swapped = arr.swapaxes(0, 1);
    std::cout << "Swapped axes of array:" << std::endl;
    std::cout << swapped << std::endl;

    // Resize
    arr.resize(1, 3);
    std::cout << "Resized array:" << std::endl;
    std::cout << arr << std::endl;


    // new arr with singleton dimensions
    std::vector<std::vector<std::vector<double>>> data3D = {arr.get_data3D()[0]};
    NumpyArray arr_with_singleton(data3D);
    std::cout << "Array with singleton dimensions:" << std::endl;
    std::cout << arr_with_singleton << std::endl;

    // squeeeeeeeze
    NumpyArray squeezed = arr_with_singleton.squeeze();
    std::cout << "Squeezed array:" << std::endl;
    std::cout << squeezed << std::endl;

    return 0;
}
```
## Example output:

```bash
 ./numpy 
Original array:
0 1 2 
3 4 5 

Reshaped array:
0 1 
2 3 
4 5 

Resized array:
0 1 0 
2 3 0 

Second array:
6 7 8 
9 10 11 

Concatenated array along axis 0:
0 1 0 
2 3 0 
6 7 8 
9 10 11 

Vertically stacked array:
0 1 0 
2 3 0 
6 7 8 
9 10 11 

Horizontally stacked array:
0 1 0 6 7 8 
2 3 0 9 10 11 

Split array along axis 0:
0 1 0 

2 3 0 

Flipped array along axis 0:
2 3 0 
0 1 0 

Rolled array along axis 1:
3 0 2 
1 0 0 

Transposed array:
3 1 
0 0 
2 0 

Swapped axes of array:
3 1 
0 0 
2 0 

Resized array:
3 0 2 

Array with singleton dimensions:
3 0 2 

Squeezed array:
3 0 2 


```
