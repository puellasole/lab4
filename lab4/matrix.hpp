#pragma once

#include <iostream>
#include <cmath>

namespace mt {

    template<class T, int N, int M>
    class Matrix {
    public:
        Matrix(int n, int m) {
            n_size = n;
            m_size = m;
            matrix = new T * [n_size];
            for (int i = 0; i < n_size; i++) {
                matrix[i] = new T[m_size];
            }
            fillMatrix();
        }
        Matrix() {
            n_size = N;
            m_size = M;
            matrix = new T * [n_size];
            for (int i = 0; i < n_size; i++) {
                matrix[i] = new T[m_size];
            }
            fillMatrix();
        }

        Matrix(const Matrix& temp) {
            m_size = temp.m_size;
            n_size = temp.n_size;
            matrix = new T * [n_size];
            for (int i = 0; i < n_size; i++)
                matrix[i] = new T[m_size];
            for (int i = 0; i < n_size; i++)
                for (int j = 0; j < m_size; j++)
                    matrix[i][j] = temp.matrix[i][j];
        }

        ~Matrix() { deleteMatrix(); }

        T determinant() {
            T result = 0;
            T** minor = new T * [n_size - 1];
            for (int i = 0; i < n_size; i++)
                minor[i] = new T[m_size - 1];

            if ((n_size == m_size) && (n_size <= 3)) {
                if (n_size == 1)
                    result = matrix[0][0];
                else if (n_size == 2)
                    result = static_cast<T>((matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]));
                else
                    result = (matrix[0][0] * matrix[1][1] * matrix[2][2] + matrix[1][0] * matrix[0][2] * matrix[2][1] + matrix[0][1] * matrix[2][0] * matrix[1][2] - matrix[0][2] * matrix[1][1] * matrix[2][0] - matrix[0][0] * matrix[1][2] * matrix[2][1] - matrix[2][2] * matrix[0][1] * matrix[1][0]);
            }

            return result;
        }

        T& at(unsigned int i, unsigned int j) {
            if (i < n_size and j < m_size)
                return matrix[i][j];
            std::abort();
        }

        T* operator[](const T& index) {
            return matrix[index];
        }

        Matrix& operator=(const Matrix& temp) {
            n_size = temp.n_size;
            m_size = temp.m_size;
            deleteMatrix();
            matrix = new T * [n_size];
            for (int i = 0; i < temp.n_size; i++) {
                matrix[i] = new T[m_size];
                for (int j = 0; j < temp.m_size; j++)
                    matrix[i][j] = temp.matrix[i][j];
            }
            return *this;
        }

        Matrix operator+(const Matrix temp) {
            Matrix newMatrix = temp;
            for (int i = 0; i < n_size; i++) {
                for (int j = 0; j < m_size; j++) {
                    newMatrix.matrix[i][j] += matrix[i][j];
                }
            }
            return newMatrix;
        }

        Matrix& operator++(int k) {
            for (int i = 0; i < n_size; i++)
                for (int j = 0; j < m_size; j++)
                    matrix[i][j]++;
            return *this;
        }

        Matrix& operator+=(const Matrix& temp) {
            for (int i = 0; i < n_size; i++)
                for (int j = 0; j < m_size; j++)
                    matrix[i][j] += temp.matrix[i][j];
            return *this;
        }

        Matrix operator*(const Matrix temp) {
            Matrix<T, N, M> newMatrix;
            for (int i = 0; i < n_size; i++)
                for (int j = 0; j < newMatrix.n_size; j++)
                    for (int k = 0; k < newMatrix.m_size; k++)
                        newMatrix.matrix[i][j] += matrix[i][k] * temp.matrix[k][j];
            return newMatrix;
        }

        Matrix& operator*=(const Matrix& temp) {
            for (int i = 0; i < n_size; i++)
                for (int j = 0; j < n_size; j++)
                    for (int k = 0; k < m_size; k++)
                        matrix[i][j] += matrix[i][k] * temp.matrix[k][j];
            return *this;
        }

        friend std::ostream& operator<<(std::ostream& outStream, const Matrix& temp) {
            for (int i = 0; i < temp.n_size; i++) {
                for (int j = 0; j < temp.m_size; j++)
                    outStream << temp.matrix[i][j] << " ";
                outStream << std::endl;
            }
            outStream << std::endl;
            return outStream;
        }

        friend std::istream& operator>>(std::istream& outStream, const Matrix& temp) {
            for (int i = 0; i < temp.n_size; i++)
                for (int j = 0; j < temp.m_size; j++)
                    outStream >> temp.matrix[i][j];
            return outStream;
        }

    private:
        T** matrix;
        int n_size;
        int m_size;

        T fillMinor(T** minor, int n) {
            T result = 0;
            int a = 1;
            int b = 1;
            for (int i = 0; i < n_size; i++)
                for (int j = 0; j < m_size; j++)
                    if ((j != n) and (i != 0)) {
                        (j < nand i > 0) ? minor[i - 1][j] = matrix[i][j] : ((j > n and i > 0) ? minor[i - 1][j - 1] = matrix[i][j] : a = 1);
                    }
            result = (minor[0][0] * minor[1][1]) - (minor[1][2] * minor[2][1]);
            return result;
        }

        void fillMatrix() {
            for (int i = 0; i < n_size; ++i)
                for (int j = 0; j < m_size; ++j)
                    matrix[i][j] = 0;


        }

        void deleteMatrix() {
            for (int i = 0; i < n_size; i++)
                delete[] matrix[i];
            delete[] matrix;
        }
    };


}
