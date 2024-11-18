#include <iostream>
#include <vector>
#include <iomanip>
#include "./HospitalData.hpp"
#include "./HospitalFunction.hpp"
using namespace std;

Human *staff[50]; // mang con tro cua staff
Human *patient[1000]; //mang con tro cua patient
Human *doctor[50]; // mang con tro cua doctor

const string RESET = "\033[0m";  // Reset lại màu mặc định
const string RED = "\033[31m";  // Màu đỏ
const string GREEN = "\033[32m";  // Màu xanh lá
const string BLUE = "\033[34m";


int main() { 
    system("CLS");
    // Staff đăng nhập
    staff[0] = new Staff;
    int login = 0; //
    Staff* staffPtr = dynamic_cast<Staff*>(staff[0]);
    
    if (staffPtr) { 
        staffPtr->logIn(login);
    } else {
        cout << "Error: Unable to cast to Staff." << endl;
        return 1;
    }
    if (!login) {
        cout << "Login failed." << endl;
        return 1;
    }
    // Kết thúc đăng nhập
    int indexSp;
    do {
      
    }while(indexSp != 0);
}
