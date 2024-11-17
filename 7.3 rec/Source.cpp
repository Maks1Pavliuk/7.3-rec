#include <iostream>
#include <iomanip>
using namespace std;

void Input(int** a, const int rowCount, const int colCount, int rowNo = 0, int colNo = 0);
void Print(int** a, const int rowCount, const int colCount, int rowNo = 0, int colNo = 0);
bool Part1_ZeroCol(int** a, const int rowCount, const int colNo, bool& result, int rowNo = 0);
void Part1_CountCol(int** a, const int rowCount, const int colNo, int& count, int rowNo = 0);
void Part1_CountCols(int** a, const int rowCount, const int colCount, int& count, bool& result, int colNo = 0);
bool IsMaxInRowN(int** a, const int n, const int k, const int colCount, int colNo = 0, int max = INT_MIN);
bool IsMinInColK(int** a, const int n, const int k, const int rowCount, int rowNo = 0, int min = INT_MAX);
void Part2_SaddlePointRow(int** a, const int rowCount, const int colCount, const int rowNo, int colNo = 0);
void Part2_SaddlePointRows(int** a, const int rowCount, const int colCount, int rowNo = 0);

int main() {
    int rowCount, colCount;
    cout << "rowCount = "; cin >> rowCount;
    cout << "colCount = "; cin >> colCount;

    int** a = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    Input(a, rowCount, colCount);
    Print(a, rowCount, colCount);

    int count = 0;
    bool result = false;
    Part1_CountCols(a, rowCount, colCount, count, result);
    if (result)
        cout << "Count of positive elements in columns with at least one zero: " << count << endl;
    else
        cout << "No zero elements in columns." << endl;

    cout << "Saddle points (max in row & min in column):" << endl;
    Part2_SaddlePointRows(a, rowCount, colCount);

    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;
    return 0;
}

void Input(int** a, const int rowCount, const int colCount, int rowNo, int colNo) {
    if (rowNo < rowCount) {
        if (colNo < colCount) {
            cout << "a[" << rowNo << "][" << colNo << "] = ";
            cin >> a[rowNo][colNo];
            Input(a, rowCount, colCount, rowNo, colNo + 1);
        }
        else {
            cout << endl;
            Input(a, rowCount, colCount, rowNo + 1, 0);
        }
    }
}

void Print(int** a, const int rowCount, const int colCount, int rowNo, int colNo) {
    if (rowNo < rowCount) {
        if (colNo < colCount) {
            cout << setw(4) << a[rowNo][colNo];
            Print(a, rowCount, colCount, rowNo, colNo + 1);
        }
        else {
            cout << endl;
            Print(a, rowCount, colCount, rowNo + 1, 0);
        }
    }
}

bool Part1_ZeroCol(int** a, const int rowCount, const int colNo, bool& result, int rowNo) {
    if (rowNo < rowCount) {
        if (a[rowNo][colNo] == 0) {
            result = true;
            return true;
        }
        return Part1_ZeroCol(a, rowCount, colNo, result, rowNo + 1);
    }
    return false;
}

void Part1_CountCol(int** a, const int rowCount, const int colNo, int& count, int rowNo) {
    if (rowNo < rowCount) {
        if (a[rowNo][colNo] > 0)
            count++;
        Part1_CountCol(a, rowCount, colNo, count, rowNo + 1);
    }
}

void Part1_CountCols(int** a, const int rowCount, const int colCount, int& count, bool& result, int colNo) {
    if (colNo < colCount) {
        bool hasZero = false;
        if (Part1_ZeroCol(a, rowCount, colNo, result)) {
            Part1_CountCol(a, rowCount, colNo, count);
        }
        Part1_CountCols(a, rowCount, colCount, count, result, colNo + 1);
    }
}

bool IsMaxInRowN(int** a, const int n, const int k, const int colCount, int colNo, int max) {
    if (colNo < colCount) {
        if (a[n][colNo] > a[n][k])
            return false;
        return IsMaxInRowN(a, n, k, colCount, colNo + 1);
    }
    return true;
}

bool IsMinInColK(int** a, const int n, const int k, const int rowCount, int rowNo, int min) {
    if (rowNo < rowCount) {
        if (a[rowNo][k] < a[n][k])
            return false;
        return IsMinInColK(a, n, k, rowCount, rowNo + 1);
    }
    return true;
}

void Part2_SaddlePointRow(int** a, const int rowCount, const int colCount, const int rowNo, int colNo) {
    if (colNo < colCount) {
        if (IsMaxInRowN(a, rowNo, colNo, colCount) && IsMinInColK(a, rowNo, colNo, rowCount))
            cout << "Saddle point at Row: " << rowNo << ", Col: " << colNo << endl;
        Part2_SaddlePointRow(a, rowCount, colCount, rowNo, colNo + 1);
    }
}

void Part2_SaddlePointRows(int** a, const int rowCount, const int colCount, int rowNo) {
    if (rowNo < rowCount) {
        Part2_SaddlePointRow(a, rowCount, colCount, rowNo);
        Part2_SaddlePointRows(a, rowCount, colCount, rowNo + 1);
    }
}
