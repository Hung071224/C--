

#include <iostream>
#include <cmath>
using namespace std;

// Biến toàn cục để đếm số viên gạch
int count = 0;

// Hàm để in ra ma trận kết quả
void printMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Hàm để kiểm tra xem một ô có thuộc vùng khuyết hay không
bool isMissing(int x, int y, int n) {
    // Nếu n = 2, chỉ có một ô khuyết ở góc phải trên
    if (n == 2) {
        return (x == 0 && y == 1);
    }
    // Nếu n > 2, chia ma trận thành 4 phần bằng nhau
    // và kiểm tra xem ô đó thuộc phần nào
    int half = n / 2;
    if (x < half && y < half) {
        // Phần trên trái, không có ô khuyết
        return false;
    }
    else if (x < half && y >= half) {
        // Phần trên phải, có ô khuyết ở góc phải trên
        return isMissing(x, y - half, half);
    }
    else if (x >= half && y < half) {
        // Phần dưới trái, không có ô khuyết
        return false;
    }
    else {
        // Phần dưới phải, không có ô khuyết
        return false;
    }
}

// Hàm để lát nền nhà bị khuyết một góc bằng các viên gạch hình thợ
void latNen(int** matrix, int x, int y, int n) {
    // Nếu n = 2, chỉ cần lát một viên gạch hình thợ
    if (n == 2) {
        count++; // Tăng biến đếm
        // Lát viên gạch hình thợ sao cho che kín 3 ô còn lại
        for (int i = x; i < x + n; i++) {
            for (int j = y; j < y + n; j++) {
                if (!isMissing(i, j, n)) {
                    matrix[i][j] = count;
                }
            }
        }
        return;
    }
    // Nếu n > 2, chia ma trận thành 4 phần bằng nhau
    // và lát nền cho từng phần
    int half = n / 2;
    // Lát nền cho phần trên trái
    latNen(matrix, x, y, half);
    // Lát nền cho phần trên phải
    latNen(matrix, x, y + half, half);
    // Lát nền cho phần dưới trái
    latNen(matrix, x + half, y, half);
    // Lát nền cho phần dưới phải
    latNen(matrix, x + half, y + half, half);
    // Sau khi lát xong 4 phần, cần lát thêm một viên gạch hình thợ
    // để che kín 3 ô ở giữa của ma trận
    count++; // Tăng biến đếm
    // Lát viên gạch hình thợ sao cho che kín 3 ô ở giữa
    for (int i = x + half - 1; i <= x + half; i++) {
        for (int j = y + half - 1; j <= y + half; j++) {
            if (!isMissing(i, j, n)) {
                matrix[i][j] = count;
            }
        }
    }
}

// Hàm chính để thực thi chương trình
int main() {
    // Nhập vào số k
    int k;
    cout << "Nhap k (2 <= k <= 10): ";
    cin >> k;
    // Kiểm tra điều kiện của k
    if (k < 2 || k > 10) {
        cout << "k khong hop le!" << endl;
        return 0;
    }
    // Tính cạnh của nền nhà
    int n = pow(2, k);
    // Khởi tạo ma trận để lưu kết quả
    int** matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }
    // Gọi hàm lát nền nhà
    latNen(matrix, 0, 0, n);
    // In ra kết quả
    cout << "So vien gach hinh tho can dung la: " << count << endl;
    cout << "Ma tran ket qua la: " << endl;
    printMatrix(matrix, n);
    // Giải phóng bộ nhớ
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    return 0;
}
