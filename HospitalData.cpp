#include "./HospitalData.hpp"
#include "./HospitalFunction.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
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
        cout << "Enter Password: ";
        cin >> this->pass;

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
    cout << "Enter the patient's admission date (dd mm yyyy): ";
    Date admission;
    do{
        is >> admission.day >> admission.month >> admission.year;
        p->setDateOfHospital(admission);
        if(!validationDate(admission)) {
            cout << "Enter admission date failed. Try again: ";
        }
    }while(!validationDate(admission));
    
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
    cout << setw(60) << "_____________________________________" << endl;
    cout << setw(60) << "|     THE PATIENT'S INFORMATION     |" << endl;
    cout << setw(60) << "|___________________________________|" << endl << endl;
    cout << "The patien's name: ";
    os << p->name << endl;
    cout << "The patien's gender: ";
    if(p->gender == 0) cout << "FEMALE\n";
    else cout << "MALE\n";
    cout << "The patient's telephone number: ";
    os << p->phoneNumber << endl;
    cout << "The patient's date of birth: ";
    os << p->dateOfBirth.day << "/" << p->dateOfBirth.month << "/" << p->dateOfBirth.year << endl;
    cout << "The patient's admission date: ";
    os << p->dateOfHospital.day << "/" << p->dateOfHospital.month << "/" << p->dateOfHospital.year << endl;
    cout << "The patient's address: ";
    os << p->address << endl;
    cout << "The patient's current status: ";
    os << p->currentStatus << endl;
    cout << "The ID of doctor: ";
    os << p->IDdoctor << endl;
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

void Patient::readInFormationByPhoneNumber(const string &phoneNumberCheck, int &check) {
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
        if(split == phoneNumberCheck) {
            check = 1;
            this->phoneNumber = split;
            getline(ss, split, '|'); // split la ten benh nhan
            this->name = split;
            getline(ss, split, '|'); // split la gender cua benh nhan
            this->gender = stoi(split);
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
                    this->dateOfHospital.day = stoi(temp);
                }else if(i == 1) {
                    this->dateOfHospital.month = stoi(temp);
                }else {
                    this->dateOfHospital.year = stoi(temp);
                }
            }
            getline(ss, split, '|'); // split la trieu chung cua benh nhan
            this->currentStatus = split;
            getline(ss, split, '|'); // split la que quan cua benh nhan
            this->address = split;
            getline(ss, split, '|'); // split la ID bac si
            this->IDdoctor = split;
        }

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
    cout << "The doctor's ID: ";
    os << d->ID << endl;
    cout << "The doctor's name: ";
    os << d->name << endl;
    cout << "The doctor's gender: ";
    if(d->gender == 0) cout << "FEMALE\n";
    else cout << "MALE\n";
    cout << "The doctor's working status: ";
    if(d->working == 0) cout << "NO\n";
    else cout << "YES\n";
    cout << "_________________________________________________________________________________\n";
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
    while(getline(fs, line)) {
        stringstream ss(line);
        string split;
        getline(ss, split, '|'); // split la ID
        string id = split;
        getline(ss, split, '|'); // split la ten
        string name = split;
        getline(ss, split, '|'); // split la gender
        int gender = stoi(split);
        getline(ss, split, '|'); // split la sdt
        string phoneNumber = split;
        getline(ss, split, '|'); // split la so nam kinh nghiem
        getline(ss, split, '|'); // split la status
        int status = stoi(split);
        if(status == 1) {
            cout << "The doctor's ID: " << id << endl;
            cout << "The doctor's name: " << name << endl;
            cout << "The doctor's gender: ";
            if(gender == 1) cout << "MALE\n";
            else cout << "FEMALE\n";
            cout << "The doctor's phone number: " << phoneNumber << endl;
            cout << "The doctor's status: YES\n";
            cout << "______________________________________________________\n";
        }
    }
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
    cout << setw(60) << "_____________________________________" << endl;
    cout << setw(60) << "|     THE MEDICINE'S INFORMATION    |" << endl;
    cout << setw(60) << "|___________________________________|" << endl << endl;
    ifstream fs("medicineAndPrice.txt", ios::in);
    if(!fs.is_open()){
        cout << "Cannot open medicineAndPrice.txt";
        return;
    }
    string line;
    while(getline(fs, line)){
        stringstream ss(line);
        string temp;
        getline(ss, temp, '|'); // temp la ID thuoc
        cout << "ID: " << temp << endl;
        getline(ss, temp, '|'); // temp la ten thuoc
        cout << "Medicine's name: " << temp << endl;
        getline(ss, temp, '|'); //temp la gia ban hang(bo qua)
        getline(ss, temp, '|'); // temp la dang bao che
        cout << "Medicine's dosage form: " << temp << endl;
        cout << "___________________________________________________________________\n";
    }
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
	treatmentCost = "0VND";
	medicalsCost = "0VND";
	totalCost = "0VND";
	statusPay = "0"; 
	dateOfBill = {0, 0, 0}; 
}

Bill::Bill(string id, string name, string treatment, string medicals, string total, string status, Date date) {
	ID = id;
	nameOfPatient = name;
	treatmentCost = treatment;
	medicalsCost = medicals;
	totalCost = total;
	statusPay = status;
	dateOfBill = date;
}

