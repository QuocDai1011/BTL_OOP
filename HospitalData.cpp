#include "./HospitalData.hpp"
#include "./HospitalFunction.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <conio.h>
#include <vector>
#include <set>
#include <algorithm>
#include <thread> 
#include <chrono> 
using namespace std;

const string RESET = "\033[0m";  // Reset lại màu mặc định
const string RED = "\033[31m";  // Màu đỏ
const string GREEN = "\033[32m";  // Màu xanh lá
const string BLUE = "\033[34m";

Human::Human() {
    name = "";
    gender = 0;
    phoneNumber = "";
}

// Định nghĩa hàm khởi tạo có tham số của lớp Human
Human::Human(string name, int gender, string phoneNumber) {
    this->name = name;
    this->gender = gender;
    this->phoneNumber = phoneNumber;
}

void Staff::setName(const string &newName) {
	Human::setName(newName);
}

void Staff::setGender(const int &newGender) {
	Human::setGender(newGender);
}

void Staff::setPhoneNumber(const string &newPhoneNumber) {
	Human::setPhoneNumber(newPhoneNumber);
}

// Định nghĩa hàm khởi tạo không tham số
Staff::Staff() : Human() { 
    ID = "";
    address = "";
    pass = "";
}

// Định nghĩa hàm khởi tạo có tham số của lớp Staff
Staff::Staff(string name, int gender, string phoneNumber, string ID, string address, string pass)
    : Human(name, gender, phoneNumber) { 
    this->ID = ID;
    this->address = address;
    this->pass = pass;
}

// Định nghĩa hàm logIn của lớp Staff
void Staff::logIn(int &login) {
    cout << RED << setw(50) << "__________" << endl;
    cout << setw(50) << "| LOGIN  |" << endl;
    cout << setw(50) << "|________|" << endl << RESET;

    ifstream fs("informationStaff.txt", ios::in);
    if (!fs.is_open()) {
        cout << "Cannot open file informationStaff.txt";
        return;
    }

    // Đọc thông tin từ file vào danh sách
    vector<pair<string, string>> credentials;
    string line;
    while (getline(fs, line)) {
        stringstream ss(line);
        string fileID, filePass;
        ss >> fileID >> filePass;
        credentials.push_back({fileID, filePass});
    }
    fs.close();

        int attemptCount = 3; // Giới hạn số lần đăng nhập
        while (attemptCount--) {
            cout << "Enter ID: ";
            cin >> this->ID;

            char ch;
            string inputPass;
            cout << "Enter Password: ";
            while (true) {
                ch = _getch(); // Lấy ký tự mà không hiển thị
                if (ch == 13) { // Enter kết thúc nhập
                    break;
                } else if (ch == 8) { // Backspace xóa ký tự
                    if (!inputPass.empty()) {
                        inputPass.pop_back();
                        cout << "\b \b";
                    }
                } else {
                    inputPass += ch;
                    cout << "*";
                }
            }
            cout << endl;

            // Kiểm tra thông tin đăng nhập
            bool loginSuccess = false;
            for (const auto& cred : credentials) {
                if (cred.first == this->ID && cred.second == inputPass) {
                    loginSuccess = true;
                    break;
                }
            }

            if (loginSuccess) {
                system("CLS");
                cout << "LOGIN SUCCESS! Welcome, " << this->ID << ".\n";
                cout << "Loading: ";
                for (int i = 0; i < 50; ++i) {
                    cout << "=";
                    this_thread::sleep_for(chrono::milliseconds(50)); // Hiệu ứng thời gian
                }
                for (int i = 0; i < 20; ++i) {
                    this_thread::sleep_for(chrono::milliseconds(50)); // Hiệu ứng thời gian
                }
                cout << " SUCCESS =)))\n";
                cout << "HAVE A NICE DAY!\n\n\n";
                login = 1;
                return;
            } else {
                cout << "LOGIN FAILED! ";
                if (attemptCount > 0) {
                    cout << "You have " << attemptCount << " attempt(s) remaining.\n";
                }
            }
        }

    cout << "Too many failed attempts. Please try again later.\n";
}


Patient::Patient() : Human() {
	currentStatus = "";
    IDmedicine = "";
    quantity = "";
    dateBuy = {0,0,0};
    accumulatedPoints = "0";
    amountReceived = "0";
}

