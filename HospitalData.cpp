#include "./HospitalData.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
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

// HospitalData.cpp

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
void Staff::logIn() {
    cout << setw(50) << "__________" << endl;
    cout << setw(50) << "| LOGIN  |" << endl;
    cout << setw(50) << "|________|" << endl;
	cout << "Enter ID: ";
	cin >> this->ID;
	cin.ignore();
	cout << "Enter Password: ";
	cin >> this->pass;
	/*cout << this->ID << ' ' << this->pass;*/
	ifstream fs("D:\\Coding\\Code_C_Cpp\\OOP_HOSPITAL_vscode\\Information\\informationStaff.txt", ios::in);
	if(!fs.is_open()) {
		cout << "Cannot open file informationStaff.txt";
	}else {
		for(int i=0; i<3; i++) {
			string str;
			getline(fs, str);
			stringstream ss(str);
			string split;
			ss >> split; // ID
			int checkID = 0, checkPass = 0;
			if(split == this->ID){
				checkID = 1;
			}
			ss >> split;
			if(split == this->pass){
				checkPass = 1;
			}
			if(checkID && checkPass) {
				cout << "LOGIN SUCCESS!";
				return;
			}
		}
		cout << "LOGIN FAILED!";
		return;
	}
}

Patient::Patient() : Human() {
	dateOfBirth = {0, 0, 0};
	address = "";
	medicalHistory = "";
	dateOfHospital = {0, 0, 0};
	currentStatus = "";
}

Patient::Patient(string name, int gender, string phoneNumber, Date dateOfBirth, string address, string medicalHistory, Date dateOfHospital, string currentStatus)
	: Human(name, gender, phoneNumber) {
	this->dateOfBirth = dateOfBirth;
	this->address = address;
	this->medicalHistory = medicalHistory;
	this->dateOfHospital = dateOfHospital;
	this->currentStatus = currentStatus;	
}

Doctor::Doctor() : Human() {
	ID = "";
	specialtyDoctor = "";
	experience = 0; 
	working = 0;
}

Doctor::Doctor(string name, int gender, string phoneNumber, string ID, string specialtyDoctor, int experience, int working)
	: Human(name, gender, phoneNumber) {
	this->ID = ID;
	this->specialtyDoctor = specialtyDoctor;
	this->experience = experience;
	this->working = working;
}

Prescription::Prescription() {
	ID = "";
	namePrescription = "";
	dosage = ""; //lieu luong cua thuoc
	dateOfPresciption = {0, 0, 0}; // ngay ke don thuoc
	nameOfDoctor = ""; // ten bac si ke don thuoc
	nameOfPatient = ""; // ten benh nhan
}

Prescription::Prescription(string ID, string namePrescription, string dosage, Date dateOfPresciption, string nameOfDoctor, string nameOfPatient) {
	this->ID = ID;
	this->namePrescription = namePrescription;
	this->dosage = dosage;
	this->dateOfPresciption = dateOfPresciption;
	this->nameOfDoctor = nameOfDoctor;
	this->nameOfPatient = nameOfPatient;
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

