#include "./HospitalData.hpp"
#include "./HospitalFunction.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <conio.h>
#include <vector>
using namespace std;

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
    cout << setw(50) << "__________" << endl;
    cout << setw(50) << "| LOGIN  |" << endl;
    cout << setw(50) << "|________|" << endl;
	ifstream fs("informationStaff.txt", ios::in);
	if(!fs.is_open()){
		cout << "Cannot open file informationStaff.txt";
		return;
	}
	int attemptCount = 3; // Giới hạn số lần đăng nhập
    while (attemptCount--) {
        cout << "Enter ID: ";
        cin >> this->ID;
        char ch;
        cout << "Enter Password: ";
        while (true) {
            ch = _getch(); // Lấy ký tự mà không hiển thị
            if (ch == 13) { // Kiểm tra nếu người dùng nhấn Enter
                break;
            } else if (ch == 8) { // Kiểm tra nếu người dùng nhấn Backspace
                if (!this->pass.empty()) {
                    this->pass.pop_back(); // Xóa ký tự cuối cùng trong mật khẩu
                    cout << "\b \b"; // Xóa dấu * trên màn hình
                }
            } else {
                this->pass += ch; // Thêm ký tự vào mật khẩu
                cout << "*"; // Hiển thị dấu * cho mỗi ký tự nhập
            }
        }
        cout << endl;

        fs.clear(); // Xóa trạng thái EOF (nếu có)
        fs.seekg(0); // Đưa con trỏ tệp về đầu

        bool loginSuccess = false;
        string str;
        while (getline(fs, str)) {
            stringstream ss(str);
            string fileID, filePass;
            ss >> fileID >> filePass;

            if (fileID == this->ID && filePass == this->pass) {
				system("CLS");
                cout << "LOGIN SUCCESS! Hello ";
                string name;
				string fullName;
                while (ss >> name) {
					fullName += name + " ";
                    cout << name << ' ';
                }
				this->name = fullName;
                cout << "\nLoading: ";
                for(int i=1; i<=50; i++) {
                    int temp = 0;
                    for(int i=0; i<10000; i++) {
                        for(int i=0; i<10000; i++){
                            temp += temp;
                        }
                    }
                    cout << "=";
                }
                cout << " SUCCESS =)))\n";
                cout << "HAVE A NICE DAY!\n";
				login = 1;
                fs.close();
                return;
            }
        }

        cout << "LOGIN FAILED!" << endl;
    }

    cout << "Too many failed attempts. Please try again later.\n";
    fs.close();
	
}

Patient::Patient() : Human() {
	dateOfBirth = {0, 0, 0};
	address = "";
	dateOfHospital = {0, 0, 0};
	currentStatus = "";
    IDdoctor = "";
    IDmedicine = "";
    quantity = "";
}

Patient::Patient(string name, int gender, string phoneNumber, Date dateOfBirth, 
string address, Date dateOfHospital, string currentStatus, string IDdoctor, string IDmedicine, string quantity)
	: Human(name, gender, phoneNumber) {
	this->dateOfBirth = dateOfBirth;
	this->address = address;
	this->dateOfHospital = dateOfHospital;
	this->currentStatus = currentStatus;	
    this->IDdoctor = IDdoctor;
    this->IDmedicine = IDmedicine;
    
}

Date Patient::getDateOfBirth() {
	return this->dateOfBirth;
}

string Patient::getAddress() {
	return this->address;
}

Date Patient::getDateOfHospital() {
	return this->dateOfHospital;
}

string Patient::getCurrentStatus() {
	return this->currentStatus;
}
string Patient::getIDdoctor() {
    return this->IDdoctor;
}

void Patient::setName(const string &newName) {
	Human::setName(newName);
}

void Patient::setDateOfBirth(const Date &newDate) {
	this->dateOfBirth.day = newDate.day;
	this->dateOfBirth.month = newDate.month;
	this->dateOfBirth.year = newDate.year;
}

void Patient::setAddress(const string &newAddress) {
	this->address = newAddress;
}

void Patient::setDateOfHospital(const Date &newDate) {
	this->dateOfHospital.day = newDate.day;
	this->dateOfHospital.month = newDate.month;
	this->dateOfHospital.year = newDate.year;
}

void Patient::setCurrentStatus(const string &newStatus) {
	this->currentStatus = newStatus;
}
void Patient::setIDdoctor(const string &newIDdoctor) {
    this->IDdoctor = newIDdoctor;
}