Patient::Patient(string name, int gender, string phoneNumber,  
Date dateBuy, string currentStatus, string IDmedicine, string quantity, string accumulatedPoints, string amountReceived)
	: Human(name, gender, phoneNumber) {
	this->dateBuy = dateBuy;
	this->currentStatus = currentStatus;
    this->IDmedicine = IDmedicine;
    this->accumulatedPoints = accumulatedPoints;
    this->amountReceived = amountReceived;
}

string Patient::getCurrentStatus() {
	return this->currentStatus;
}

void Patient::setName(const string &newName) {
	Human::setName(newName);
}

void Patient::setCurrentStatus(const string &newStatus) {
	this->currentStatus = newStatus;
}

istream& operator>>(istream& is, Patient *p) {
    return is;
}


bool Patient::checkIDdoctor(string IDcheck) {
    ifstream fs("informationDoctor.txt", ios::in);
    if(!fs.is_open()) {
        cout << "Cannot open informationDoctor.txt!";
        return false;
    }
    string line;
    while(getline(fs, line)) {
        stringstream ss(line);
        string word;
        getline(ss, word, '|'); // word la ID cua bac si
        if(word == IDcheck) {
            return true;
        }
    }
    fs.close();
    return false;
}

bool Patient::checkIDmedicine(string IDcheck) {
    ifstream fs("medicineAndPrice.txt", ios::in);
    if(!fs.is_open()) {
        cout << "Cannot open medicineAndPrice.txt!\n";
        return false;
    }
    string line;
    set<string> se;
    while(getline(fs, line)) {
        stringstream ss(line);
        string word;
        getline(ss, word, '|'); // word la ID cua thuoc
        se.insert(word);
    }
    stringstream split(IDcheck);
    string cut;
    while(getline(split, cut, ',')) {
        if(se.find(cut) == se.end()) {
            return false;
        }
    }
    fs.close();
    return true;
}


Prescription::Prescription() {
	ID = "";
	namePrescription = "";
    price = 0;
    dosageForm = "";
    currentQuantity = 0;
    dosageOfDrug = "";
}

Prescription::Prescription(string ID, string namePrescription, double price, string dosageForm,
    int currentQuantity, string dosageOfDrug) {
	this->ID = ID;
	this->namePrescription = namePrescription;
    this->price = price;
    this->dosageForm = dosageForm;
    this->currentQuantity = currentQuantity;
    this->dosageOfDrug = dosageOfDrug;
}

void Prescription::readFromFile() {
    // In tiêu đề bảng
    cout << RED << "+---------+----------------------------------+---------+-------------------------+" << endl;
    cout << "| ID      | Medicine's Name                  | Cost    | Dosage Form             |" << endl;
    cout << "+---------+----------------------------------+---------+-------------------------+" << endl << RESET;

    ifstream fs("medicineAndPrice.txt", ios::in);
    if(!fs.is_open()) {
        cout << "Cannot open medicineAndPrice.txt";
        return;
    }

    string line;
    while(getline(fs, line)) {
        stringstream ss(line);
        string temp;

        // Tách các thông tin thuốc
        getline(ss, temp, '|'); // ID thuốc
        string id = temp;

        getline(ss, temp, '|'); // Tên thuốc
        string name = temp;

        getline(ss, temp, '|'); // Giá bán (bỏ qua)
        string cost = temp;

        getline(ss, temp, '|'); // Dạng bào chế
        string dosageForm = temp;

        // In thông tin thuốc theo định dạng bảng
        cout << "| " << setw(8) << left << id
             << "| " << setw(33) << left << name
             << "| " << setw(8) << left << cost
             << "| " << setw(24) << left << dosageForm
             << "|" << endl;
    }

    // In cuối bảng
    cout << "+---------+----------------------------------+---------+-------------------------+" << endl;

    fs.close();
}

string Prescription::getIDFromFile(string IDCheck) {
    ifstream fs("medicineAndPrice.txt", ios::in);
    if(!fs.is_open()) {
        cout << "Cannot open medicineAndPrice.txt\n";
        return " ";
    }
    string line;
    while(getline(fs, line)){
        stringstream ss(line);
        string split;
        getline(ss, split, '|'); //split la ID thuoc
        if(split == IDCheck) {
            return split;
        }
    }
    fs.close();
    return " ";
}

string Prescription::getNamePresciptionFromFile(string ID) {
    ifstream fs("medicineAndPrice.txt", ios::in);
    if(!fs.is_open()) {
        cout << "Cannot open medicineAndPrice.txt\n";
        return " ";
    }
    string line;
    while(getline(fs, line)){
        stringstream ss(line);
        string split;
        getline(ss, split, '|'); //split la ID thuoc
        if(split == ID) {
            getline(ss, split, '|'); // split la ten thuoc
            return split;
        }
    }
    fs.close();
    return " ";
}

