#ifndef NUMPY_ARRAY_HPP
#define NUMPY_ARRAY_HPP

#include <vector>
#include <iostream>
#include <algorithm>

class NumpyArray {
private:
    std::vector<std::vector<std::vector<double>>> data3D;
    int rows;
    int cols;
    int depth;

public:
    NumpyArray(int rows, int cols);
    NumpyArray(std::vector<std::vector<double>> data);
    NumpyArray(std::vector<std::vector<std::vector<double>>> data3D);

    double& operator()(int row, int col);
    const double& operator()(int row, int col) const;

    int shape(int dim) const;

    void reshape(int rows, int cols);
    void resize(int rows, int cols);
    static NumpyArray concatenate(const NumpyArray& arr1, const NumpyArray& arr2, int axis);
    static NumpyArray vstack(const NumpyArray& arr1, const NumpyArray& arr2);
    static NumpyArray hstack(const NumpyArray& arr1, const NumpyArray& arr2);
    std::vector<NumpyArray> split(int axis, int numSections);
    void flip(int axis);
    void roll(int shift, int axis);
    NumpyArray transpose() const;
    NumpyArray swapaxes(int axis1, int axis2);
    NumpyArray squeeze() const;

    const std::vector<std::vector<std::vector<double>>>& get_data3D() const; // New member function

    friend std::ostream& operator<<(std::ostream& os, const NumpyArray& arr);
};

#endif
/*
$ g++ -o numpy numpy_array.cpp main.cpp
*/