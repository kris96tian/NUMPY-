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