#include <iostream>
#include "lab4/matrix.hpp"


int main() {

    mt::Matrix<int, 3, 3> matrix;
    mt::Matrix<int, 3, 3> matrix2;
    std::cin >> matrix;
    matrix2 = matrix;
    mt::Matrix<int, 3, 3> matrix3 = matrix + matrix2;
    std::cout << matrix.determinant() << std::endl;
    matrix[1][1] = 6;
    std::cout << matrix;
    std::cout << matrix3;
    std::cout << matrix[1][1];


}








