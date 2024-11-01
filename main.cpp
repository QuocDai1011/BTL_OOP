#include <iostream>
#include "./HospitalData.hpp"
#include "./HospitalFunction.hpp"
using namespace std;

Human *staff[100]; // mang con tro cua staff
Human *patient[100000]; //mang con tro cua patient
Human *doctor[1000]; // mang con tro cua doctor


int main() { 
    // Staff đăng nhập
    staff[0] = new Staff;
    int login = 0;
    Staff* staffPtr = dynamic_cast<Staff*>(staff[0]);
    
    if (staffPtr) { // Kiểm tra xem ép kiểu có thành công không
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
}