double Prescription::getPriceByIDFromFile(string ID) {
    ifstream fs("medicineAndPrice.txt", ios::in);
    if(!fs.is_open()) {
        cout << "Cannot open medicineAndPrice.txt\n";
        return 0;
    }
    string line;
    while(getline(fs, line)){
        stringstream ss(line);
        string split; 
        getline(ss, split, '|'); //split la ID thuoc
        if(split == ID) {
            getline(ss, split, '|'); // split la ten thuoc
            getline(ss, split, '|'); //split la gia tien o dang string
            return stod(split);
        }
    }
    fs.close();
    return 0;
}

string Prescription::getDosageFormFromFile(string ID) {
    ifstream fs("medicineAndPrice.txt", ios::in);
    if(!fs.is_open()) {
        cout << "Cannot open medicineAndPrice.txt\n";
        return " ";
    }
    string line;
    while(getline(fs, line)){
        stringstream ss(line);
        string split;
        getline(ss, split, '|'); //split la ID thuoc
        if(split == ID) {
            getline(ss, split, '|'); // split la ten thuoc
            getline(ss, split, '|'); //split la gia tien o dang string
            getline(ss, split, '|'); //split la dang bao che cua thuoc
            return split;
        }
    }
    fs.close();
    return " ";
}

Bill::Bill() {
    ID = "";
    nameOfPatient = "";
    totalCost = "0VND";
    statusPay = "0";
    dateOfBill = {0, 0, 0};
}

Bill::Bill(string id, string name, string total, string status, Date date) {
    ID = id;
    nameOfPatient = name;
    totalCost = total;
    statusPay = status;
    dateOfBill = date;
}

Bill::Bill(string phone) : patientPhone(phone) {
    totalCost = "0VND";
    statusPay = "0";
    dateOfBill = {0, 0, 0};
}

void Bill::loadMedicineList() {
    ifstream file("informationPatient.txt");
    if (!file.is_open()) {
        cout << "Cannot open informationPatient.txt.\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string phone, medicineIDList, quantityList;

        getline(iss, phone, '|');
        if (phone == patientPhone) {
            for (int i = 0; i < 7; i++) getline(iss, phone, '|'); // Bỏ qua các thông tin khác
            getline(iss, medicineIDList, '|');
            getline(iss, quantityList, '|');
            cout <<"-------------------------------------------------------------"<<endl;
            cout << "Medicine ID List of Patient: " << medicineIDList << endl; // Gỡ lỗi
            cout << "Quantity for each medicine: " << quantityList << endl; // Gỡ lỗi
            cout <<"-------------------------------------------------------------"<<endl;

            if (!medicineIDList.empty() && !quantityList.empty()) {
                istringstream idStream(medicineIDList);
                istringstream qtyStream(quantityList);

                string id, qty;
                while (getline(idStream, id, ',') && getline(qtyStream, qty, ',')) {
                    if (!id.empty() && !qty.empty()) {
                        try {
                            medicineList.push_back(make_pair(id, stoi(qty)));
                        } catch (const invalid_argument &e) {
                            cout << "Invalid argument: " << e.what() << endl;
                        } catch (const out_of_range &e) {
                            cout << "Out of range: " << e.what() << endl;
                        }
                    }
                }
            }
            break;
        }
    }
    file.close();
}


void Bill::calculateTotalCost() {
    double totalCostDouble = 0.0;
    ifstream medicineFile("medicineAndPrice.txt");
    if (!medicineFile.is_open()) {
        cout << "Cannot open medicineAndPrice.txt\n";
        return;
    }

    string line;
    while (getline(medicineFile, line)) {
        istringstream iss(line);
        string id, name, price, unit;

        getline(iss, id, '|');
        getline(iss, name, '|');
        getline(iss, price, '|');
        getline(iss, unit, '|');
        if (!id.empty() && !price.empty()) {
            try {
                double priceDouble = stod(price);
                for (auto &medicine: medicineList) {
                    if (medicine.first == id) {
                        totalCostDouble += priceDouble * medicine.second;
                    }
                }
            } catch (const invalid_argument &e) {
                cout << "Invalid argument: " << e.what() << endl;
            } catch (const out_of_range &e) {
                cout << "Out of range: " << e.what() << endl;
            }
        }
    }
    medicineFile.close();

    totalCost = to_string(totalCostDouble) + " VND";
}

