#include "pch.h"
#include "CppUnitTest.h"
#include "../7.3 rec/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    // Вспомогательная функция для создания массива
    int** CreateArray(int rows, int cols) {
        int** a = new int* [rows];
        for (int i = 0; i < rows; i++) a[i] = new int[cols];
        return a;
    }

    // Вспомогательная функция для удаления массива
    void DeleteArray(int** a, int rows) {
        for (int i = 0; i < rows; i++) delete[] a[i];
        delete[] a;
    }

    TEST_CLASS(UnitTest1)
    {
    public:
        TEST_METHOD(TestPart1_ZeroCol)
        {
            int** a = CreateArray(3, 3);
            a[0][0] = 1; a[0][1] = 0; a[0][2] = 3;
            a[1][0] = 4; a[1][1] = 5; a[1][2] = 6;
            a[2][0] = 7; a[2][1] = 8; a[2][2] = 9;

            bool result = false;
            Assert::IsTrue(Part1_ZeroCol(a, 3, 1, result));
            Assert::IsTrue(result);

            DeleteArray(a, 3);
        }

        TEST_METHOD(TestPart1_CountCol)
        {
            int** a = CreateArray(3, 3);
            a[0][0] = 1; a[0][1] = -2; a[0][2] = 3;
            a[1][0] = 4; a[1][1] = 0; a[1][2] = 6;
            a[2][0] = 7; a[2][1] = -8; a[2][2] = 9;

            int count = 0;
            Part1_CountCol(a, 3, 2, count);
            Assert::AreEqual(3, count);

            DeleteArray(a, 3);
        }

        TEST_METHOD(TestIsMaxInRowN)
        {
            int** a = CreateArray(3, 3);
            a[0][0] = 3; a[0][1] = 2; a[0][2] = 1;
            a[1][0] = 4; a[1][1] = 5; a[1][2] = 6;
            a[2][0] = 7; a[2][1] = 8; a[2][2] = 9;

            Assert::IsTrue(IsMaxInRowN(a, 0, 0, 3));
            Assert::IsFalse(IsMaxInRowN(a, 0, 2, 3));

            DeleteArray(a, 3);
        }

        TEST_METHOD(TestIsMinInColK)
        {
            int** a = CreateArray(3, 3);
            a[0][0] = 3; a[0][1] = 5; a[0][2] = 1;
            a[1][0] = 4; a[1][1] = 6; a[1][2] = 7;
            a[2][0] = 8; a[2][1] = 9; a[2][2] = 2;

            Assert::IsTrue(IsMinInColK(a, 0, 2, 3));
            Assert::IsFalse(IsMinInColK(a, 1, 1, 3));

            DeleteArray(a, 3);
        }
    };
}