istream& operator>>(istream& is, Patient *p) {
    cout << setw(60) << "_____________________________________" << endl;
    cout << setw(60) << "|  ENTER THE PATIENT'S INFORMATION  |" << endl;
    cout << setw(60) << "|___________________________________|" << endl;
    cout << endl;
    cout << "Enter the patient's name: ";
    is >> ws; // Xóa khoảng trắng thừa
    getline(is, p->name);
    p->name = nameFormat(p->name);

    cout << "Enter patient's gender (0: FEMALE || 1: MALE): ";
    do {
        is >> p->gender;
        if (p->gender != 0 && p->gender != 1) {
            cout << "Invalid input! Try again: ";
        }
    } while (p->gender != 0 && p->gender != 1);
    
    is.ignore(); // Xóa bộ đệm sau khi nhập gender

    cout << "Enter the patient's telephone number: ";
    is >> ws; // Xóa khoảng trắng thừa
    getline(is, p->phoneNumber);

    cout << "Enter the patient's date of birth (dd mm yyyy): ";
    Date birth;
    do {
        is >> birth.day >> birth.month >> birth.year;
        p->setDateOfBirth(birth);
        if(!validationDate(birth)){
            cout << "Enter date of birth failed. Try again: ";
        }
    }while(!validationDate(birth));
    Date admission;
    getCurrentDate(admission.day, admission.month, admission.year);
    p->setDateOfHospital(admission);
    is.ignore(); // Xóa bộ đệm sau khi nhập admission date

    cout << "Enter the province where the patient resides: ";
    string province;
    getline(is, province);
    province = nameFormat(province);
    p->setAddress(province);

    cout << "Enter the patient's current condition: ";
    string status;
    getline(is, status);
    p->setCurrentStatus(status);
    cout << "-------------------- LIST OF DOCTORS ON DUTY --------------------\n";
    Doctor dt;
    dt.readDoctorStatus();
    cout << "Enter the ID of the doctor: ";
    string ID;
    cin >> ID;
    p->setIDdoctor(ID);
    system("CLS");
    cout << "-------------------------- DOCTOR CHOOSES MEDICINE FOR PATIENT --------------------------\n";
    cout << "The patient's name: " << p->name << endl;
    cout << "The patient's date of birth: " << birth.day << "/" << birth.month << "/" << birth.year << endl;
    cout << "The patient's current status: " << status << endl;
    Prescription pre;
    pre.readFromFile();
    cout << "Enter medication according to patient ID: ";
    is >> ws;
    getline(is, p->IDmedicine);
    p->IDmedicine = removeSpace(p->IDmedicine);
    cout << "Enter the quantity of medicine corresponding to the type of medicine: ";
    getline(is, p->quantity);
    p->quantity = removeSpace(p->quantity);
    cout << "___________________________________________________________________________________\n";
    return is;
}

ostream& operator<<(ostream& os, Patient *p) {
    // In tiêu đề bảng
  
    // In thông tin bệnh nhân theo các cột
    os << "| " << setw(20) << left << p->name
       << "| " << setw(8) << left;
    if (p->gender == 0) os << "FEMALE";
    else os << "MALE";
    string dateBirth = to_string(p->dateOfBirth.day) + "/" + to_string(p->dateOfBirth.month) + "/" + to_string(p->dateOfBirth.year);
    string dateAmi = to_string(p->dateOfHospital.day) + "/" + to_string(p->dateOfHospital.month) + "/" + to_string(p->dateOfHospital.year);
    os << "| " << setw(17) << left << p->phoneNumber
       << "| " << setw(18) << left << dateBirth
       << "| " << setw(18) << left << dateAmi
       << "| " << setw(19) << left << p->address
       << "| " << setw(24) << left << p->currentStatus
       << "| " << setw(12) << left << p->IDdoctor << " |" << endl;

    os << "+---------------------+---------+------------------+-------------------+-------------------+--------------------+-------------------------+--------------+" << endl;

    return os;
}

void Patient::writeToFile() {
    ofstream fs("informationPatient.txt", ios::app);
    if(!fs.is_open()) {
        cout << "Cannot open file informationPatient.txt";
        return;
    }
    fs << this->phoneNumber << "|";
    fs << this->name << "|";
    fs << this->gender << "|";
    fs << this->dateOfBirth.day << "/" << this->dateOfBirth.month << "/" << this->dateOfBirth.year << "|";
    fs << this->dateOfHospital.day << "/" << this->dateOfHospital.month << "/" << this->dateOfHospital.year << "|";
    fs << this->currentStatus << "|";
    fs << this->address << "|";
    fs << this->IDdoctor << "|";
    fs << this->IDmedicine << "|";
    fs << this->quantity << "|\n";
    fs.close();
}

