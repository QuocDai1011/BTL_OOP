#include "HospitalData.hpp"

Human::Human() {
	name = "";
	gender = 0;
	phoneNumber = "";
}
Human::Human(string name, int gender, string phoneNumber) {
	this->name = name;
	this->gender = gender;
	this->phoneNumber = phoneNumber;
}

Staff::Staff() : Human() { 
	ID = "";
	address = "";
}

Staff::Staff(string name, int gender, string phoneNumber, string ID, string address)
	: Human(name, gender, phoneNumber) { 
	this->ID = ID;
	this->address = address;
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
 