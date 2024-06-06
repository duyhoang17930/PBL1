#include <iostream>
#include <vector>
#include <cmath> 
#include <fstream>
#include <string.h>

using namespace std;

double cs1,cs2,cs3;     //bien luu gia tri in ra man hinh

// Ham tim diem con nam sai class de cap nhat w1, w2, b
double calculateHingeLoss(double x1, double x2, int y, double w1, double w2, double b) {
    double loss = 1 - y*(w1 * x1 + w2 * x2 + b);    // loss lon hon 0 thi diem nam sai vung => cap nhat w1, w2, b
    if (loss < 0) loss = 0; // diem da nam dung class
    return loss;
}


// ham tinh dao ham cua w1, w2, b
void calculateSVMLoss(const vector<double>& x1, const vector<double>& x2, const vector<int>& y, double w1, double w2, double b, double &dw1, double &dw2, double &db) {
    int n = static_cast<int>(y.size());
    dw1 = 0;    //dao ham cua w1
    dw2 = 0;    //dao ham cua w2
    db = 0;     //dao ham cua b
    for (int i = 0; i < n; i++) {
        double loss = calculateHingeLoss(x1[i], x2[i], y[i], w1, w2, b); // Tinh toan hingeloss cho tung diem du lieu
        if (loss > 0) {
            dw1 += (-x1[i] * y[i]); // cap nhat dao ham cua w1
            dw2 += (-x2[i] * y[i]); // cap nhat dao ham cua w2
            db += (-y[i]); // cap nhat dao ham cua b
        }
    }
    dw1 /= n; // Chuan hoa dao ham w1
    dw2 /= n; // Chuan hoa dao ham w2
    db /= n; // Chuan hoa dao ham b
}


//gioi thieu ve de tai
void introduce(){
    cout << "+-------------------------------------------------------------------------------+\n";
    cout << "|                         TRUONG DAI HOC BACH KHOA                              |\n";
    cout << "|                         KHOA CONG NGHE THONG TIN                              |\n";
    cout << "|                                                                               |\n";
    cout << "|                        DO AN LAP TRINH TINH TOAN                              |\n";
    cout << "|       QUA TRINH TINH TOAN SU DUNG THUAT TOAN SUPPORT VECTOR MACHINE (SVM)     |\n";
    cout << "|                                                                               |\n";
    cout << "|                Nguoi huong dan: PGS. TS. Nguyen Tan Khoi                      |\n";
    cout << "|                                                                               |\n";
    cout << "|                           Sinh vien thuc hien:                                |\n";
    cout << "|                                                                               |\n";
    cout << "|          Luu Hoang Phuc        102230366                     NHOM: 20         |\n";
    cout << "|                                                                               |\n";
    cout << "|          Nguyen Duy Hoang      102230347                     NHOM: 20         |\n";
    cout << "|                                                                               |\n";
    cout << "+-------------------------------------------------------------------------------+\n";
    
} 


// Ham tinh toan SVM
void trainSVM(const vector<double>& x1, const vector<double>& x2, const vector<int>& y) {
    double learningRate = 0.0005;   //toc do thay doi w1, w2, b
    double threshold = 0.001;   //dieu kien dung, do chinh xac
    double w1 = 1;
    double w2 = 1;  // gia tri ban dau cua w1, w2, b
    double b = 0;
    double dw1 = 0;
    double dw2 = 0;
    double db = 0;
    while (true) {
    	calculateSVMLoss(x1, x2, y, w1, w2, b, dw1, dw2, db); // Tinh toan SVM Loss
        
        if (abs(dw1) < threshold && abs(dw2) < threshold && abs(db) < threshold) { // Kiem tra dieu kien dung
           cs1=w1;cs2=w2;cs3=b;//ghi lai duong thang tim duoc de in ra file
            break;
        }
        w1 -= learningRate * dw1; // Cap nhat w1
        w2 -= learningRate * dw2; //Cap nhat w2
        b -= learningRate * db; // Cap nhat  b
    }
}

string Chonfile(){
    string filename;
    int t;
    cout << "Chon file input (0-5): "; //chon file
    cin >> t;
    switch(t){
    	case 0:
    		filename = "0";
    		break;
        case 1:
            filename = "18diem.csv";
            break;
        case 2:
            filename = "15diem.csv";
            break;
        case 3:
            filename = "15diem2.csv";
            break;
        case 4:
            filename = "599diem.csv";
            break;
        case 5:
            filename = "1078diem.csv";
            break;
    }
    return filename;
}


void Print(double w1,double w2, double b){
    cout << "\nw1 = "<<w1<<"\nw2 = "<<w2<<"\nb = "<<b<<"\n";
    string dauw2,daub;
    dauw2 = w2<0?" - ":" + ";
    daub = b<0?" - ":" + ";
    cout << "Equation: " << w1 << " * x1" <<dauw2<< fabs(w2) << " * x2 " <<daub<< fabs(b) << " = 0" << "\n\n";// In ra phuong trinh sieu phang tim duoc
}

void bang_chon(){
	cout << "0: Thoat chuong trinh"<<"\n";
    cout << "1: 18 diem"<<"\n";
    cout << "2: 15 diem"<<"\n";
    cout << "3: 15 diem"<<"\n";
    cout << "4: 599 diem"<<"\n";
    cout << "5: 1078 diem"<<"\n";
}

int main() {
    //gioi thieu
    introduce();
    string filename;
	bang_chon();
    // Du lieu dau vao
    while(true){
//    string filename;
    ifstream file;
    filename = Chonfile();
    file.open(filename.c_str());
    //kiem tra file
    if (filename=="0") return 0;
    if (!file){
    	cerr<<"Khong the mo file ! "<<filename<<std::endl;
    	return 1;
	}
    ofstream output;
	output.open("output.txt",ios::out);
    int n,i;
    file>>n;
    double x1[n+1],x2[n+1];
    int y[n];
    
    for (int i=0;i<=n+1;i++){   //doc file csv
    	file>>x1[i];
    	file.ignore();
    	file>>x2[i];
    	file.ignore();
    	file>>y[i];
    	file.ignore();
	} 
	file.close();
    // Chuyen doi mang thanh vector
    vector<double> X1(x1, x1 + n);
    vector<double> X2(x2, x2 + n);
    vector<int> Y(y, y + n);
    
    //Tinh toan w1, w2, b
    trainSVM(X1, X2, Y);
    
    Print(cs1,cs2,cs3);
    output << "Equation: " << cs1 << " * x1 " << cs2 << " * x2 " << cs3 << " = 0" << "\n\n";
    output.close();
	}
    return 0;
}