void Patient::readInFormationByPhoneNumber(const string &phoneNumberCheck, int &check, Patient *p) {
    ifstream fs("informationPatient.txt",  ios::in);
    if(!fs.is_open()) {
        cout << "Cannot open information.txt.\n";
        return;
    }
    check = 0;
    string line;
    while(getline(fs, line)) {
        stringstream ss(line);
        string split;
        getline(ss, split, '|'); //split la so dien thoai = ID benh nhan
        int ok = 0;
        if(split == phoneNumberCheck) {
            ok = 1;
            check = 1;
            p->phoneNumber = split;
            getline(ss, split, '|'); // split la ten benh nhan
            p->name = split;
            getline(ss, split, '|'); // split la gender cua benh nhan
            p->gender = stoi(split);
            getline(ss, split, '|'); // split la ngay sinh cua benh nhan
            stringstream ssplit(split);
            string temp;
            for(int i = 0; i<3; i++){
                getline(ssplit, temp, '/'); // ssplit la ngay sinh
                if(i == 0) {
                    this->dateOfBirth.day = stoi(temp);
                }else if(i == 1) {
                    this->dateOfBirth.month = stoi(temp);
                }else {
                    this->dateOfBirth.year = stoi(temp);
                }
            }
            getline(ss, split, '|'); // split la ngay nhap vien cua benh nhan
            stringstream ssplitt(split);
            for(int i = 0; i<3; i++){
                getline(ssplitt, temp, '/'); // ssplit la ngay sinh
                if(i == 0) {
                    p->dateOfHospital.day = stoi(temp);
                }else if(i == 1) {
                    p->dateOfHospital.month = stoi(temp);
                }else {
                    p->dateOfHospital.year = stoi(temp);
                }
            }
            getline(ss, split, '|'); // split la trieu chung cua benh nhan
            p->currentStatus = split;
            getline(ss, split, '|'); // split la que quan cua benh nhan
            p->address = split;
            getline(ss, split, '|'); // split la ID bac si
            p->IDdoctor = split;
        }
        if(ok) cout << p;

    }
    fs.close();
} 

void Patient::updateInformation() {
    cout << "Update the patient's admission date (dd mm yyyy): ";
    Date doa;
    cin >> doa.day >> doa.month >> doa.year;
    this->dateOfHospital = doa;
    cout << "Update the patient's current status: ";
    string temp;
    cin.ignore();
    getline(cin, temp);
    this->currentStatus = temp;
    cout << "-------------------- LIST OF DOCTORS ON DUTY --------------------\n";
    Doctor dt;
    dt.readDoctorStatus();
    cout << "Enter the ID of the doctor: ";
    string ID;
    cin >> ID;
    this->IDdoctor = ID;
    system("CLS");
    cout << "-------------------------- DOCTOR CHOOSES MEDICINE FOR PATIENT --------------------------\n";
    cout << "The patient's name: " << this->name << endl;
    cout << "The patient's date of birth: " << this->dateOfBirth.day << "/" << this->dateOfBirth.month << "/" << this->dateOfBirth.year << endl;
    cout << "The patient's current status: " << this->currentStatus << endl;
    Prescription pre;
    pre.readFromFile();
    cout << "Enter medication according to patient ID: ";
    cin.ignore();
    getline(cin, this->IDmedicine);
    this->IDmedicine = removeSpace(this->IDmedicine);
    cout << "Enter the quantity of medicine corresponding to the type of medicine: ";
    getline(cin, this->quantity);
    this->quantity = removeSpace(this->quantity);
    cout << "___________________________________________________________________________________\n";
  
}


Doctor::Doctor() : Human() {
	ID = "";
	experience = 0; 
	working = 0;
}

Doctor::Doctor(string name, int gender, string phoneNumber, string ID, int experience, int working)
	: Human(name, gender, phoneNumber) {
	this->ID = ID;
	this->experience = experience;
	this->working = working;
}

string Doctor::getID() {
    return this->ID;
}

int Doctor::getExperience() {
    return this->experience;
}

int Doctor::getWorking() {
    return this->working;
}

void Doctor::setID(const string &newID) {
    this->ID = newID;
}

void Doctor::setExperience(const int &newExperience) {
    this->experience = newExperience;
}

void Doctor::setWorking(const int &newWorking) {
    this->working = newWorking;
}

