

#include <iostream>
#include <cmath>
using namespace std;

int count = 0;

void printMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

bool isMissing(int x, int y, int n) {

    if (n == 2) {
        return (x == 0 && y == 1);
    }

    int half = n / 2;
    if (x < half && y < half) {

        return false;
    }
    else if (x < half && y >= half) {

        return isMissing(x, y - half, half);
    }
    else if (x >= half && y < half) {

        return false;
    }
    else {

        return false;
    }
}

void latNen(int** matrix, int x, int y, int n) {

    if (n == 2) {
        count++;
        for (int i = x; i < x + n; i++) {
            for (int j = y; j < y + n; j++) {
                if (!isMissing(i, j, n)) {
                    matrix[i][j] = count;
                }
            }
        }
        return;
    }
    int half = n / 2;
    latNen(matrix, x, y, half);
    latNen(matrix, x, y + half, half);
    latNen(matrix, x + half, y, half);
    latNen(matrix, x + half, y + half, half);
    count++; 
    for (int i = x + half - 1; i <= x + half; i++) {
        for (int j = y + half - 1; j <= y + half; j++) {
            if (!isMissing(i, j, n)) {
                matrix[i][j] = count;
            }
        }
    }
}

int main() {
    int k;
    cout << "Nhap k (2 <= k <= 10): ";
    cin >> k;
    if (k < 2 || k > 10) {
        cout << "k khong hop le!" << endl;
        return 0;
    }
    int n = pow(2, k);
    int** matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }
    latNen(matrix, 0, 0, n);
    cout << "So vien gach hinh tho can dung la: " << count << endl;
    cout << "Ma tran ket qua la: " << endl;
    printMatrix(matrix, n);
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    return 0;
}