void Bill::displayBill() {
    cout << RED << "==============" << setw(25) << "HOA DON" << setw(30) << "==============" << endl << RESET;

    // Đọc thông tin bệnh nhân từ file informationPatient.txt để lấy tên bệnh nhân và ID bác sĩ
    ifstream patientFile("informationPatient.txt");
    string line;
    string patientName, doctorID, doctorName, doctorPhone;

    if (!patientFile.is_open()) {
        cout << "Cannot open informationPatient.txt\n";
        return;
    }

    while (getline(patientFile, line)) {
        istringstream iss(line);
        string phone, name, status, birthDate, visitDate, symptoms, hometown, docID, medicineID, quantity;

        getline(iss, phone, '|');
        if (phone == patientPhone) { // Tìm đúng bệnh nhân
            getline(iss, name, '|');
            patientName = name; // Lấy tên bệnh nhân
            getline(iss, status, '|');
            getline(iss, birthDate, '|');
            getline(iss, visitDate, '|');
            getline(iss, symptoms, '|');
            getline(iss, hometown, '|');
            getline(iss, docID, '|');
            doctorID = docID; // Lấy ID bác sĩ
            break;
        }
    }
    patientFile.close();

    // Đọc thông tin bác sĩ từ file informationDoctor.txt để lấy tên bác sĩ
    ifstream doctorFile("informationDoctor.txt");
    string doctorLine;

    if (!doctorFile.is_open()) {
        cout << "Cannot open informationDoctor.txt\n";
        return;
    }

    while (getline(doctorFile, doctorLine)) {
        istringstream iss(doctorLine);
        string id, doctorNameTmp, gender, docPhone, unknown, status;

        getline(iss, id, '|');
        if (id == doctorID) {
            getline(iss, doctorNameTmp, '|');
            doctorName = doctorNameTmp; // Lấy tên bác si
            getline(iss, gender, '|');     
            getline(iss, docPhone, '|');
            doctorPhone = docPhone; // Lấy số điện thoại bác sĩ
            getline(iss, unknown, '|');
            getline(iss, status, '|');
            break;
        }
    }
    doctorFile.close();

    // Hiển thị thông tin bệnh nhân và bác sĩ
    cout << left << setw(10) << "ID benh nhan: " << patientPhone 
     << setw(10) << ""  
     << left << setw(10) << "Benh nhan: " << patientName << endl;
    cout << left << setw(10) << "SDT benh nhan: " << patientPhone
        << setw(10) << ""  
        << left << setw(10) << "Bac si: " << doctorName
        << setw(10) << "" 
        << left << setw(10) << "SDT Bac si: " << doctorPhone << endl;

    cout << "-------------------------------------------------------------------------------------------------" << endl;

    // Hiển thị danh sách thuốc
    ifstream medicineFile("medicineAndPrice.txt");
    if (!medicineFile.is_open()) {
        cout << "Cannot open medicineAndPrice.txt\n";
        return;
    }

    cout << left << setw(15) << "ID Thuoc" << " | " 
         << left << setw(30) << "Ten Thuoc" << " | " 
         << right << setw(15) << "Don gia" << " | " 
         << right << setw(10) << "So luong" << " | " 
         << right << setw(15) << "Thanh tien" << endl;
    cout << "-------------------------------------------------------------------------------------------------" << endl;

    while (getline(medicineFile, line)) {
        istringstream iss(line);
        string id, name, price, unit;

        getline(iss, id, '|');
        getline(iss, name, '|');
        getline(iss, price, '|');
        getline(iss, unit, '|');

        if (!id.empty() && !price.empty()) {
            try {
                double priceDouble = stod(price);
                for (auto &medicine : medicineList) {
                    if (medicine.first == id) {
                        double cost = priceDouble * medicine.second;
                        cout << left << setw(15) << id << " | " 
                             << left << setw(30) << name << " | " 
                             << right << setw(15) << std::fixed << std::setprecision(2) << price << " | " 
                             << right << setw(10) << medicine.second << " | " 
                             << right << setw(15) << std::fixed << std::setprecision(2) << cost << endl;
                    }
                }
            } catch (const invalid_argument &e) {
                cout << "Invalid argument: " << e.what() << endl;
            } catch (const out_of_range &e) {
                cout << "Out of range: " << e.what() << endl;
            }
        }
    }
    medicineFile.close();

    cout << "--------------------------------" << endl;
    cout << "Tong chi phi: " << totalCost << endl;

    int totalCostInt = stoi(totalCost);
    cout << "Thanh chu: ";
    docso(totalCostInt);
    cout << endl;
    cout << "=================================" << endl;
}
