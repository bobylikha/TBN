#include "../src/reference/gemm.hpp"
#include "../src/optimized/encoding.hpp"

#include <cassert>
#include <iostream>
#include <stdexcept>

int main() {
    Matrix A = {
        {1, 0, -1},
        {-1, 1, 1}
    };

    Matrix B = {
        {1, -1},
        {-1, 1},
        {1, 1}
    };

    Matrix expected = {
        {0, -2},
        {-1, 3}
    };

    Matrix actual = ternary_binary_gemm(A, B);

    assert(actual == expected); //проверяет, совпадает ли результат нашей функции с правильным ответом

    std::cout << "Reference GEMM test passed!\n";


    // Test 2: matrices of size 1x1
    {
        Matrix A = {{-1}};
        Matrix B = {{1}};

        Matrix expected = {{-1}};

        Matrix actual = ternary_binary_gemm(A, B);

        assert(actual == expected);

        std::cout << "1x1 matrix test passed!\n";
    }

    // Test 3: incompatible matrix dimensions
    {
        Matrix A = {{1, 0, -1}};
        Matrix B = {
            {1, -1},
            {-1, 1}
        };

        bool exception_thrown = false;

        try {
            Matrix C = ternary_binary_gemm(A, B);
        }
        catch (const std::invalid_argument&) {
            exception_thrown = true; //исключения при неправильном размере матрицы
        }

        assert(exception_thrown);

        std::cout << "Dimension mismatch test passed!\n";
    }

    // Test 4: encoding
    {
        TernaryBits positive = encode_ternary(1);
        TernaryBits zero = encode_ternary(0);
        TernaryBits negative = encode_ternary(-1);

        assert(positive.positive == 1);
        assert(positive.negative == 0);

        assert(zero.positive == 0);
        assert(zero.negative == 0);

        assert(negative.positive == 0);
        assert(negative.negative == 1);

        assert(encode_binary(1) == 0);
        assert(encode_binary(-1) == 1);

        std::cout << "Encoding test passed!\n";
    }
    return 0;
}
