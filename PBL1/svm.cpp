#include <iostream>
#include <vector>
#include <cmath> 
using namespace std;

// Ham tinh toan Hinge Loss
double calculateHingeLoss(double x1, double x2, int y, double w1, double w2, double b) {
    double loss = 0;
    if (y == 1) {
        loss = 1 - (w1 * x1 + w2 * x2 + b); // Tinh toan loss khi nhan la 1
    } else {
        loss = 1 + (w1 * x1 + w2 * x2 + b); // tinh toan loss khi nhan khong phai 1
    }
    if (loss < 0) loss = 0; // dam bao Loss khong nho hon 0
    return loss;
}

// ham tinh toan SVM Loss
double calculateSVMLoss(const vector<double>& x1, const vector<double>& x2, const vector<int>& y, double w1, double w2, double b, double &dw1, double &dw2, double &db) {
    int n = static_cast<int>(y.size());
    double cost = 0;
    dw1 = 0;
    dw2 = 0;
    db = 0;
    for (int i = 0; i < n; i++) {
        double loss = calculateHingeLoss(x1[i], x2[i], y[i], w1, w2, b); // Tinh toan hingeloss cho tung diem du lieu
        cost += loss; // Tong hoa loss cho toan bo du lieu
        if (loss > 0) {
            dw1 += (-x1[i] * y[i]); // dao ham cua cost theo w1
            dw2 += (-x2[i] * y[i]); // dao ham cua cost theo w2
            db += (-y[i]); // dao ham cua cost theo b
        }
    }
    cost /= n; // Chuan hoa cost
    dw1 /= n; // Chuan hoa dao ham cua cost theo w1
    dw2 /= n; // Chuan hoa dao ham cua cost theo w2
    db /= n; // Chuan hoa dao ham cua cost theo b
    return cost;
}

// Ham huan luyen SVM
void trainSVM(const vector<double>& x1, const vector<double>& x2, const vector<int>& y) {
    double learningRate = 0.0005;
    double threshold = 0.001;
    double w1 = 1;
    double w2 = 1;
    double b = 0;
    double dw1 = 0;
    double dw2 = 0;
    double db = 0;
    int iter = 0;
    while (true) {
        double cost = calculateSVMLoss(x1, x2, y, w1, w2, b, dw1, dw2, db); // Tinh toan SVM Loss
        iter++;
      
        if (abs(dw1) < threshold && abs(dw2) < threshold && abs(db) < threshold) { // Kiem tra dieu kien dung
            cout << "Equation: " << w1 << " * x1 + " << w2 << " * x2 + " << b << " = 0" << endl; // In ra phuong trinh sieu phang tim duoc
            break;
        }
        w1 -= learningRate * dw1; // Cap nhat w1
        w2 -= learningRate * dw2; //Cap nhat w2
        b -= learningRate * db; // Cap nhat  b
    }
}

int main() {
    // Du lieu dau vao
    double x1[18] = {35, 27, 19, 25, 26, 45, 46, 48, 47, 29, 27, 28, 27, 30, 28, 23, 27, 18};
    double x2[18] = {20, 57, 76, 33, 52, 26, 28, 29, 49, 43, 137, 44, 90, 49, 84, 20, 54, 44};
    int y[18] = {-1, -1, -1, -1, -1, 1, 1, 1, 1, -1, 1, -1, -1, -1, -1, -1, -1, -1};

    // Chuyen doi mang thanh vector
    vector<double> X1(x1, x1 + 18);
    vector<double> X2(x2, x2 + 18);
    vector<int> Y(y, y + 18);

    // Huan luyen SVM
    trainSVM(X1, X2, Y);

    return 0;
}