ostream& operator<<(ostream& os, Doctor *d) {
    // In tiêu đề bảng
    os << "| " << setw(8) << left << d->ID
       << "| " << setw(23) << left << d->name
       << "| " << setw(8) << left;
    if (d->gender == 0) os << "FEMALE";
    else os << "MALE";
    os << "| " << setw(7) << left;
    if (d->working == 0) os << "NO";
    else os << "YES";
    os << " |" << endl;
    
    os << "+---------+------------------------+---------+---------+" << endl;

    return os;
}


void Doctor::readFromFile(int index) {
    ifstream fs("informationDoctor.txt", ios::in);
    if(!fs.is_open()) {
        cout << "Cannot open informationDoctor.txt\n";
        return;
    }
    for(int i=0; i<index; i++) {
        string line1;
        getline(fs, line1);
    }
    string line;
    getline(fs, line);
    stringstream ss(line);
    string word;
    getline(ss, word, '|'); //word la ID
    this->ID = word;
    getline(ss, word, '|'); //word la ten
    this->name = word;
    getline(ss, word, '|'); // word la gender
    this->gender = stoi(word);
    getline(ss, word, '|'); // word la so dien thoai
    this->phoneNumber = word;
    getline(ss, word, '|'); //word la nam kinh nghiem
    this->experience = stoi(word);
    getline(ss, word, '|'); // word la trang thai lam viec
    this->working = stoi(word);
    fs.close();
}

void Doctor::readDoctorStatus() {
    ifstream fs("informationDoctor.txt", ios::in);
    if(!fs.is_open()) {
        cout << "Cannot open informationDoctor.txt\n";
        return;
    }
    
    string line;
    
    // In tiêu đề bảng
    cout << "+---------+-----------------------+---------+---------------------+------------+" << endl;
    cout << "| ID      | Name                  | Gender  | Phone Number        | Status     |" << endl;
    cout << "+---------+-----------------------+---------+---------------------+------------+" << endl;
    
    // Đọc thông tin từ file và in ra bảng
    while(getline(fs, line)) {
        stringstream ss(line);
        string split;
        
        // Tách các trường thông tin
        getline(ss, split, '|'); // ID
        string id = split;
        getline(ss, split, '|'); // Name
        string name = split;
        getline(ss, split, '|'); // Gender
        int gender = stoi(split);
        getline(ss, split, '|'); // Phone number
        string phoneNumber = split;
        getline(ss, split, '|'); // Experience
        getline(ss, split, '|'); // Status
        int status = stoi(split);
        
        // Chỉ hiển thị bác sĩ có trạng thái là đang làm việc (status == 1)
        if(status == 1) {
            cout << "| " << setw(8) << left << id
                 << "| " << setw(22) << left << name
                 << "| " << setw(8) << left;
            if(gender == 1) cout << "MALE";
            else cout << "FEMALE";
            cout << "| " << setw(20) << left << phoneNumber
                 << "| " << setw(10) << left << "YES" << " |" << endl;
        }
    }
    
    // In cuối bảng
    cout << "+---------+-----------------------+---------+---------------------+------------+" << endl;
    
    fs.close();
}
void Doctor::readFromFileByID(const string &IDcheck, int &check){
    check = 0;
     ifstream fs("informationDoctor.txt", ios::in);
    if(!fs.is_open()) {
        cout << "Cannot open informationDoctor.txt\n";
        return;
    }
    string line;
    while(getline(fs, line)) {
        stringstream ss(line);
        string split;
        getline(ss, split, '|'); // ID
        if(split == IDcheck) {
            this->ID = split;
            getline(ss, split, '|'); //name
            this->name = split;
            getline(ss, split, '|'); //gender
            this->gender = stoi(split);
            getline(ss, split, '|'); // sdt;
            this->phoneNumber = split;
            getline(ss, split, '|'); //experience
            this->experience = stoi(split);
            getline(ss, split, '|'); //status
            this->working = stoi(split);
        }
    }
    fs.close();
}

Prescription::Prescription() {
	ID = "";
	namePrescription = "";
    price = 0;
    dosageForm = "";
}

Prescription::Prescription(string ID, string namePrescription, double price, string dosageForm) {
	this->ID = ID;
	this->namePrescription = namePrescription;
    this->price = price;
    this->dosageForm = dosageForm;
}

void Prescription::readFromFile() {
    // In tiêu đề bảng
    cout << "+---------+----------------------------------+---------+-------------------------+" << endl;
    cout << "| ID      | Medicine's Name                  | Cost    | Dosage Form             |" << endl;
    cout << "+---------+----------------------------------+---------+-------------------------+" << endl;

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
    cout << "==============" << setw(25) << "HOA DON" << setw(30) << "==============" << endl;

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
