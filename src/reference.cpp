//эталонные вычисления
#include <iostream>
#include <vector>
#include<stdexcept>

using Matrix = std::vector<std::vector<int>>;

Matrix ternary_binary_gemm(const Matrix& A, const Matrix& B){ //General Matrix Multiplication — общее матричное умножение.
    if (A.empty() || B.empty() || A[0].empty() || B[0].empty()){ //проверка на пустые мвтрицы
        throw std::invalid_argument("Matrices must not be empty"); //исключения пока не перехватываем
    } 
    
    const std::size_t M = A.size(); //кол-во строк A
    const std::size_t K = A[0].size(); //кол-во столбцов A
    const std::size_t N = B[0].size(); //кол-во столбцов B
    
    for (const auto& row : A){
        if (row.size() != K){ //проверка на одинаковую длинну строк 
            throw std::invalid_argument("A is not rectangular"); 
        }
        for (int value : row){
            if (value != -1 && value != 0 && value != 1){
                throw std::invalid_argument("A must be ternary"); 
            }
        }
    }

    if (B.size() != K) {
        throw std::invalid_argument("Incompatible matrix dimensions");
    }

    for (const auto& row : B) { //проверяем элементы 
        if (row.size() != N) {
            throw std::invalid_argument("B is not rectangular");
        }

        for (int value : row) {
            if (value != -1 && value != 1) {
                throw std::invalid_argument("B must be binary");
            }
        }
    }

    Matrix C(M, std::vector<int>(N, 0)); //Она создаёт матрицу с (M) строками, каждая из которых содержит (N) нулей.
    // Reference implementation: three nested loops
    for (std::size_t i = 0; i < M; ++i) { //Перебираем строки матрицы результата.
        for (std::size_t j = 0; j < N; ++j) { //Перебираем столбцы матрицы результата.
            int sum = 0;

            for (std::size_t k = 0; k < K; ++k) { //Вычисляет скалярное произведение.
                sum += A[i][k] * B[k][j];
            }

            C[i][j] = sum;
        }
    }

    return C;
}

int main(){
    Matrix A = {
        {1, 0, -1},
        {-1, 1, 1}
    };

    Matrix B = {
        {1, -1},
        {-1, 1},
        {1, 1}
    };
    
    Matrix C = ternary_binary_gemm(A, B);

    for (const auto& row : C) {
        for (int value : row) {
            std::cout << value << " ";
        }
        std::cout << '\n';
    }

    return 0;
}
