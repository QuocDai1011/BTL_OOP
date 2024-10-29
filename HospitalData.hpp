#ifndef HOSPITALDATA_H
#define HOSPITALDATA_H

#include <string>
using namespace std;

struct Date	{
	int day;
	int month;
	int year;	
};

class Human {
	private:
		string name;
		int gender; // quy dinh 0 la NU va 1 la NAM
		string phoneNumber;
	public:
		Human();
		Human(string name, int gender, string phoneNumber);
};

class Staff : public Human {
	private: 
		string ID;
		string address;
	public:
		Staff();  
		Staff(string name, int gender, string phoneNumber, string ID, string address);	
};

class Patient : public Human {
	private:
		Date dateOfBirth;
		string address;
		string medicalHistory; // lich su benh
		Date dateOfHospital; // ngay nhap vien
		string currentStatus; // tinh trang hien tai
	public:
		Patient();
		Patient(string name, int gender, string phoneNumber, Date dateOfBirth, 
		string address, string medicalHistory, Date dateOfHospital, string currentStatus);
};

class Doctor : public Human {
	private: 
		string ID;
		string specialtyDoctor; //chuyen khoa
		int experience; //tinh bang so nam lam viec
		int working; //co dang lam viec hay khong 0 la KHONG CO BENH NHAN KHAM, 1 la DANG KHAM  
	public:
		Doctor();
		Doctor(string name, int gender, string phoneNumber, string ID, string specialtyDoctor, int experience, int working);
};

class Prescription {
	private:
		string ID;
		string namePrescription;
		string dosage; //lieu luong cua thuoc
		Date dateOfPresciption; // ngay ke don thuoc
		string nameOfDoctor; // ten bac si ke don thuoc
		string nameOfPatient; // ten benh nhan
	public:
		Prescription();
		Prescription(string ID, string namePrescription, string dosage, Date dateOfPresciption, string nameOfDoctor, string nameOfPatient);
};

class Bill {
	private:
		string ID;
		string nameOfPatient; // ten cua benh nhan
		string treatmentCost; // chi phi DIEU TRI CHU Y KIEU DU LIEU STRING. Don vi la VND. Vi du: 300000VND
		string medicalsCost; // Chi phi THUOC. CHU Y GIONG O TREN
		string totalCost; // Tong chi phi
		string statusPay; //Tinh trang thanh toan. Quy dinh: 0 la CHUA THANH TOAN, 1 la DA THANH TOAN
		Date dateOfBill; //Ngay tao ra BILL
	public: 
		Bill();
		Bill(string ID, string nameOfPatient, string treatmentCost, string medicalsCost, string totalCost, string statusPay, Date dateOfBill);
};

#endif
