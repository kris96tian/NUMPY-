#include "numpy++.hpp"

NumpyArray::NumpyArray(int rows, int cols) : rows(rows), cols(cols), depth(1) {
    data3D.resize(1, std::vector<std::vector<double>>(rows, std::vector<double>(cols, 0)));
}

NumpyArray::NumpyArray(std::vector<std::vector<double>> data) : data3D(1, data), rows(data.size()), cols(data[0].size()), depth(1) {}

NumpyArray::NumpyArray(std::vector<std::vector<std::vector<double>>> data3D) : data3D(data3D) {
    if (!data3D.empty()) {
        depth = data3D.size();
        rows = data3D[0].size();
        cols = data3D[0][0].size();
    } else {
        depth = rows = cols = 0;
    }
}

double& NumpyArray::operator()(int row, int col) {
    return data3D[0][row][col];
}

const double& NumpyArray::operator()(int row, int col) const {
    return data3D[0][row][col];
}

int NumpyArray::shape(int dim) const {
    return (dim == 0) ? rows : cols;
}

const std::vector<std::vector<std::vector<double>>>& NumpyArray::get_data3D() const {
    return data3D;
}

void NumpyArray::reshape(int rows, int cols) {
    if (rows * cols != this->rows * this->cols) {
        std::cerr << "Cannot reshape array: incompatible shapes" << std::endl;
        return;
    }

    std::vector<std::vector<double>> newData(rows, std::vector<double>(cols, 0));
    int k = 0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            newData[i][j] = data3D[0][k / this->cols][k % this->cols];
            k++;
        }
    }

    this->rows = rows;
    this->cols = cols;
    data3D = {newData};
}

void NumpyArray::resize(int rows, int cols) {
    std::vector<std::vector<double>> newData(rows, std::vector<double>(cols, 0));
    int minRows = std::min(rows, this->rows);
    int minCols = std::min(cols, this->cols);

    for (int i = 0; i < minRows; ++i) {
        for (int j = 0; j < minCols; ++j) {
            newData[i][j] = data3D[0][i][j];
        }
    }

    data3D = {newData};
    this->rows = rows;
    this->cols = cols;
}

NumpyArray NumpyArray::concatenate(const NumpyArray& arr1, const NumpyArray& arr2, int axis) {
    if (axis != 0 && axis != 1) {
        std::cerr << "Invalid axis for concatenation" << std::endl;
        return NumpyArray(0, 0);
    }

    if (axis == 0) {
        if (arr1.cols != arr2.cols) {
            std::cerr << "Incompatible shapes for concatenation" << std::endl;
            return NumpyArray(0, 0);
        }

        NumpyArray result(arr1.rows + arr2.rows, arr1.cols);
        for (int i = 0; i < arr1.rows; ++i) {
            for (int j = 0; j < arr1.cols; ++j) {
                result(i, j) = arr1(i, j);
            }
        }
        for (int i = 0; i < arr2.rows; ++i) {
            for (int j = 0; j < arr2.cols; ++j) {
                result(arr1.rows + i, j) = arr2(i, j);
            }
        }
        return result;
    } else {
        if (arr1.rows != arr2.rows) {
            std::cerr << "Incompatible shapes for concatenation" << std::endl;
            return NumpyArray(0, 0);
        }

        NumpyArray result(arr1.rows, arr1.cols + arr2.cols);
        for (int i = 0; i < arr1.rows; ++i) {
            for (int j = 0; j < arr1.cols; ++j) {
                result(i, j) = arr1(i, j);
            }
        }
        for (int i = 0; i < arr2.rows; ++i) {
            for (int j = 0; j < arr2.cols; ++j) {
                result(i, arr1.cols + j) = arr2(i, j);
            }
        }
        return result;
    }
}

NumpyArray NumpyArray::vstack(const NumpyArray& arr1, const NumpyArray& arr2) {
    return concatenate(arr1, arr2, 0);
}

NumpyArray NumpyArray::hstack(const NumpyArray& arr1, const NumpyArray& arr2) {
    return concatenate(arr1, arr2, 1);
}

std::vector<NumpyArray> NumpyArray::split(int axis, int numSections) {
    std::vector<NumpyArray> result;

    if (axis == 0) {
        if (numSections > rows) {
            std::cerr << "Cannot split array: number of sections exceeds number of rows" << std::endl;
            return result;
        }

        int sectionSize = rows / numSections;
        int remainder = rows % numSections;
        int start = 0;
        for (int i = 0; i < numSections; ++i) {
            int end = start + sectionSize + (remainder-- > 0 ? 1 : 0);
            result.emplace_back(std::vector<std::vector<double>>(data3D[0].begin() + start, data3D[0].begin() + end));
            start = end;
        }
    } else {
        if (numSections > cols) {
            std::cerr << "Cannot split array: number of sections exceeds number of columns" << std::endl;
            return result;
        }

        int sectionSize = cols / numSections;
        int remainder = cols % numSections;
        int start = 0;
        for (int i = 0; i < numSections; ++i) {
            int end = start + sectionSize + (remainder-- > 0 ? 1 : 0);
            std::vector<std::vector<double>> newData;


for (const auto& row : data3D[0]) {
    std::vector<double> newRow(row.begin() + start, row.begin() + end);
    newData.push_back(newRow);
}
result.emplace_back(newData);
start = end;
}
}

return result;
}

void NumpyArray::flip(int axis) {
if (axis == 0) {
    std::reverse(data3D[0].begin(), data3D[0].end());
} else {
    for (auto& row : data3D[0]) {
        std::reverse(row.begin(), row.end());
    }
}
}

void NumpyArray::roll(int shift, int axis) {
if (axis == 0) {
    shift = (shift % rows + rows) % rows;
    std::rotate(data3D[0].begin(), data3D[0].begin() + shift, data3D[0].end());
} else {
    shift = (shift % cols + cols) % cols;
    for (auto& row : data3D[0]) {
        std::rotate(row.begin(), row.begin() + shift, row.end());
    }
}
}

NumpyArray NumpyArray::transpose() const {
NumpyArray result(cols, rows);
for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
        result(j, i) = data3D[0][i][j];
    }
}
return result;
}

NumpyArray NumpyArray::swapaxes(int axis1, int axis2) {
return (axis1 == 0 && axis2 == 1) ? transpose() : transpose().transpose();
}

NumpyArray NumpyArray::squeeze() const {
if (depth == 1 && (rows == 1 || cols == 1)) {
    std::vector<std::vector<double>> newData = data3D[0];
    return NumpyArray(newData);
}
return *this;
}

std::ostream& operator<<(std::ostream& os, const NumpyArray& arr) {
for (int i = 0; i < arr.rows; ++i) {
    for (int j = 0; j < arr.cols; ++j) {
        os << arr.data3D[0][i][j] << " ";
    }
    os << std::endl;
}
return os;
}